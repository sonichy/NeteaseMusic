#ifndef TOPLISTITEM_H
#define TOPLISTITEM_H

#include <QWidget>
#include <QPushButton>
#include <QNetworkReply>

class ToplistItem : public QWidget
{
    Q_OBJECT
public:
    explicit ToplistItem(QWidget *parent = nullptr);
    void setImage(QString surl);
    long id;
    QString name;

private:
    QPushButton *pushButton;

signals:
    void send(long id,QString name);

private slots:
    void replyImage(QNetworkReply *reply);
    void itemPressed();
};

#endif // TOPLISTITEM_H
