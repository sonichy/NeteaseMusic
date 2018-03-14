#include "controlbar.h"
#include <QHBoxLayout>

ControlBar::ControlBar(QWidget *parent) : QWidget(parent)
{
    setStyleSheet("QSlider::sub-page:Horizontal { background-color: #9F2425; }"
                  "QSlider::add-page:Horizontal { background-color: #333333; }"
                  "QSlider::groove:Horizontal { background: transparent; height:4px; }"
                  "QSlider::handle:Horizontal { width:13px; height:13px; border:1px solid #ffffff; border-radius:7px; background:#9F2425; margin: -5px 0px -5px 0px; }"
                  "QToolTip{border-style:none; background-color:black;}");

    //setFixedHeight(50);
    QHBoxLayout *hbox = new QHBoxLayout;

    pushButton_last = new QPushButton;
    pushButton_last->setFixedSize(48,48);
    pushButton_last->setIcon(QIcon(":/last.svg"));
    pushButton_last->setIconSize(QSize(35,35));
    pushButton_last->setFocusPolicy(Qt::NoFocus);
    pushButton_last->setFlat(true);
    hbox->addWidget(pushButton_last);

    pushButton_play = new QPushButton;
    pushButton_play->setFixedSize(48,48);
    pushButton_play->setIcon(QIcon(":/play.svg"));
    pushButton_play->setIconSize(QSize(42,42));
    pushButton_play->setFocusPolicy(Qt::NoFocus);
    pushButton_play->setFlat(true);
    //connect(pushButton_play,SIGNAL(pressed()),this,SLOT(emitPlayPause()));
    hbox->addWidget(pushButton_play);

    pushButton_next = new QPushButton;
    pushButton_next->setFixedSize(48,48);
    pushButton_next->setIcon(QIcon(":/next.svg"));
    pushButton_next->setIconSize(QSize(35,35));
    pushButton_next->setFocusPolicy(Qt::NoFocus);
    pushButton_next->setFlat(true);
    hbox->addWidget(pushButton_next);

    label_song_timeNow = new QLabel;
    label_song_timeNow->setText("00:00");
    label_song_timeNow->setStyleSheet("color:white;");
    hbox->addWidget(label_song_timeNow);

    slider_progress = new QSlider;
    slider_progress->setRange(0,1000);
    slider_progress->setOrientation(Qt::Horizontal);
    slider_progress->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    slider_progress->setFocusPolicy(Qt::NoFocus);
    hbox->addWidget(slider_progress);

    label_song_duration = new QLabel;
    label_song_duration->setText("00:00");
    label_song_duration->setStyleSheet("color:white;");
    hbox->addWidget(label_song_duration);

    pushButton_mute = new QPushButton;
    pushButton_mute->setFixedSize(25,25);
    pushButton_mute->setIcon(QIcon(":/volume.svg"));
    pushButton_mute->setIconSize(QSize(20,20));
    pushButton_mute->setFocusPolicy(Qt::NoFocus);
    pushButton_mute->setFlat(true);
    hbox->addWidget(pushButton_mute);

    slider_volume = new QSlider;
    slider_volume->setOrientation(Qt::Horizontal);
    slider_volume->setRange(0,100);
    slider_volume->setValue(100);
    slider_volume->setFixedWidth(100);
    slider_volume->setFocusPolicy(Qt::NoFocus);
    hbox->addWidget(slider_volume);

    QPushButton *pushButton_loop = new QPushButton;
    pushButton_loop->setFixedSize(30,30);
    pushButton_loop->setIcon(QIcon(":/looplist.svg"));
    pushButton_loop->setIconSize(QSize(25,25));
    pushButton_loop->setFocusPolicy(Qt::NoFocus);
    pushButton_loop->setFlat(true);
    hbox->addWidget(pushButton_loop);

    pushButton_lyric = new QPushButton;
    pushButton_lyric->setFixedSize(30,30);
    pushButton_lyric->setIcon(QIcon(":/lyric.svg"));
    pushButton_lyric->setIconSize(QSize(25,25));
    pushButton_lyric->setFocusPolicy(Qt::NoFocus);
    pushButton_lyric->setFlat(true);
    pushButton_lyric->setCheckable(true);
    pushButton_lyric->setChecked(true);
    hbox->addWidget(pushButton_lyric);

    QPushButton *pushButton_playlist = new QPushButton;
    pushButton_playlist->setFixedSize(30,30);
    pushButton_playlist->setIcon(QIcon(":/playlist.svg"));
    pushButton_playlist->setIconSize(QSize(25,25));
    pushButton_playlist->setFocusPolicy(Qt::NoFocus);
    pushButton_playlist->setFlat(true);
    hbox->addWidget(pushButton_playlist);

    pushButton_fullscreen = new QPushButton;
    pushButton_fullscreen->setFixedSize(30,30);
    pushButton_fullscreen->setIcon(QIcon(":/fullscreen.svg"));
    pushButton_fullscreen->setIconSize(QSize(25,25));
    pushButton_fullscreen->setFocusPolicy(Qt::NoFocus);
    pushButton_fullscreen->setFlat(true);
    hbox->addWidget(pushButton_fullscreen);

    setLayout(hbox);
}

//void ControlBar::emitPlayPause()
//{
//    emit playPause();
//}
