#ifndef MYLABEL_H
#define MYLABEL_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QByteArray>
#include <qDebug>
#include "quazip.h"
#include "quazipfile.h"
#include <QResizeEvent>


//设置label比例不变

class mylabel : public QLabel
{
    Q_OBJECT
public:
    mylabel(QuaZip *,QString ,QWidget* parent = 0);
    ~mylabel();
    QPixmap *img;
    int imgwidth;
    int imgheight;

    int mywidget;//实际高
    int myheight;//实际宽

protected:
    void resizeEvent(QResizeEvent *event);


};

#endif // MYLABEL_H
