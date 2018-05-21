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
#include <QThread>



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



    QList<page> page_list;

    bool ok=true;
    bool show_file(QString);       //显示文件

    mywidget *imgwidget;
    QuaZip *myfile=NULL;
    QList<mylabel*> mylabel_list;
    int page_first=-1;
    int page_last=-1;
    QThread *new_thread;






private slots:

    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);



    void on_open_file_triggered();

    void on_close_file_triggered();

    void on_quit_triggered();

    void slot_add_first();
    void slot_delete_first();
    void slot_add_last();
    void slot_delete_last();




private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
