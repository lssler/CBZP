#ifndef PAGE_H
#define PAGE_H

#include <QTreeWidgetItem>
#include <QString>

class page
{
public:
    page(QTreeWidgetItem *,QString);
    QTreeWidgetItem *item;
    QString dir;
};

#endif // PAGE_H
