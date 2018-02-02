#include "mainwindow.h"
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
#include <QDir>
#include <QTextBlock>

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

    titleBar = new TitleBar;
    connect(titleBar->pushButton_search,SIGNAL(clicked(bool)),this,SLOT(search()));
    connect(titleBar->lineEdit_search,SIGNAL(returnPressed()),this,SLOT(search()));
    connect(titleBar->lineEdit_page,SIGNAL(returnPressed()),this,SLOT(search()));
    connect(titleBar->pushButton_lastPage,SIGNAL(clicked(bool)),this,SLOT(lastPage()));
    connect(titleBar->pushButton_nextPage,SIGNAL(clicked(bool)),this,SLOT(nextPage()));
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
    navWidget = new NavWidget;
    //connect(navWidget->listWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(itemClick(QListWidgetItem*)));
    connect(navWidget->listWidget,SIGNAL(currentRowChanged(int)),this,SLOT(navPage(int)));
    connect(navWidget->pushButton_songname,SIGNAL(clicked(bool)),this,SLOT(navLyric()));
    hbox->addWidget(navWidget);

    stackedWidget = new QStackedWidget;
    stackedWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    stackedWidget->addWidget(toplistWidget);

    tableWidget_playlist = new QTableWidget;
    tableWidget_playlist->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget_playlist->setSelectionMode(QAbstractItemView::SingleSelection);
    tableWidget_playlist->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableWidget_playlist->setColumnCount(6);
    tableWidget_playlist->setColumnHidden(4,true);
    tableWidget_playlist->setColumnHidden(5,true);
    QStringList header;
    header << "歌名" << "歌手" << "专辑" << "时长" << "id" << "专辑封面";
    tableWidget_playlist->setHorizontalHeaderLabels(header);
    tableWidget_playlist->horizontalHeader()->setStyleSheet("QHeaderView::section { color:white; background-color:#232326; }");
    tableWidget_playlist->verticalHeader()->setStyleSheet("QHeaderView::section { color:white; background-color:#232326; }");
    tableWidget_playlist->setStyleSheet("QTableView { color:white; selection-background-color:#e6e6e6; }");
    connect(tableWidget_playlist,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(playSong(int,int)));
    stackedWidget->addWidget(tableWidget_playlist);
    hbox->addWidget(stackedWidget);

    textBrowser = new QTextBrowser;
    textBrowser->zoomIn(10);
    //textBrowser->selectAll();
    textBrowser->setAlignment(Qt::AlignCenter);
    //textBrowser->moveCursor(QTextCursor::Start,QTextCursor::MoveAnchor);
    textBrowser->setStyleSheet("color:#ffffff;");
    stackedWidget->addWidget(textBrowser);

    vbox->addLayout(hbox);

    controlBar = new ControlBar;
    connect(controlBar->pushButton_play,SIGNAL(pressed()),this,SLOT(playPause()));
    connect(controlBar->pushButton_mute,SIGNAL(pressed()),this,SLOT(mute()));
    //connect(controlBar,SIGNAL(playPause()),this,SLOT(playPause()));
    connect(controlBar->slider_progress,SIGNAL(sliderReleased()),this,SLOT(setMPPosition()));
    connect(controlBar->slider_volume,SIGNAL(sliderReleased()),this,SLOT(setVolume()));
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

