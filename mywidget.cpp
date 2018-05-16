#include "mywidget.h"
#include <QDebug>

mywidget::mywidget(QWidget *parent) : QWidget(parent)
{
    vlayout=new QVBoxLayout;
    vlayout->setSpacing(0);
    vlayout->setContentsMargins(0,0,0,0);
    mywidget::setLayout(vlayout);



    widget_ls =new QWidget;
    vlayout->addWidget(widget_ls);
    widget_ls->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    mywidget::setFixedHeight(all_height);
    mywidget::move(0,0);
}



void mywidget::move_my(int x, int y)
{

    int ph=mywidget::parentWidget()->height();

    ph=ph+100;

    if(x>w_add*2)
        x=w_add*2;
    else if(x<0-w_add*2)
        x=0-w_add*2;
    if(y>mywidget::y())   //向下移动
    {
        int y_last_up=y+all_height - widget_ls->height() - vlayout->itemAt(vlayout->count()-2)->widget()->height();
        if(y>-100 && page_first>0)
            y=addfirst(y);
        if(y_last_up>ph)
            deletelast();
    }
    else                   //向上移动
    {

        if(vlayout->count()>1)
        {
            int y_first_down=y+vlayout->itemAt(0)->widget()->height();
            int y_last_down=y+all_height - widget_ls->height();
            int num_ls=page_list.size() -2;
            if(y_first_down<-100)
                y=deletefirst(y);
            if(y_last_down<ph && page_last<num_ls)
            {

                addlast();
            }
        }
    }

    mywidget::move(x,y);

}

void mywidget::wheelEvent(QWheelEvent *event)
{

    int angle=event->delta();

    angle=angle/10;
    int sx=mywidget::x();
    int sy=mywidget::y();
    sy=sy+angle;
    mywidget::move_my(sx,sy);
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
        int x_ls=event->globalPos().x()-press_x;
        int y_ls=event->globalPos().y()-press_y;
        int x=mywidget::x()+x_ls;
        int y=mywidget::y()+y_ls;
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

void mywidget::addlast() //用于处尾部添加mylabel
{


    mylabel *label_ls;
    page_last++;
    label_ls = new mylabel(myfile,page_list[page_last].dir);
    mylabel_list.append(label_ls);
    all_height=all_height+label_ls->imgheight;


    mywidget::setFixedHeight(all_height);

    vlayout->insertWidget(vlayout->count()-1,label_ls);

    emit sign_treeitemnow(page_list[page_last].item);
    label_ls->show();



}
int mywidget::addfirst(int y) //在首部添加mylabel
{

    mylabel *label_ls;
    page_first--;
    label_ls = new mylabel(myfile,page_list[page_first].dir);
    mylabel_list.insert(0,label_ls);
    all_height=all_height+label_ls->imgheight;

    mywidget::setFixedHeight(all_height);
    vlayout->insertWidget(0,label_ls);

    int y_ls=0;
    if(label_ls->imgwidth > mywidget::width())
    {
        y_ls=mywidget::width() * label_ls->imgheight / label_ls->imgwidth;
        qDebug()<<label_ls->imgwidth;
        qDebug()<<y_ls;

    }
    else
        y_ls=label_ls->imgheight;
    y=y-y_ls;

    label_ls->show();

    emit sign_treeitemnow(page_list[page_first].item);
    return y;

}
int mywidget::deletefirst(int y)//删除首部
{

    page_first++;
    int y_ls;
    y_ls=vlayout->itemAt(0)->widget()->height();
    y=y+y_ls;

    all_height=all_height-mylabel_list[0]->imgheight;
    mylabel_list.removeFirst();

    mywidget::setFixedHeight(all_height);
    delete vlayout->itemAt(0)->widget();
    mywidget::move(mywidget::x(),-100);
    return y;

}
void mywidget::deletelast()//删除尾部
{
    finish=false;
    page_last--;



    all_height=all_height-mylabel_list[mylabel_list.count()-2]->imgheight;
    mylabel_list.removeLast();

    mywidget::resize(mywidget::width(),all_height);
    delete vlayout->itemAt(vlayout->count()-2)->widget();
    finish=true;
}
