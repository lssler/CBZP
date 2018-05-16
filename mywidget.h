#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QWheelEvent>
#include <QMouseEvent>
#include "quazipfile.h"
#include <QResizeEvent>
#include "quazip.h"
#include "quazipfile.h"
#include "page.h"
#include "mylabel.h"
#include <QSpacerItem>
#include <QTreeWidgetItem>

class mywidget : public QWidget
{
    Q_OBJECT
public:
    explicit mywidget(QWidget *parent = nullptr);
    QVBoxLayout *vlayout;
    QuaZip *myfile=NULL;

    bool finish=true ;//判断执行是否完成

    QWidget *widget_ls;

    QList<page > page_list;
    QList<mylabel *>mylabel_list;
    int page_first=0,page_last=0;

    int w_add=0;

    int all_height=100;



protected:
    void wheelEvent(QWheelEvent *event);
    void mousePressEvent( QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void move_my(int ,int);       //用于移动，原move函数可以同时使用

    void addlast(); //用于处尾部添加mylabel
    int addfirst(int); //在首部添加mylabel
    int deletefirst(int);//删除首部
    void deletelast();//删除尾部

    bool mouse_press=false;
    int press_x,press_y,my_x,my_y;

signals:
    void sign_treeitemnow(QTreeWidgetItem *);

public slots:
    void slot_width(int);
};

#endif // MYWIDGET_H
