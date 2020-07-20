#include "eventolabel.h"

eventoLabel::eventoLabel(QWidget *parent) :
    QLabel(parent)
{

}

eventoLabel::~eventoLabel()
{

}

void eventoLabel::mousePressEvent(QMouseEvent *ev)
{
    emit clicked();
}
