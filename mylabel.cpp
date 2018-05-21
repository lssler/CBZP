#include "mylabel.h"
#include <QBoxLayout>

mylabel::mylabel(QuaZip *myfile,QString dir,QWidget *parent) :
    QLabel(parent)
{
    myfile->setCurrentFile(dir);
    QuaZipFile  fileR(myfile);
    fileR.open(QIODevice::ReadOnly);

    img =new QPixmap;
    img->loadFromData(fileR.readAll());
    fileR.close();

    imgwidth=img->width();
    imgheight=img->height();
    img->scaled(imgwidth,imgheight,Qt::KeepAspectRatio,Qt::SmoothTransformation);//按比例缩放
    mylabel::setPixmap(*img);
    mylabel::setAlignment(Qt::AlignHCenter);  //图片放在中间

}



void mylabel::resizeEvent(QResizeEvent *event)
{
    event->ignore();
    if(imgwidth>mylabel::width())
    {
        mylabel::setScaledContents(true);
        mywidget=mylabel::width();
        myheight=mywidget*imgheight/imgwidth;
        mylabel::setFixedHeight(myheight);
    }
    else
    {
        mylabel::setScaledContents(false);
        mywidget=mylabel::width();
        myheight=imgheight;
        mylabel::setFixedHeight(imgheight);
    }
    event->accept();
}

mylabel::~mylabel()
{
    delete img;
    //delete mylabel;
}
