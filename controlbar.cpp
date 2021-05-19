#include "controlbar.h"

ControlBar::ControlBar(QWidget *parent) : QWidget(parent)
{
    setStyleSheet("QSlider::sub-page:Horizontal { background-color: #9F2425; }"
                  "QSlider::add-page:Horizontal { background-color: #333333; }"
                  "QSlider::groove:Horizontal { background: transparent; height:4px; }"
                  "QSlider::handle:Horizontal { width:13px; height:13px; border:1px solid #ffffff; border-radius:7px; background:#9F2425; margin: -5px 0px -5px 0px; }"
                  "QToolTip{border-style:none; background-color:black;}");

    //setFixedHeight(50);
    QHBoxLayout *hbox = new QHBoxLayout;
    hbox->addSpacing(15);

    pushButton_last = new QPushButton;
    pushButton_last->setFixedSize(40,40);
    pushButton_last->setStyleSheet("QPushButton { border-image: url(:/icon/last.svg); }"
                                   "QPushButton:hover { border-image: url(:/icon/last_hover.svg); }"
                                   "QPushButton:pressed { border-image: url(:/icon/last.svg); }");
    pushButton_last->setFocusPolicy(Qt::NoFocus);
    pushButton_last->setFlat(true);
    pushButton_last->setCursor(Qt::PointingHandCursor);
    hbox->addWidget(pushButton_last);
    hbox->addSpacing(5);

    pushButton_play = new QPushButton;
    pushButton_play->setFixedSize(48,48);
    pushButton_play->setStyleSheet("QPushButton { border-image: url(:/icon/play.svg); }"
                                   "QPushButton:hover { border-image: url(:/icon/play_hover.svg); }"
                                   "QPushButton:pressed { border-image: url(:/icon/play.svg); }");
    pushButton_play->setFocusPolicy(Qt::NoFocus);
    pushButton_play->setFlat(true);
    pushButton_play->setCursor(Qt::PointingHandCursor);
    hbox->addWidget(pushButton_play);
    hbox->addSpacing(5);

    pushButton_next = new QPushButton;
    pushButton_next->setFixedSize(40,40);
    pushButton_next->setStyleSheet("QPushButton { border-image: url(:/icon/next.svg); }"
                                   "QPushButton:hover { border-image: url(:/icon/next_hover.svg); }"
                                   "QPushButton:pressed { border-image: url(:/icon/next.svg); }");
    pushButton_next->setFocusPolicy(Qt::NoFocus);
    pushButton_next->setFlat(true);
    pushButton_next->setCursor(Qt::PointingHandCursor);
    hbox->addWidget(pushButton_next);

    hbox->addSpacing(25);

    label_song_timeNow = new QLabel;
    label_song_timeNow->setText("00:00");
    label_song_timeNow->setStyleSheet("color:white;");
    hbox->addWidget(label_song_timeNow);

    slider_progress = new QSlider;
    slider_progress->setRange(0,1000);
    slider_progress->setOrientation(Qt::Horizontal);
    slider_progress->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    slider_progress->setFocusPolicy(Qt::NoFocus);
    //slider_progress->setCursor(Qt::PointingHandCursor);
    hbox->addWidget(slider_progress);

    label_song_duration = new QLabel;
    label_song_duration->setText("00:00");
    label_song_duration->setStyleSheet("color:white;");
    hbox->addWidget(label_song_duration);

    pushButton_mute = new QPushButton;
    pushButton_mute->setFixedSize(25,25);
    pushButton_mute->setIcon(QIcon(":/icon/volume.svg"));
    pushButton_mute->setIconSize(QSize(20,20));
    pushButton_mute->setFocusPolicy(Qt::NoFocus);
    pushButton_mute->setFlat(true);
    pushButton_mute->setCursor(Qt::PointingHandCursor);
    hbox->addWidget(pushButton_mute);

    slider_volume = new QSlider;
    slider_volume->setOrientation(Qt::Horizontal);
    slider_volume->setRange(0,100);
    //slider_volume->setValue(100);
    slider_volume->setFixedWidth(100);
    slider_volume->setFocusPolicy(Qt::NoFocus);
    //slider_volume->setCursor(Qt::PointingHandCursor);
    hbox->addWidget(slider_volume);

    QPushButton *pushButton_loop = new QPushButton;
    pushButton_loop->setFixedSize(30,30);
    pushButton_loop->setIcon(QIcon(":/icon/looplist.svg"));
    pushButton_loop->setIconSize(QSize(25,25));
    pushButton_loop->setFocusPolicy(Qt::NoFocus);
    pushButton_loop->setFlat(true);
    pushButton_loop->setCursor(Qt::PointingHandCursor);
    hbox->addWidget(pushButton_loop);

    pushButton_lyric = new QPushButton;
    pushButton_lyric->setFixedSize(30,30);
    pushButton_lyric->setIcon(QIcon(":/icon/lyric.svg"));
    pushButton_lyric->setIconSize(QSize(25,25));
    pushButton_lyric->setFocusPolicy(Qt::NoFocus);
    pushButton_lyric->setFlat(true);
    pushButton_lyric->setCheckable(true);
    pushButton_lyric->setChecked(true);
    pushButton_lyric->setCursor(Qt::PointingHandCursor);
    hbox->addWidget(pushButton_lyric);

//    QPushButton *pushButton_playlist = new QPushButton;
//    pushButton_playlist->setFixedSize(30,30);
//    pushButton_playlist->setIcon(QIcon(":/icon/playlist.svg"));
//    pushButton_playlist->setIconSize(QSize(25,25));
//    pushButton_playlist->setFocusPolicy(Qt::NoFocus);
//    pushButton_playlist->setFlat(true);
//    pushButton_playlist->setCursor(Qt::PointingHandCursor);
//    hbox->addWidget(pushButton_playlist);

    pushButton_download = new QPushButton;
    pushButton_download->setFixedSize(30,30);
    pushButton_download->setIcon(QIcon(":/icon/download.svg"));
    pushButton_download->setIconSize(QSize(25,25));
    pushButton_download->setFocusPolicy(Qt::NoFocus);
    pushButton_download->setFlat(true);
    pushButton_download->setCursor(Qt::PointingHandCursor);
    hbox->addWidget(pushButton_download);

    pushButton_fullscreen = new QPushButton;
    pushButton_fullscreen->setFixedSize(30,30);
    pushButton_fullscreen->setIcon(QIcon(":/icon/fullscreen.svg"));
    //pushButton_fullscreen->setIcon(QIcon::fromTheme("window_fullscreen"));
    pushButton_fullscreen->setIconSize(QSize(25,25));
    pushButton_fullscreen->setFocusPolicy(Qt::NoFocus);
    pushButton_fullscreen->setFlat(true);
    pushButton_fullscreen->setCursor(Qt::PointingHandCursor);
    hbox->addWidget(pushButton_fullscreen);

    setLayout(hbox);
}
