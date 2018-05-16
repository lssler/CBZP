#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString filedir="unfile";
    if(argc>1)                   //判断是否打开文件
    {
        filedir=QString::fromLocal8Bit(argv[1]);
        filedir.replace("\\","/");
    }

    else
    {
        filedir="unfile";
        qDebug()<<"未直接打开文件";       //赋初值用于比较以判断是否直接打开文件
    }

    MainWindow w(filedir);
    w.show();

    return a.exec();
}
