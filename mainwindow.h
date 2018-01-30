#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "apimusic.h"
#include <QMainWindow>
#include <QStackedWidget>
#include <QTableWidget>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    APIMusic *apiMusic;
    QStackedWidget *stackedWidget;
    QWidget *toplistWidget;
    QTableWidget *tableWidget_playlist;
    void createWidgetToplist();
    QByteArray getReply(QString surl);    

private slots:
    void showNormalMaximized();
    void moveMe(QPoint point);
    void createPlaylist(long);
};

#endif // MAINWINDOW_H