QByteArray MainWindow::postReply(QString surl,QString spost)
{
    QNetworkAccessManager *NAM = new QNetworkAccessManager;
    QNetworkRequest request;
    request.setUrl(QUrl(surl));
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    QByteArray BA_post;
    BA_post.append(spost);
    QNetworkReply *reply = NAM->post(request,BA_post);
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
    stackedWidget->setCurrentWidget(tableWidget_playlist);
    tableWidget_playlist->setRowCount(0);
    qDebug() << id;
    QString surl = QString("http://music.163.com/api/playlist/detail?id=%1").arg(id);
    qDebug() << surl;
    QJsonDocument json = QJsonDocument::fromJson(getReply(surl));
    QJsonArray tracks = json.object().value("result").toObject().value("tracks").toArray();
    //qDebug() << tracks;
    for(int i=0; i<tracks.size(); i++){
        tableWidget_playlist->insertRow(i);
        tableWidget_playlist->setItem(i,0,new QTableWidgetItem(tracks[i].toObject().value("name").toString()));
        QJsonArray artists = tracks[i].toObject().value("artists").toArray();
        QString sartists = "";
        for(int a=0; a<artists.size(); a++){
            sartists += artists[a].toObject().value("name").toString();
            if(a<artists.size()-1) sartists += ",";
        }
        tableWidget_playlist->setItem(i,1,new QTableWidgetItem(sartists));
        tableWidget_playlist->setItem(i,2,new QTableWidgetItem(tracks[i].toObject().value("album").toObject().value("name").toString()));
        int ds = tracks[i].toObject().value("duration").toInt()/1000;
        tableWidget_playlist->setItem(i,3,new QTableWidgetItem(QString("%1:%2").arg(ds/60,2,10,QLatin1Char(' ')).arg(ds%60,2,10,QLatin1Char('0'))));
        tableWidget_playlist->setItem(i,4,new QTableWidgetItem(QString::number(tracks[i].toObject().value("id").toInt())));
        tableWidget_playlist->setItem(i,5,new QTableWidgetItem(tracks[i].toObject().value("album").toObject().value("picUrl").toString()));
    }
    tableWidget_playlist->resizeColumnsToContents();
}

void MainWindow::playSong(int row, int column)
{
    Q_UNUSED(column);
    QString id = tableWidget_playlist->item(row,4)->text();
    QString surl = "http://music.163.com/song/media/outer/url?id=" + id + ".mp3";
    qDebug() << surl;
    player->setMedia(QUrl(surl));
    player->play();
    navWidget->label_songname->setText(tableWidget_playlist->item(row,0)->text() + "\n" + tableWidget_playlist->item(row,1)->text());
    getLyric(id);
    QPixmap pixmap;
    pixmap.loadFromData(getReply(tableWidget_playlist->item(row,5)->text()));
    navWidget->pushButton_songname->setIcon(QIcon(pixmap));
    pixmap.save(QDir::currentPath() + "/cover.jpg");
}

void MainWindow::durationChange(qint64 d)
{
    //qDebug() << "duration =" << d;
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

    // 歌词选行
    int hl=0;
    // 非最后一句
    for(int i=0; i<lyrics.size()-1; i++){
        if(t>lyrics.at(i).time && t<lyrics.at(i+1).time){
            //if(desktopLyric->isHidden()){
                //label_lyric->setText(lyrics.at(i).sentence);
            //}else{
                //label_lyric->setText("");
                //desktopLyric->label_lyric->setText(lyrics.at(i).sentence);
            //}
            //qDebug() << t << lyrics.at(i).time;
            hl=i;
            break;
        }
    }
    for(int a=0; a<lyrics.size(); a++){
        QTextCursor cursor(textBrowser->document()->findBlockByLineNumber(a));
        QTextBlockFormat TBF = cursor.blockFormat();
        TBF.setForeground(QBrush(Qt::white));
        //TBF.setBackground(QBrush(Qt::transparent));
        TBF.clearBackground();
        cursor.setBlockFormat(TBF);
    }
    if(lyrics.size()>0){
        QTextCursor cursor1(textBrowser->document()->findBlockByLineNumber(hl));
        QTextBlockFormat TBF1 = cursor1.blockFormat();
        TBF1.setForeground(QBrush(Qt::green));
        TBF1.setBackground(QBrush(QColor(255,255,255,80)));
        cursor1.setBlockFormat(TBF1);
        textBrowser->setTextCursor(cursor1);
    }
}

void MainWindow::volumeChange(int v)
{
    controlBar->slider_volume->setValue(v);
    controlBar->slider_volume->setToolTip(QString::number(v));
}

