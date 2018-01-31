#include "mainwindow.h"
#include "titlebar.h"
#include "navwidget.h"
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
#include <QHeaderView>

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

    //apiMusic = new APIMusic;
    createWidgetToplist();
    QHBoxLayout *hbox = new QHBoxLayout;
    NavWidget *navWidget = new NavWidget;
    connect(navWidget,SIGNAL(nav(int)),this,SLOT(nav(int)));
    hbox->addWidget(navWidget);    

    stackedWidget = new QStackedWidget;
    stackedWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    stackedWidget->addWidget(toplistWidget);
    tableWidget_playlist = new QTableWidget;
    tableWidget_playlist->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget_playlist->setSelectionMode(QAbstractItemView::SingleSelection);
    tableWidget_playlist->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableWidget_playlist->setColumnCount(5);
    QStringList header;
    header << "歌名" << "歌手" << "专辑" << "时长" << "id";
    tableWidget_playlist->setHorizontalHeaderLabels(header);
    tableWidget_playlist->horizontalHeader()->setStyleSheet("QHeaderView::section{background:#232326;}");
    tableWidget_playlist->verticalHeader()->setStyleSheet("QHeaderView::section{background:#232326;}");
    tableWidget_playlist->setStyleSheet("color:white; selection-background-color:#e6e6e6;");
    connect(tableWidget_playlist,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(playSong(int,int)));
    stackedWidget->addWidget(tableWidget_playlist);
    hbox->addWidget(stackedWidget);
    vbox->addLayout(hbox);

    controlBar = new ControlBar;
    connect(controlBar,SIGNAL(playPause()),this,SLOT(playPause()));
    vbox->addWidget(controlBar);    
    widget->setLayout(vbox);

    player = new QMediaPlayer;
    connect(player,SIGNAL(durationChanged(qint64)),this,SLOT(durationChange(qint64)));
    connect(player,SIGNAL(positionChanged(qint64)),this,SLOT(positionChange(qint64)));
    connect(player,SIGNAL(volumeChanged(int)),this,SLOT(volumeChange(int)));
    //connect(player,SIGNAL(error(QMediaPlayer::Error)),this,SLOT(errorHandle(QMediaPlayer::Error)));
    connect(player,SIGNAL(stateChanged(QMediaPlayer::State)),SLOT(stateChange(QMediaPlayer::State)));
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
    tableWidget_playlist->clearContents();
    for(int i=0; i<tracks.size(); i++){
        tableWidget_playlist->insertRow(i);
        tableWidget_playlist->setItem(i,0,new QTableWidgetItem(tracks[i].toObject().value("name").toString()));
        tableWidget_playlist->setItem(i,1,new QTableWidgetItem(tracks[i].toObject().value("artists").toArray()[0].toObject().value("name").toString()));
        tableWidget_playlist->setItem(i,2,new QTableWidgetItem(tracks[i].toObject().value("album").toObject().value("name").toString()));
        int ds = tracks[i].toObject().value("duration").toInt()/1000;
        tableWidget_playlist->setItem(i,3,new QTableWidgetItem(QString("%1:%2").arg(ds/60,2,10,QLatin1Char(' ')).arg(ds%60,2,10,QLatin1Char('0'))));
        tableWidget_playlist->setItem(i,4,new QTableWidgetItem(QString::number(tracks[i].toObject().value("id").toInt())));
    }    
    tableWidget_playlist->resizeColumnsToContents();
}

void MainWindow::playSong(int row, int column)
{
    Q_UNUSED(column);
    QString surl = "http://music.163.com/song/media/outer/url?id=" + tableWidget_playlist->item(row,4)->text() + ".mp3";
    qDebug() << surl;
    player->setMedia(QUrl(surl));
    player->play();
}

void MainWindow::durationChange(qint64 d)
{
    qDebug() << "duration =" << d;
    controlBar->slider_progress->setMaximum(d);
    QTime t(0,0,0);
    t = t.addMSecs(d);
    controlBar->label_song_duration->setText(t.toString("mm:ss"));
}

void MainWindow::positionChange(qint64 p)
{    
    //qDebug() << "position =" << p;
    controlBar->slider_progress->setValue(p);
    QTime t(0,0,0);
    t = t.addMSecs(p);
    controlBar->label_song_timeNow->setText(t.toString("mm:ss"));
}

void MainWindow::volumeChange(int v)
{
    controlBar->slider_volume->setValue(v);
    controlBar->slider_volume->setToolTip(QString::number(v));
}

void MainWindow::stateChange(QMediaPlayer::State state)
{
    qDebug() << state;
    if(state == QMediaPlayer::PlayingState){
        controlBar->pushButton_play->setIcon(QIcon(":/pause.svg"));
    }
    if(state == QMediaPlayer::PausedState){
        controlBar->pushButton_play->setIcon(QIcon(":/play.svg"));
    }
    if(state == QMediaPlayer::StoppedState){
        controlBar->pushButton_play->setIcon(QIcon(":/play.svg"));
    }
}

void MainWindow::playPause()
{
    //qDebug() << "state=" << player->state();
    if(player->state() == QMediaPlayer::PlayingState){
        player->pause();
    }else if(player->state() == QMediaPlayer::PausedState){
        player->play();
    }else if(player->state() == QMediaPlayer::StoppedState){
        player->play();
    }
}

void MainWindow::nav(int i)
{
    qDebug() << "nav" << i;
    switch (i) {
    case 1:
        stackedWidget->setCurrentIndex(0);
        break;
    }
}
