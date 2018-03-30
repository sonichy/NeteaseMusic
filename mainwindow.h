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
#include <QScrollArea>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QLabel *label_titleBar_bottom;
    TitleBar *titleBar;
    NavWidget *navWidget;
    QStackedWidget *stackedWidget;   
    QScrollArea *rankScrollArea;
    QWidget *playlistWidget;
    QLabel *label_playlistTitle;
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
    QPushButton *pushButton_fontcolor, *pushButton_path;

private slots:
    void showNormalMaximize();
    void moveMe(QPoint point);
    void createPlaylist(long id, QString name);
    void playSong(int,int);
    void durationChange(qint64 d);
    void positionChange(qint64 p);
    void stateChange(QMediaPlayer::State state);
    void volumeChange(int v);
    void playPause();    
    void sliderProgressMoved(int p);
    void sliderVolumeMoved(int v);
    void mute();    
    void navPage(int row);
    void preSearch();
    void search();
    void lastPage();
    void nextPage();
    void swapLyric();
    void hideLyric();
    void showHideLyric(bool);
    void dialogSet();
    void chooseFont();
    void chooseFontColor();
    void openDownloadPath();
    void chooseDownloadPath();
    void playLast();
    void playNext();
    void enterFullscreen();
    void exitFullscreen();
    void dialogDownload();
    void download(QString surl, QString filepath);
    void updateProgress(qint64 bytesReceived, qint64 bytesTotal);
};

#endif // MAINWINDOW_H
