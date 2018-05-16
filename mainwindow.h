#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QDebug>
#include "quazip.h"
#include "quazipfile.h"
#include <QString>
#include <QVBoxLayout>
#include <QLabel>
#include "mylabel.h"
#include "mywidget.h"
#include "page.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QString,QWidget *parent = 0);
    ~MainWindow();
    QString strmid(QString *,QString , QString);  //截取两字符之间的字符


    bool file_bool=false;     //标志是否有文件打开

    QList<mylabel> label_list;
    bool ok=true;
    bool show_file(QString);       //显示文件

    mywidget *imgwidget;





private slots:

    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);



    void on_open_file_triggered();

    void on_close_file_triggered();

    void on_quit_triggered();
    void slot_setcurrentitem(QTreeWidgetItem *);



private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
