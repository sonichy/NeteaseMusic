#ifndef CONTROLBAR_H
#define CONTROLBAR_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QSlider>
#include <QHBoxLayout>

class ControlBar : public QWidget
{
    Q_OBJECT
public:
    explicit ControlBar(QWidget *parent = nullptr);
    QSlider *slider_progress, *slider_volume;
    QPushButton *pushButton_last, *pushButton_play, *pushButton_next, *pushButton_mute, *pushButton_lyric, *pushButton_download, *pushButton_fullscreen;
    QLabel *label_song_timeNow, *label_song_duration;

signals:
    //void playPause();

private slots:
    //void emitPlayPause();
};

#endif // CONTROLBAR_H