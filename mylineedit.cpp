#include "mylineedit.h"

MyLineEdit::MyLineEdit(QWidget *parent)
{

}

void MyLineEdit::mousePressEvent(QMouseEvent *)
{
    emit MousePressed();
}
