#include "navwidget.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QDebug>

NavWidget::NavWidget(QWidget *parent) : QWidget(parent)
{    
    setStyleSheet("QPushButton {color:#ffffff;} "
                  "QListWidget { border:none; } "
                  "QListWidget::item { color:#cccccc; padding:4px;} "
                  "QListWidget::item:selected { background-color:#333333; }");
    setFixedWidth(200);
    setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Expanding);
    QVBoxLayout *vbox = new QVBoxLayout;    
    listWidget = new QListWidget;
    listWidget->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Expanding);
    QListWidgetItem *LWI;
    LWI = new QListWidgetItem("推荐");
    LWI->setFlags(Qt::NoItemFlags);
    listWidget->insertItem(0, LWI);
    //LWI = new QListWidgetItem(QIcon(":/music.svg"), "发现音乐");
    LWI = new QListWidgetItem(QIcon(":/music.svg"), "排行榜");
    listWidget->insertItem(1, LWI);
    //LWI = new QListWidgetItem(QIcon(":/radio.svg"), "私人FM");
    LWI = new QListWidgetItem(QIcon(":/radio.svg"), "歌单");
    listWidget->insertItem(2, LWI);
    //LWI = new QListWidgetItem(QIcon(":/video.svg"), "MV");
    LWI = new QListWidgetItem(QIcon(":/video.svg"), "歌词");
    listWidget->insertItem(3, LWI);
    LWI = new QListWidgetItem(QIcon(":/friend.svg"), "朋友");
    listWidget->insertItem(4, LWI);
    LWI = new QListWidgetItem("本地音乐");
    LWI->setFlags(Qt::NoItemFlags);
    listWidget->insertItem(5, LWI);
    LWI = new QListWidgetItem(QIcon(":/music1.svg"), "本地音乐");
    listWidget->insertItem(6, LWI);
    LWI = new QListWidgetItem(QIcon(":/download.svg"), "下载管理");
    listWidget->insertItem(7, LWI);
    LWI = new QListWidgetItem(QIcon(":/cloud.svg"), "我的音乐云盘");
    listWidget->insertItem(8, LWI);
    LWI = new QListWidgetItem(QIcon(":/man.svg"), "我的歌手");
    listWidget->insertItem(9, LWI);
    LWI = new QListWidgetItem(QIcon(":/video.svg"), "我的MV");
    listWidget->insertItem(10, LWI);
    LWI = new QListWidgetItem(QIcon(":/radio1.svg"), "我的电台");
    listWidget->insertItem(11, LWI);
    LWI = new QListWidgetItem("创建的歌单");
    LWI->setFlags(Qt::NoItemFlags);
    listWidget->insertItem(12, LWI);
    LWI = new QListWidgetItem(QIcon(":/heart.svg"), "我喜欢的音乐");
    listWidget->insertItem(13, LWI);
    LWI = new QListWidgetItem(QIcon(":/songlist.svg"), "我的音乐");
    listWidget->insertItem(14, LWI);
    vbox->addWidget(listWidget);

    pushButton_songname = new QPushButton;
    pushButton_songname->setFixedHeight(40);
    //pushButton_songname->setIcon(QIcon(":/looplist.svg"));
    pushButton_songname->setIconSize(QSize(30,30));
    pushButton_songname->setFocusPolicy(Qt::NoFocus);
    pushButton_songname->setFlat(true);
    vbox->addWidget(pushButton_songname);

    setLayout(vbox);
}
