#include "pcsxwindow.h"
#include <QPixmap>
#include <QGridLayout>
#include <QDockWidget>
#include <QScrollArea>
#include <QMenuBar>
#include <QMenu>
#include <QMessageBox>
#include <QSignalMapper>
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

    FileManager _fileManager = FileManager("data/");
    createLabels(_fileManager.getFilesImages());

    addSlider();

    setMinimumSize(600, 600);
    setWindowTitle(tr("PCSX Interface"));
}

void PcsxWindow::createMenu() {
    QMenu* file = menuBar()->addMenu("File");
    file->addAction("Quit", this, SLOT(close()));

    QMenu *settings = menuBar()->addMenu("Settings");
    _fullscreen = settings->addAction("Fullscreen");
    _fullscreen->setCheckable(true);
    _nohacks = settings->addAction("No hacks");
    _nohacks->setCheckable(true);

    QSignalMapper* mapper = new QSignalMapper(this);
    mapper->setMapping(_fullscreen, FULLSCREEN);
    mapper->setMapping(_nohacks, NOHACK);
    connect(_fullscreen, SIGNAL(triggered()), mapper, SLOT(map()));
    connect(_nohacks, SIGNAL(triggered()), mapper, SLOT(map()));
    connect(mapper, SIGNAL(mapped(int)), this, SLOT(handleOption(int)));

    QMenu* help = menuBar()->addMenu("Help");
    help->addAction("About",this,SLOT(about()));
}

void PcsxWindow::addSettings() {
    QHBoxLayout *hlayout = new QHBoxLayout();
    _vboxLayout->addLayout(hlayout);
    hlayout->addStretch();

    _lineEdit = new QLineEdit();
    _lineEdit->setPlaceholderText("Ex : Final fantasy X");

    _list = new QPushButton();
    _list->setIcon(QIcon("img/list.png"));
    _list->setIconSize(QSize(65,65));
    _list->setStyleSheet("QPushButton { background: none; border: none; margin: 0px; padding: 0px; } QPushButton:focus { border: none; outline: none; } ");

    _thumbnail = new QPushButton();
    _thumbnail->setIcon(QIcon("img/thumbnails.png"));
    _thumbnail->setIconSize(QSize(65,65));
    _thumbnail->setStyleSheet("QPushButton { background: none; border: none; margin: 0px; padding: 0px; } QPushButton:focus { border: none; outline: none; } ");

    hlayout->addWidget(_lineEdit);
    hlayout->addWidget(_list);
    hlayout->addWidget(_thumbnail);
    hlayout->addStretch();
    hlayout->setSpacing(0);

    connect(_lineEdit, SIGNAL(textChanged(QString)), this, SLOT(handleLineEdit(QString)));
    connect(_list, SIGNAL(clicked()), this, SLOT(handleList()));
    connect(_thumbnail, SIGNAL(clicked()), this, SLOT(handleThumbnails()));
}

void PcsxWindow::createLabels(std::vector<std::string> filesImages) {
    QGridLayout *layout = new QGridLayout();
    _vboxLayout->addLayout(layout);

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
        layout->addWidget(label, j, k);
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
    qDebug() << text;
}

void PcsxWindow::handleThumbnails() {

}

void PcsxWindow::handleList() {

}

void PcsxWindow::handleOption(int option) {
    std::string optionName = optionsName[option];
    if(_fullscreen->isChecked()) {
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
    int pid = fork();
    if (pid==0) {
//        system(command.c_str());
        exit(0);
    }
}

void PcsxWindow::about() {
    QMessageBox *msg = new QMessageBox();
    msg->setText("Author : Vimont Ludovic");
    msg->exec();
}

