#ifndef PCSXWINDOW_H
#define PCSXWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <iostream>
#include <QString>
#include <QSlider>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include "filemanager.h"
#include "pcsxlabel.h"

enum Options { FULLSCREEN, NOHACK };
static const char * optionsName[] = { "--fullscreen ", "--nohacks " };

class PcsxWindow : public QMainWindow {
    Q_OBJECT

    public:
        explicit PcsxWindow(QWidget *parent = 0);
        void createMenu();
        void createLabels(std::vector<std::string> filesImages);
        void addSettings();
        void addSlider();

    public slots:
        void launchGame(QString gameName);
        void handleList();
        void handleThumbnails();
        void handleLabelSize(int size);
        void handleLineEdit(QString);
        void about();
        void handleOption(int option);
        void saveSettings();

    private:
        std::vector<PcsxLabel *> _labels;
        std::string _options;
        QAction *_fullscreen;
        QAction *_nohacks;
        QWidget *_screen;
        QLineEdit *_lineEdit;
        QVBoxLayout *_vboxLayout;
        QPushButton *_list;
        QPushButton *_thumbnail;
        QSlider *_slider;
};

#endif // PCSXWINDOW_H
