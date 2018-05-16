#ifndef MYWIDGET0_H
#define MYWIDGET0_H

#include <QWidget>
#include <QResizeEvent>

class mywidget0 : public QWidget
{
    Q_OBJECT
public:
    explicit mywidget0(QWidget *parent = nullptr);

protected:
    void resizeEvent(QResizeEvent *event);
signals:
    void sign_width( int);
public slots:
};

#endif // MYWIDGET0_H
