#ifndef NAVWIDGET_H
#define NAVWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QPushButton>

class NavWidget : public QWidget
{
    Q_OBJECT

public:
    explicit NavWidget(QWidget *parent = nullptr);
    QListWidget *listWidget;
    QPushButton *pushButton_songname;

private:


signals:    

public slots:

};

#endif // NAVWIDGET_H
