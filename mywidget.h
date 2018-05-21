#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QWheelEvent>
#include <QMouseEvent>
#include "quazipfile.h"
#include <QResizeEvent>
#include <QSpacerItem>
#include <QTreeWidgetItem>
#include <QThread>


class mywidget : public QWidget
{
    Q_OBJECT
public:
    explicit mywidget(QWidget *parent = nullptr);
    QVBoxLayout *vlayout;


    QWidget *widget_ls;

    QThread *t;



    int all_height=100;  //总高度




protected:
    void wheelEvent(QWheelEvent *event);
    void mousePressEvent( QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void move_my(int ,int);       //用于移动，原move函数可以同时使用


    bool mouse_press=false;
    int press_x,press_y,my_x,my_y;

signals:
    void add_first();
    void add_last();
    void delete_first();
    void delete_last();

public slots:
    void slot_width(int);
};

#endif // MYWIDGET_H
