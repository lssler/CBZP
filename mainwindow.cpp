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

    //排队处理
    connect(imgwidget,SIGNAL(add_first()),this,SLOT(slot_add_first()),Qt::QueuedConnection);
    connect(imgwidget,SIGNAL(delete_first()),this,SLOT(slot_delete_first()),Qt::QueuedConnection);
    connect(imgwidget,SIGNAL(add_last()),this,SLOT(slot_add_last()),Qt::QueuedConnection);
    connect(imgwidget,SIGNAL(delete_last()),this,SLOT(slot_delete_last()),Qt::QueuedConnection);



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




    QuaZip *myfile1=new QuaZip(filedir);

    if(!myfile1->open(QuaZip::mdUnzip))  //打开文件失败
        return false;

    if(myfile!=NULL)            //判断是否已有文件打开，有关闭
    {
        myfile->close();
        free(myfile);
        myfile=NULL;
    }
    myfile=myfile1;

    ui->treeWidget->clear();           //删除之前的树目录
    page_list.clear();
    mylabel_list.clear();
    for(num=0;num<imgwidget->vlayout->count()-1;num++) //保留弹簧
        delete imgwidget->vlayout->itemAt(0)->widget();


    myfile->setCurrentFile("main");          //读取main文件
    QuaZipFile  fileR(myfile);
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
            page_list.append(*page_ls);
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
        else if(type.indexOf("/book")==0)
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
    page_first=page_now;
    page_last=page_now;

    int ls=0;
    int ls_1=imgwidget->vlayout->count()-1;

    for(ls=0;ls<ls_1;ls++)  //最后一个
    {

        delete imgwidget->vlayout->itemAt(0)->widget();
    }
    mylabel_list.clear();
    label_ls = new mylabel(myfile,page_list[page_now].dir);
    mylabel_list.append(label_ls);
    imgwidget->all_height +=label_ls->imgheight;
    imgwidget->setFixedHeight(imgwidget->all_height);
    imgwidget->vlayout->insertWidget(0,label_ls);
    label_ls->show();
    imgwidget->move(0,0);
}



void MainWindow::on_open_file_triggered()
{
    QString filedir=QFileDialog::getOpenFileName(this,tr("Open File"),":/",tr("*.cbzp")); //打开文件
    // qDebug()<<"文件："<<filedir;
    show_file(filedir);
}

void MainWindow::on_close_file_triggered()
{
    if(myfile!=NULL)
    {
        myfile->close();
        free(myfile);
        myfile=NULL;
        page_list.clear();
        mylabel_list.clear();
        ui->treeWidget->clear();
        int i=0;
        for(i=0;i<imgwidget->vlayout->count()-1;i++)
            delete imgwidget->vlayout->itemAt(i)->widget();
    }



}


void MainWindow::on_quit_triggered()
{
    exit(0);
}

//void ldimg::slot_add_last() //用于尾部添加mylabel
void MainWindow::slot_add_last() //用于尾部添加mylabel
{

    int num_ls=page_list.size()-1;
    if(page_last<num_ls)
    {
        mylabel *label_ls;
        page_last++;
        label_ls = new mylabel(myfile,page_list[page_last].dir);
        ui->treeWidget->setCurrentItem(page_list[page_last].item);

        mylabel_list.append(label_ls);
        imgwidget->all_height +=label_ls->imgheight;
        imgwidget->setFixedHeight(imgwidget->all_height);

        imgwidget->vlayout->insertWidget(imgwidget->vlayout->count()-1, label_ls);
        label_ls->show();

    }

}
void MainWindow::slot_add_first() //在首部添加mylabel
{

    if(page_first>0)
    {
        mylabel *label_ls;
        page_first--;

        label_ls = new mylabel(myfile,page_list[page_first].dir);
        ui->treeWidget->setCurrentItem(page_list[page_first].item);

        imgwidget->vlayout->insertWidget(0,label_ls);
        mylabel_list.insert(0,label_ls);
        int y_ls=0;
        if(label_ls->imgwidth > imgwidget->width())
            y_ls=imgwidget->width() * label_ls->imgheight / label_ls->imgwidth;
        else
            y_ls=label_ls->imgheight;
        y_ls=imgwidget->y() - y_ls;
        imgwidget->all_height +=label_ls->imgheight;
        imgwidget->setFixedHeight(imgwidget->all_height);
        label_ls->show();
        imgwidget->move(0,y_ls);
      }

}
void MainWindow::slot_delete_first()//删除首部
{

    page_first++;
    int y_ls;
    y_ls=imgwidget->vlayout->itemAt(0)->widget()->height();
    y_ls=imgwidget->y()+y_ls;
    imgwidget->all_height -=mylabel_list[0]->imgheight;
    mylabel_list.removeFirst();
    delete imgwidget->vlayout->itemAt(0)->widget();
    imgwidget->setFixedHeight(imgwidget->all_height);

    imgwidget->move(0,y_ls);


}
void MainWindow::slot_delete_last()//删除尾部
{

    page_last--;

    imgwidget->all_height -=mylabel_list[mylabel_list.size()-1]->imgheight;
    imgwidget->setFixedHeight(imgwidget->all_height);
    mylabel_list.removeLast();

    delete imgwidget->vlayout->itemAt(imgwidget->vlayout->count()-2)->widget();


}

