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
