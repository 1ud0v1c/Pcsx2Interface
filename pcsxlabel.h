#ifndef PCSXLABEL_H
#define PCSXLABEL_H

#include <QLabel>
#include <QString>
#include <QPixmap>

class PcsxLabel : public QLabel {
    Q_OBJECT

    public:
        explicit PcsxLabel(const QString& text ="", QWidget * parent = 0);
        ~PcsxLabel();

    protected:
        void mousePressEvent(QMouseEvent *event);

    signals:
        void clicked(QString gameName);

    public slots:
        void resizeEvent(QResizeEvent *event);
        void setPixmap(const QPixmap &pixmap);

    private:
        QString _filename;
        QPixmap _pixmap;
};

#endif // PCSXLABEL_H
