#include "mywidget.h"
#include <QDebug>

mywidget::mywidget(QWidget *parent) : QWidget(parent)
{

    vlayout=new QVBoxLayout;
    vlayout->setSpacing(0);
    vlayout->setContentsMargins(0,0,0,0);

    //t=new QThread;
    //sendsign =new send(0);
    //t->start();
    //sendsign->moveToThread(t);

    mywidget::setLayout(vlayout);
    mywidget::setFixedHeight(all_height);
    widget_ls = new QWidget;
    vlayout->addWidget(widget_ls);
    widget_ls->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);


    mywidget::move(0,0);
}



void mywidget::move_my(int x, int y)
{

    int ph=mywidget::parentWidget()->height();
    int ph1=ph+500;

    int ls_x=mywidget::x()+x;
    int ls_y=mywidget::y()+y;
    if(vlayout->count()>1)
    {
        if(y>0)   //向下移动
        {
            int y_last_up=mywidget::y()+all_height - vlayout->itemAt(vlayout->count()-2)->widget()->height() - widget_ls->height();
            if(ls_y>-500 )
                emit add_first();

            if(ls_y>500)
                y=0;
            if(y_last_up>ph1 )
                emit delete_last();

        }
        else if(y<0)                   //向上移动
        {


            int y_first_down=mywidget::y()+vlayout->itemAt(0)->widget()->height();
            int y_last_down=mywidget::y()+all_height-widget_ls->height();


            if(y_last_down < ph1 )
            {
                emit add_last();
                //sendsign->send_add_last();
            }

            if(y_first_down<-500 )
            {
                emit delete_first();
            }



            if(y_last_down < 500 )
                y=0;

        }
    }
    else
    {
        x=0;
        y=0;
    }

    mywidget::move(0,mywidget::y()+y);

}

void mywidget::wheelEvent(QWheelEvent *event)
{

    int y=event->delta();


    mywidget::move_my(0,y);
    event->accept();

}

void mywidget::mousePressEvent( QMouseEvent * event )
{
    if(event->button() == Qt::LeftButton)
    {
        mouse_press = true;
        press_x=event->globalPos().x();
        press_y=event->globalPos().y();

    }
    event->ignore();
}
void mywidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(mouse_press)
        mouse_press=false;
    event->ignore();
}

void mywidget::mouseMoveEvent(QMouseEvent *event)//鼠标按住移动
{
    if(mouse_press==true)
    {
        int x=event->globalPos().x()-press_x;
        int y=event->globalPos().y()-press_y;
        press_x=event->globalPos().x();
        press_y=event->globalPos().y();
        move_my(x,y);
    }
    event->ignore();
}

void mywidget::slot_width(int w)
{
    mywidget::setFixedWidth(w);
}
