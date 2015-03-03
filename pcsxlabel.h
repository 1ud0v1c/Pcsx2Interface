#ifndef PCSXLABEL_H
#define PCSXLABEL_H

#include <QLabel>
#include <QString>

class PcsxLabel : public QLabel {
    Q_OBJECT

    public:
        explicit PcsxLabel(const QString& text ="", QWidget * parent = 0);
        ~PcsxLabel();

    protected:
        void mousePressEvent(QMouseEvent *ev);

    signals:
        void clicked(QString gameName);

    private:
        QString _filename;
};

#endif // PCSXLABEL_H
