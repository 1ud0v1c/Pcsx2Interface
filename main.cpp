#include "pcsxwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PcsxWindow w;
    w.show();

    return a.exec();
}
