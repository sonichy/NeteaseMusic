#include "mainwindow.h"
#include "titlebar.h"
#include "navwidget.h"
#include "controlbar.h"
#include "toplistitem.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QTableWidgetItem>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowIcon(QIcon(":/icon.svg"));
    setWindowFlags(Qt::FramelessWindowHint);
    resize(1000,700);
    move((QApplication::desktop()->width()-width())/2,(QApplication::desktop()->height()-height())/2);
    setStyleSheet("background-color:#232326;");

    QWidget *widget = new QWidget;
    setCentralWidget(widget);
    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->setSpacing(0);
    vbox->setContentsMargins(0,0,0,0);

    TitleBar *titleBar = new TitleBar;
    connect(titleBar->pushButton_minimize,SIGNAL(clicked(bool)),this,SLOT(showMinimized()));
    connect(titleBar->pushButton_maximize,SIGNAL(clicked(bool)),this,SLOT(showNormalMaximized()));
    connect(titleBar->pushButton_close,SIGNAL(clicked(bool)),qApp,SLOT(quit()));
    connect(titleBar,SIGNAL(moveMainWindow(QPoint)),this,SLOT(moveMe(QPoint)));
    vbox->addWidget(titleBar);

    QLabel *label_titleBar_bottom = new QLabel;
    label_titleBar_bottom->setFixedHeight(2);
    label_titleBar_bottom->setStyleSheet("background-color:#9F2425");
    vbox->addWidget(label_titleBar_bottom);

    apiMusic = new APIMusic;
    createWidgetToplist();
    QHBoxLayout *hbox = new QHBoxLayout;
    NavWidget *navWidget = new NavWidget;
    hbox->addWidget(navWidget);
    //hbox->addStretch();
    stackedWidget = new QStackedWidget;
    stackedWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    stackedWidget->addWidget(toplistWidget);
    QTableWidget *tableWidget_playlist = new QTableWidget;
    tableWidget_playlist->setColumnCount(5);
    stackedWidget->addWidget(tableWidget_playlist);
    hbox->addWidget(stackedWidget);
    vbox->addLayout(hbox);

    ControlBar *controlBar = new ControlBar;
    vbox->addWidget(controlBar);
    widget->setLayout(vbox);
}

MainWindow::~MainWindow()
{
}

void MainWindow::moveMe(QPoint point)
{
    move(point);
}

void MainWindow::createWidgetToplist()
{
    toplistWidget = new QWidget;
    QString surl = "http://music.163.com/api/toplist";
    QJsonDocument json = QJsonDocument::fromJson(getReply(surl));
    qDebug() << surl;
    QGridLayout *gridLayout = new QGridLayout(toplistWidget);
    QJsonArray list = json.object().value("list").toArray();
    //qDebug() << list;
    for(int r=0; r< list.size()/5; r++){
        for(int c=0; c<5; c++){
            QString coverImgUrl = list[r*5+c].toObject().value("coverImgUrl").toString();
            ToplistItem *toplistItem = new ToplistItem;
            toplistItem->setImage(coverImgUrl);
            toplistItem->id = list[r*5+c].toObject().value("id").toDouble();
            connect(toplistItem,SIGNAL(send(long)),this,SLOT(createPlaylist(long)));
            gridLayout->addWidget(toplistItem,r,c);
        }
    }
//    QJsonObject artistToplist = json.object().value("artistToplist").toObject();
//    QString coverUrl = artistToplist.value("coverUrl").toString();
//    ToplistItem *toplistItem = new ToplistItem;
//    toplistItem->setImage(coverUrl);
//    toplistItem->id = artistToplist.value("id").toDouble();
//    connect(toplistItem,SIGNAL(send(long)),this,SLOT(createPlaylist(long)));
//    gridLayout->addWidget(toplistItem,list.size()/5,0);
}

QByteArray MainWindow::getReply(QString surl)
{
    QNetworkAccessManager *NAM = new QNetworkAccessManager;
    QNetworkRequest request;
    request.setUrl(QUrl(surl));
    QNetworkReply *reply = NAM->get(request);
    QEventLoop loop;
    connect(reply,&QNetworkReply::finished,&loop,&QEventLoop::quit);
    loop.exec();
    reply->deleteLater();
    return reply->readAll();
}

void MainWindow::showNormalMaximized()
{
    //qDebug() << "isMaximized=" << isMaximized();
    if(isMaximized()){
        showNormal();
    }else{
        showMaximized();
    }
}

void MainWindow::createPlaylist(long id)
{
    stackedWidget->setCurrentIndex(1);
    qDebug() << id;
    QString surl = QString("http://music.163.com/api/playlist/detail?id=%1").arg(id);
    qDebug() << surl;
    QJsonDocument json = QJsonDocument::fromJson(getReply(surl));
    QJsonArray tracks = json.object().value("result").toObject().value("tracks").toArray();
    //qDebug() << tracks;
    //tableWidget_playlist->setRowCount(0);
    for(int i=0; i<tracks.size(); i++){
        tableWidget_playlist->insertRow(i);
        tableWidget_playlist->setItem(i,0,new QTableWidgetItem(tracks[i].toObject().value("name").toString()));
        //qDebug() << i << tracks[i].toObject().value("name").toString();
    }
}
