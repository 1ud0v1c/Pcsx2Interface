#ifndef PCSXWINDOW_H
#define PCSXWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <iostream>
#include <QString>
#include <QSlider>
#include <QVBoxLayout>
#include "pcsxlabel.h"
#include <QPushButton>
#include "filemanager.h"

class PcsxWindow : public QMainWindow {
    Q_OBJECT

    public:
        explicit PcsxWindow(QWidget *parent = 0);
        void createLabels(std::vector<std::string> filesImages, std::vector<std::string> filesISO);
        void addSettings();
        void addSlider();

    public slots:
        void launchGame(QString gameName);
        void handleList();
        void handleThumbnails();
        void handleLabelSize(int size);

    private:
        std::vector<PcsxLabel *> _labels;
        QWidget *_screen;
        QVBoxLayout *_vboxLayout;
        QPushButton *_list;
        QPushButton *_thumbnail;
        QSlider *_slider;
};

#endif // PCSXWINDOW_H
