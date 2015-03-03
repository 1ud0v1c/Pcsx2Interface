#include "pcsxwindow.h"
#include <QPixmap>
#include <QGridLayout>
#include <QDockWidget>
#include <QDebug>
#include <cstdlib>
#include <unistd.h>

PcsxWindow::PcsxWindow(QWidget *parent) : QMainWindow(parent) {
    _screen = new QWidget();
    setCentralWidget(_screen);

    _vboxLayout = new QVBoxLayout();
    _screen->setLayout(_vboxLayout);

    addSettings();

    FileManager _fileManager = FileManager("data/");
    createLabels(_fileManager.getFilesImages(), _fileManager.getFilesISOs());

    addSlider();

    setMinimumSize(600, 600);
    setWindowTitle(tr("PCSX Interface"));
}

void PcsxWindow::addSettings() {
    QHBoxLayout *hlayout = new QHBoxLayout();
    _vboxLayout->addLayout(hlayout);
    hlayout->addStretch();

    _list = new QPushButton();
    _list->setIcon(QIcon("img/list.png"));
    _list->setIconSize(QSize(65,65));
    _list->setStyleSheet("QPushButton { background: none; border: none; margin: 0px; padding: 0px; } QPushButton:focus { border: none; outline: none; } ");

    _thumbnail = new QPushButton();
    _thumbnail->setIcon(QIcon("img/thumbnails.png"));
    _thumbnail->setIconSize(QSize(65,65));
    _thumbnail->setStyleSheet("QPushButton { background: none; border: none; margin: 0px; padding: 0px; } QPushButton:focus { border: none; outline: none; } ");

    hlayout->addWidget(_list);
    hlayout->addWidget(_thumbnail);
    hlayout->addStretch();
    hlayout->setSpacing(0);

    connect(_list, SIGNAL(clicked()), this, SLOT(handleList()));
    connect(_thumbnail, SIGNAL(clicked()), this, SLOT(handleThumbnails()));
}

void PcsxWindow::createLabels(std::vector<std::string> filesImages, std::vector<std::string> filesISO) {
    QGridLayout *layout = new QGridLayout();
    _vboxLayout->addLayout(layout);

    unsigned int j = 0;
    for (unsigned int i = 0; i < filesImages.size(); ++i) {
        QPixmap pix(filesImages[i].c_str());
        PcsxLabel *label = new PcsxLabel(filesISO[i].c_str());
        label->setPixmap(pix);
        if(i % 4 == 0) {
            j++;
        }
        label->setMaximumHeight(400);
        label->setScaledContents(true);
        layout->addWidget(label, j, i);
        _labels.push_back(label);
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

void PcsxWindow::handleThumbnails() {

}

void PcsxWindow::handleList() {

}

void PcsxWindow::launchGame(QString gameName) {
    std::string command = "pcsx2 \""+gameName.toStdString()+"\" --nogui";
    qDebug() << command.c_str();
    int pid = fork();
    if (pid==0) {
        system(command.c_str());
        exit(0);
    }
}

