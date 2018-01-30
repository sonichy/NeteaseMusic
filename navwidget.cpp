#include "navwidget.h"
#include <QListWidget>
#include <QVBoxLayout>
#include <QLabel>

NavWidget::NavWidget(QWidget *parent) : QWidget(parent)
{    
    setStyleSheet("QLabel{color:#999999;}"
                  "QListWidget { border:none; } "
                  "QListWidget::item { color:#cccccc; padding:5px;} "
                  "QListWidget::item:selected { background-color:#333333; }");
    setFixedWidth(200);
    setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Expanding);
    QVBoxLayout *vbox = new QVBoxLayout;
    QLabel *label = new QLabel;
    label->setText("推荐");
    vbox->addWidget(label);
    QListWidget *listWidget_recommend = new QListWidget;
    QListWidgetItem *LWI1,*LWI2,*LWI3,*LWI4,*LWI5,*LWI6;
    LWI1 = new QListWidgetItem(QIcon(":/music.svg"), "发现音乐");
    LWI2 = new QListWidgetItem(QIcon(":/radio.svg"), "私人FM");
    LWI3 = new QListWidgetItem(QIcon(":/video.svg"), "MV");
    LWI4 = new QListWidgetItem(QIcon(":/friend.svg"), "朋友");
    listWidget_recommend->insertItem(1, LWI1);
    listWidget_recommend->insertItem(2, LWI2);
    listWidget_recommend->insertItem(3, LWI3);
    listWidget_recommend->insertItem(4, LWI4);
    listWidget_recommend->setFixedHeight(150);
    vbox->addWidget(listWidget_recommend);
    label = new QLabel;
    label->setText("我的音乐");
    vbox->addWidget(label);
    QListWidget *listWidget_myMusic = new QListWidget;
    LWI1 = new QListWidgetItem(QIcon(":/music1.svg"), "本地音乐");
    LWI2 = new QListWidgetItem(QIcon(":/download.svg"), "下载管理");
    LWI3 = new QListWidgetItem(QIcon(":/cloud.svg"), "我的音乐云盘");
    LWI4 = new QListWidgetItem(QIcon(":/man.svg"), "我的歌手");
    LWI5 = new QListWidgetItem(QIcon(":/video.svg"), "我的MV");
    LWI6 = new QListWidgetItem(QIcon(":/radio1.svg"), "我的电台");
    listWidget_myMusic->insertItem(1, LWI1);
    listWidget_myMusic->insertItem(2, LWI2);
    listWidget_myMusic->insertItem(3, LWI3);
    listWidget_myMusic->insertItem(4, LWI4);
    listWidget_myMusic->insertItem(5, LWI5);
    listWidget_myMusic->insertItem(6, LWI6);
    listWidget_myMusic->setFixedHeight(220);
    vbox->addWidget(listWidget_myMusic);
    label = new QLabel;
    label->setText("创建的歌单");
    vbox->addWidget(label);
    QListWidget *listWidget_songList = new QListWidget;
    LWI1 = new QListWidgetItem(QIcon(":/heart.svg"), "我喜欢的音乐");
    LWI2 = new QListWidgetItem(QIcon(":/songlist.svg"), "我的音乐");
    listWidget_songList->insertItem(1, LWI1);
    listWidget_songList->insertItem(2, LWI2);
    vbox->addWidget(listWidget_songList);
    vbox->addStretch();
    setLayout(vbox);
}
