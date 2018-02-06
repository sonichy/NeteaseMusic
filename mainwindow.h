#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "titlebar.h"
#include "navwidget.h"
#include "controlbar.h"
#include "lyricwidget.h"
#include <QMainWindow>
#include <QStackedWidget>
#include <QTableWidget>
#include <QMediaPlayer>
#include <QTextBrowser>
#include <QTime>

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
    LyricWidget *lyricWidget;    
    int volume;
    void createWidgetToplist();
    QByteArray getReply(QString surl);
    QByteArray postReply(QString surl,QString spost);
    void getLyric(QString id);
    struct Lyric{
        QTime time;
        QString sentence;
    };
    QList<Lyric> lyrics;
    QLineEdit *lineEdit_downloadPath;
    QString downloadPath;
    QString readSettings(QString path, QString group, QString key);
    void writeSettings(QString path, QString group, QString key, QString value);
    QPushButton *pushButton_fontcolor;

private slots:
    void showNormalMaximize();
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
    void navPage(int row);
    void search();
    void lastPage();
    void nextPage();
    void swapLyric();
    void hideLyric();
    void showHideLyric(bool);
    void on_action_settings_triggered();
    void chooseFont();
    void chooseFontColor();
    void chooseDownloadPath();
};

#endif // MAINWINDOW_H
