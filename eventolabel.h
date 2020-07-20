#ifndef EVENTOLABEL_H
#define EVENTOLABEL_H

#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QEvent>

class eventoLabel : public QLabel
{
    Q_OBJECT

public:
    explicit eventoLabel(QWidget *parent = 0);
    ~eventoLabel();


signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent* event);

private:

};

#endif // EVENTOLABEL_H
