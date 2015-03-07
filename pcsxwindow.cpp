#include "pcsxwindow.h"
#include <QPixmap>
#include <QDockWidget>
#include <QScrollArea>
#include <QMenuBar>
#include <QMenu>
#include <QMessageBox>
#include <QSignalMapper>
#include <QSettings>
#include <QCoreApplication>
#include <QSpacerItem>
#include <QDebug>
#include <cstdlib>
#include <unistd.h>

PcsxWindow::PcsxWindow(QWidget *parent) : QMainWindow(parent) {
    createMenu();

    _screen = new QWidget();
    setCentralWidget(_screen);

    _vboxLayout = new QVBoxLayout();
    _screen->setLayout(_vboxLayout);

    addSettings();

    _fileManager = new FileManager("data/");
    createLabels(_fileManager->getFilesImages());

    addSlider();

    setMinimumSize(600, 600);
    setWindowTitle(tr("PCSX Interface"));
}

void PcsxWindow::createMenu() {
    QSettings settings("Pcsx2Interface", "Pcsx2InterfaceSettings");
    settings.beginGroup("Options");
    bool isFullscreen = settings.value("fullscreen").value<bool>();
    bool isNohacks = settings.value("nohacks").value<bool>();
    settings.endGroup();

    QMenu* file = menuBar()->addMenu("File");
    file->addAction("Quit", this, SLOT(close()));
    connect(qApp, SIGNAL(aboutToQuit()), this, SLOT(saveSettings()));

    QMenu *options = menuBar()->addMenu("Settings");
    QAction *fullscreen = options->addAction("Fullscreen");
    fullscreen->setCheckable(true);
    fullscreen->setChecked((isFullscreen) ? true : false);
    _actions.push_back(fullscreen);

    QAction *nohacks = options->addAction("No hacks");
    nohacks->setCheckable(true);
    nohacks->setChecked((isNohacks) ? true : false);
    _actions.push_back(nohacks);

    QSignalMapper* mapper = new QSignalMapper(this);
    mapper->setMapping(fullscreen, FULLSCREEN);
    mapper->setMapping(nohacks, NOHACK);
    connect(fullscreen, SIGNAL(triggered()), mapper, SLOT(map()));
    connect(nohacks, SIGNAL(triggered()), mapper, SLOT(map()));
    connect(mapper, SIGNAL(mapped(int)), this, SLOT(handleOption(int)));

    QMenu* help = menuBar()->addMenu("Help");
    help->addAction("About",this,SLOT(about()));

    for(unsigned int i = 0; i < _actions.size(); ++i) {
         handleOption(i);
    }
}

void PcsxWindow::addSettings() {
    QHBoxLayout *hlayout = new QHBoxLayout();
    _vboxLayout->addLayout(hlayout);
    hlayout->addStretch();

    _lineEdit = new QLineEdit();
    _lineEdit->setPlaceholderText("Ex : Final fantasy X");

    _list = new QPushButton();
    _list->setIcon(QIcon(":/img/list.png"));
    _list->setIconSize(QSize(25,25));
    _list->setStyleSheet("QPushButton { background: none; border: none; margin: 0px; padding: 0px; } QPushButton:focus { border: none; outline: none; } ");

    _thumbnail = new QPushButton();
    _thumbnail->setIcon(QIcon(":/img/thumbnails.png"));
    _thumbnail->setIconSize(QSize(25,25));
    _thumbnail->setStyleSheet("QPushButton { background: none; border: none; margin: 0px; padding: 0px; } QPushButton:focus { border: none; outline: none; } ");

    hlayout->addWidget(_lineEdit);
    hlayout->addSpacerItem(new QSpacerItem(300, 25));
    hlayout->addWidget(_thumbnail);
    hlayout->addSpacerItem(new QSpacerItem(5, 5));
    hlayout->addWidget(_list);
    hlayout->addStretch();
    hlayout->setSpacing(0);

    connect(_lineEdit, SIGNAL(textChanged(QString)), this, SLOT(handleLineEdit(QString)));
    connect(_list, SIGNAL(clicked()), this, SLOT(handleList()));
    connect(_thumbnail, SIGNAL(clicked()), this, SLOT(handleThumbnails()));
}

void PcsxWindow::createLabels(std::vector<std::string> filesImages) {
    _gridLayout = new QGridLayout();
    _vboxLayout->addLayout(_gridLayout);

    unsigned int j = 0, k =0;
    for (unsigned int i = 0; i < filesImages.size(); ++i) {
        if(i % 4 == 0) {
            j++;
            k = 0;
        }

        QPixmap pix(filesImages[i].c_str());
        PcsxLabel *label = new PcsxLabel("");
        label->setPixmap(pix);
        label->setMaximumHeight(400);
        label->setScaledContents(true);
        _gridLayout->addWidget(label, j, k);
        _labels.push_back(label);

        k++;
        connect(label, SIGNAL(clicked(QString)), this, SLOT(launchGame(QString)));
    }
}

void PcsxWindow::addSlider() {
    QHBoxLayout *hlayout = new QHBoxLayout();
    _vboxLayout->addLayout(hlayout);
    _slider = new QSlider(Qt::Horizontal);
    _slider->setMinimum(150);
    _slider->setMaximum(400);
    _slider->setValue(400);
    hlayout->addWidget(_slider);
    connect(_slider, SIGNAL(valueChanged(int)), this, SLOT(handleLabelSize(int)));
}

void PcsxWindow::handleLabelSize(int size) {
    for(unsigned int i = 0; i < _labels.size(); ++i) {
         _labels[i]->setMaximumHeight(size);
    }
}


void PcsxWindow::handleLineEdit(QString text) {

}

void PcsxWindow::handleThumbnails() {

}

void PcsxWindow::handleList() {

}

void PcsxWindow::handleOption(int option) {
    std::string optionName = optionsName[option];
    if(_actions[option]->isChecked()) {
        _options += optionName;
    } else {
        std::size_t found = _options.find(optionName);
        if (found != std::string::npos) {
            _options.replace(found, optionName.size(), "");
        }
    }
}

void PcsxWindow::launchGame(QString gameName) {
    std::string command = "pcsx2 \""+gameName.toStdString()+"\" --nogui "+_options;
    qDebug() << command.c_str();
//    int pid = fork();
//    if (pid==0) {
//        system(command.c_str());
//        exit(0);
//    }
}

void PcsxWindow::about() {
    QMessageBox *msg = new QMessageBox();
    msg->setText("Author : Vimont Ludovic");
    msg->exec();
}

void PcsxWindow::saveSettings() {
    QSettings settings("Pcsx2Interface", "Pcsx2InterfaceSettings");
    settings.beginGroup("Options");
    settings.setValue("fullscreen", (_actions[FULLSCREEN]->isChecked()) ? true : false);
    settings.setValue("nohacks", (_actions[NOHACK]->isChecked()) ? true : false);
    settings.endGroup();
}
