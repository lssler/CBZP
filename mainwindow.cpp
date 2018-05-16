#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QLabel>
#include <QList>



MainWindow::MainWindow(QString filedir,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);


    this->setWindowTitle("CBZP");
    QList<int>list;
    list<<100<<500;
    ui->splitter->setSizes(list);

    imgwidget=new mywidget(ui->widget);


    connect(ui->widget,SIGNAL(sign_width(int)),imgwidget,SLOT(slot_width(int)));
    connect(imgwidget,SIGNAL(sign_treeitemnow(QTreeWidgetItem*)),this,SLOT(slot_setcurrentitem(QTreeWidgetItem *)));

    imgwidget->move(0,0);
    show_file(filedir);


}

MainWindow::~MainWindow()
{
    delete ui;
}


bool MainWindow::show_file(QString filedir)
{


    filedir.replace("\\","/");

    QString type="null",dir,name;
    int num1=0,num2=0,num=0;




    QuaZip *myfile=new QuaZip(filedir);

    if(!myfile->open(QuaZip::mdUnzip))  //打开文件失败
        return false;

    if(imgwidget->myfile!=NULL)            //判断是否已有文件打开，有关闭
    {
        imgwidget->myfile->close();
        free(imgwidget->myfile);
        imgwidget->myfile=NULL;
    }
    imgwidget->myfile=myfile;

    ui->treeWidget->clear();           //删除之前的树目录
    imgwidget->page_list.clear();
    for(num1=0;num1<imgwidget->vlayout->count()-1;num1++) //保留弹簧
        delete imgwidget->vlayout->itemAt(0)->widget();


    imgwidget->myfile->setCurrentFile("main");          //读取main文件
    QuaZipFile  fileR(imgwidget->myfile);
    fileR.open(QIODevice::ReadOnly);
    QString *str=new QString(fileR.readAll());
    fileR.close();




    this->setWindowTitle(strmid(str,"<title>","</title"));  //设置程序

    str->remove(0,str->indexOf("<book>")+6);
    type="book";
    int item_grade=0;
    QTreeWidgetItem *item_ls,*item_ls1;
    page *page_ls;
    int page_num=0;
    while(type.indexOf("/book")!=0)  //判断是否存在书籍
    {
        num1=str->indexOf("<");
        num2=str->indexOf(">");

        type=str->mid(num1+1,num2-num1-1);
        str->remove(0,num2+1);

        if(type.indexOf("img")==0)
        {
            num1=type.indexOf("\"");
            num2=type.lastIndexOf("\"");
            dir=type.mid(num1+1,num2-num1-1);

            page_ls=new page(item_ls,dir);
            imgwidget->page_list.append(*page_ls);
            page_num++;

        }
        else if(type.indexOf("item")==0)
        {

            num1=type.indexOf("\"");
            num2=type.lastIndexOf("\"");
            name=type.mid(num1+1,num2-num1-1);

            if(item_grade>0)   //该item不在最低层
            {
                item_ls1=new QTreeWidgetItem(item_ls);
                item_ls->addChild(item_ls1);
            }
            else
            {
                item_ls1=new QTreeWidgetItem(ui->treeWidget);
            }
            item_ls1->setData(0,0,name);
            item_ls1->setData(1,0,page_num);

            item_ls=item_ls1;

            item_grade++;
        }
        else if(type.indexOf("/item")==0)
        {
            item_grade--;
            if(item_grade>0)
                item_ls=item_ls->parent();
        }
        else
            break;
    }

    return true;
}


QString MainWindow::strmid(QString *str,QString str1,QString str2)
{
    int ls1,ls2,ls3;
    QString str3;
    ls1=str->indexOf(str1);
    ls2=str->indexOf(str2);
    ls3=str1.size();
    str3 = str->mid(ls1+ls3,ls2-ls1-ls3);
    str3.trimmed();
    return str3;
}

void MainWindow::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    mylabel *label_ls;
    int page_now=item->data(1,0).toInt(&ok);
    imgwidget->page_first=page_now;
    imgwidget->page_last=page_now;
    int ls=0;
    for(ls=0;ls<imgwidget->vlayout->count()-1;ls++)  //保留弹簧
        delete imgwidget->vlayout->itemAt(0)->widget();

    label_ls = new mylabel(imgwidget->myfile,imgwidget->page_list[page_now].dir);
    imgwidget->mylabel_list.append(label_ls);

    imgwidget->vlayout->insertWidget(0,label_ls);
    imgwidget->all_height=imgwidget->all_height+label_ls->imgheight;
    imgwidget->setFixedHeight(imgwidget->all_height);
    label_ls->show();
    imgwidget->move(0,0);
}



void MainWindow::on_open_file_triggered()
{
    QString filedir=QFileDialog::getOpenFileName(this,tr("打开文件"),":/",tr("*.cbzp"));
    // qDebug()<<"文件："<<filedir;
    show_file(filedir);
}

void MainWindow::on_close_file_triggered()
{
    if(imgwidget->myfile!=NULL)
    {
        imgwidget->myfile->close();
        free(imgwidget->myfile);
        imgwidget->myfile=NULL;
        imgwidget->page_list.clear();
        ui->treeWidget->clear();
        int i=0;
        for(i=0;i<imgwidget->vlayout->count()-1;i++)  //保留弹簧
            delete imgwidget->vlayout->itemAt(i)->widget();
    }



}

void MainWindow::slot_setcurrentitem(QTreeWidgetItem *item)
{
    ui->treeWidget->setCurrentItem(item);
}

void MainWindow::on_quit_triggered()
{
    exit(0);
}
