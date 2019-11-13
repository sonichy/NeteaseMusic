#ifndef NAVWIDGET_H
#define NAVWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QLabel>
#include <QDebug>
#include <QVBoxLayout>

class NavWidget : public QWidget
{
    Q_OBJECT

public:
    explicit NavWidget(QWidget *parent = nullptr);
    QListWidget *listWidget;
    QPushButton *pushButton_albumPic;
    QLabel *label_songname;

private:

signals:

public slots:

};

#endif // NAVWIDGET_H
