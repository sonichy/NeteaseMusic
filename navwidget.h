#ifndef NAVWIDGET_H
#define NAVWIDGET_H

#include <QWidget>
#include <QListWidget>

class NavWidget : public QWidget
{
    Q_OBJECT
public:
    explicit NavWidget(QWidget *parent = nullptr);

private:
    QListWidget *listWidget;

signals:
    void nav(int);

public slots:
    void itemClick(QListWidgetItem* item);
};

#endif // NAVWIDGET_H
