#include "toplistitem.h"
#include <QVBoxLayout>
#include <QNetworkAccessManager>

ToplistItem::ToplistItem(QWidget *parent) : QWidget(parent)
{
    setFixedSize(120,120);
    QVBoxLayout *vbox = new QVBoxLayout;
    pushButton = new QPushButton;
    pushButton->setFixedSize(QSize(100,100));
    pushButton->setFocusPolicy(Qt::NoFocus);
    pushButton->setFlat(true);
    pushButton->setIconSize(pushButton->size());
    pushButton->setCursor(Qt::PointingHandCursor);
    connect(pushButton,SIGNAL(pressed()),this,SLOT(sendId()));
    vbox->addWidget(pushButton);
    setLayout(vbox);
}

void ToplistItem::setImage(QString surl)
{
    QNetworkAccessManager *NAM = new QNetworkAccessManager;
    QNetworkRequest request;
    request.setUrl(QUrl(surl));
    NAM->get(request);
    connect(NAM, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyImage(QNetworkReply*)));
}

void ToplistItem::replyImage(QNetworkReply *reply)
{
    QPixmap pixmap;
    pixmap.loadFromData(reply->readAll());
    pushButton->setIcon(QIcon(pixmap));
    reply->deleteLater();
}

void ToplistItem::sendId()
{
    emit send(id);
}
