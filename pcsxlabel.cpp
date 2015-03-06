#include "pcsxlabel.h"
#include <QDebug>

PcsxLabel::PcsxLabel(const QString& text, QWidget * parent) : QLabel(parent) {
    setText(text);
    _filename = text;
}

PcsxLabel::~PcsxLabel() {
}

void PcsxLabel::mousePressEvent(QMouseEvent * event) {
  emit clicked(_filename);
}

void PcsxLabel::setPixmap(const QPixmap &pixmap) {
    _pixmap = pixmap;
    QLabel::setPixmap(pixmap);
}

void PcsxLabel::resizeEvent(QResizeEvent * event) {
    QLabel::setPixmap(_pixmap.scaled(this->size(),Qt::KeepAspectRatio, Qt::SmoothTransformation));
}
