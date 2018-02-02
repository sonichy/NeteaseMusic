#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//#include "apimusic.h"
#include "titlebar.h"
#include "navwidget.h"
#include "controlbar.h"
#include <QMainWindow>
#include <QStackedWidget>
#include <QTableWidget>
#include <QMediaPlayer>
#include <QTextBrowser>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    //APIMusic *apiMusic;
    TitleBar *titleBar;
    NavWidget *navWidget;
    QStackedWidget *stackedWidget;
    QWidget *toplistWidget;
    QTableWidget *tableWidget_playlist;
    QTextBrowser *textBrowser;
    ControlBar *controlBar;
    QMediaPlayer *player;
    int volume;
    void createWidgetToplist();
    QByteArray getReply(QString surl);
    QByteArray postReply(QString surl,QString spost);
    void getLyric(QString id);

private slots:
    void showNormalMaximized();
    void moveMe(QPoint point);
    void createPlaylist(long);
    void playSong(int,int);
    void durationChange(qint64 d);
    void positionChange(qint64 p);
    void stateChange(QMediaPlayer::State state);
    void volumeChange(int v);
    void playPause();    
    void setMPPosition();
    void setVolume();
    void mute();
    void itemClick(QListWidgetItem* item);
    void search();
    void lastPage();
    void nextPage();
};

#endif // MAINWINDOW_H