void MainWindow::stateChange(QMediaPlayer::State state)
{
    //qDebug() << state;
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

void MainWindow::navPage(int row)
{
    qDebug() << "nav" << row;
    switch (row) {
    case 1:
        stackedWidget->setCurrentWidget(toplistWidget);
        break;
    case 2:
        stackedWidget->setCurrentWidget(tableWidget_playlist);
        break;
    case 3:
        textBrowser->setStyleSheet("QTextBrowser{color:white; border-image:url(cover.jpg);}");
        stackedWidget->setCurrentWidget(textBrowser);
        break;
    }
}

void MainWindow::setMPPosition()
{
    player->setPosition(controlBar->slider_progress->value());
}


void MainWindow::setVolume()
{
    player->setVolume(controlBar->slider_volume->value());
}

void MainWindow::mute()
{
    if(player->isMuted()){
        player->setMuted(false);
        controlBar->pushButton_mute->setIcon(QIcon(":/volume.svg"));
        controlBar->slider_volume->setValue(volume);
    }else{
        volume = player->volume();
        player->setMuted(true);
        controlBar->pushButton_mute->setIcon(QIcon(":/mute.svg"));
        controlBar->slider_volume->setValue(0);
    }
}

void MainWindow::search()
{
    if(titleBar->lineEdit_search->text()!=""){
        int limit = 20;
        QString surl = "http://music.163.com/api/search/pc";
        QString spost = "type=1&s=" + titleBar->lineEdit_search->text() + "&limit=" + QString::number(limit) + "&offset=" + QString::number((titleBar->lineEdit_page->text().toInt()-1)*limit);
        qDebug() << surl + "?" + spost;
        //qDebug() << postReply(surl,spost);
        stackedWidget->setCurrentIndex(1);
        tableWidget_playlist->setRowCount(0);
        QJsonDocument json = QJsonDocument::fromJson(postReply(surl,spost));
        QJsonArray songs = json.object().value("result").toObject().value("songs").toArray();
        //qDebug() << songs;
        for(int i=0; i<songs.size(); i++){
            tableWidget_playlist->insertRow(i);
            tableWidget_playlist->setItem(i,0,new QTableWidgetItem(songs[i].toObject().value("name").toString()));
            tableWidget_playlist->setItem(i,1,new QTableWidgetItem(songs[i].toObject().value("artists").toArray()[0].toObject().value("name").toString()));
            tableWidget_playlist->setItem(i,2,new QTableWidgetItem(songs[i].toObject().value("album").toObject().value("name").toString()));
            int ds = songs[i].toObject().value("duration").toInt()/1000;
            tableWidget_playlist->setItem(i,3,new QTableWidgetItem(QString("%1:%2").arg(ds/60,2,10,QLatin1Char(' ')).arg(ds%60,2,10,QLatin1Char('0'))));
            tableWidget_playlist->setItem(i,4,new QTableWidgetItem(QString::number(songs[i].toObject().value("id").toInt())));
            tableWidget_playlist->setItem(i,5,new QTableWidgetItem(songs[i].toObject().value("album").toObject().value("picUrl").toString()));
        }
        tableWidget_playlist->resizeColumnsToContents();
    }
}

void MainWindow::lastPage()
{
    int page = titleBar->lineEdit_page->text().toInt();
    if(page > 1){
        titleBar->lineEdit_page->setText(QString::number(page-1));
        search();
    }
}

void MainWindow::nextPage()
{
    int page = titleBar->lineEdit_page->text().toInt();
    if(page < 99){
        titleBar->lineEdit_page->setText(QString::number(page+1));
        search();
    }
}

void MainWindow::getLyric(QString id)
{
    QString surl = "http://music.163.com/api/song/lyric?os=pc&lv=-1&kv=-1&tv=-1&id=" + id;
    qDebug() << surl;
    QJsonDocument json = QJsonDocument::fromJson(getReply(surl));
    QString slyric = json.object().value("lrc").toObject().value("lyric").toString();    

    lyrics.clear();
    QStringList line = slyric.split("\n");
    for(int i=0; i<line.size(); i++){
        if(line.at(i).contains("]")){
            QStringList strlist = line.at(i).split("]");
            //qDebug() << strlist.at(0).mid(1);
            Lyric lyric;
            QString stime = strlist.at(0).mid(1);
            //qDebug() << stime.length() << stime.indexOf(".");
            if((stime.length()-stime.indexOf("."))==3) stime += "0";
            lyric.time = QTime::fromString(stime, "mm:ss.zzz");
            lyric.sentence = strlist.at(1);
            lyrics.append(lyric);
        }
    }
    for(int i=0; i<lyrics.size(); i++){
        textBrowser->insertPlainText(lyrics.at(i).sentence + "\n");
    }
    QTextCursor cursor = textBrowser->textCursor();
    cursor.setPosition(0, QTextCursor::MoveAnchor);
    textBrowser->setTextCursor(cursor);
}

void MainWindow::navLyric()
{
    navWidget->listWidget->setCurrentRow(3);
}
