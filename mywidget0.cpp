#include "mywidget0.h"

mywidget0::mywidget0(QWidget *parent) : QWidget(parent)
{

}

void mywidget0::resizeEvent(QResizeEvent *event)
{
    event->ignore();
    emit sign_width(mywidget0::width());
}
