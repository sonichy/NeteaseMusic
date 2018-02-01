#include "titlebar.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QDebug>
#include <QMenu>
#include <QAction>
#include <QApplication>
#include <QDialog>

TitleBar::TitleBar(QWidget *parent) : QWidget(parent)
{
    setStyleSheet("QPushButton::menu-indicator{width:0px;}"
                  "QMenu::item{color:white;} QMenu::item:selected {background-color: #333333;}"
                  "QLineEdit { font-size:12px; border:2px solid #000000; border-top-left-radius:10px; border-bottom-left-radius:10px; color:#cccccc; background-color:#000000; padding-left:10px;}"
                  "#search { background-color:#000000; border-top-right-radius:10px; border-bottom-right-radius:10px; }");
    setFixedHeight(50);

    QHBoxLayout *hbox = new QHBoxLayout;
    hbox->setSpacing(0);

    QLabel *label_icon = new QLabel;
    label_icon->setFixedSize(30,30);
    label_icon->setPixmap(QPixmap(":/icont.svg").scaled(label_icon->size(),Qt::KeepAspectRatioByExpanding,Qt::SmoothTransformation));
    hbox->addWidget(label_icon);

    QLabel *label_title = new QLabel;
    label_title->setText("网易云音乐");
    label_title->setAlignment(Qt::AlignCenter);
    label_title->setStyleSheet("color:white;font-size:15px;");
    hbox->addWidget(label_title);

    hbox->addStretch();

    lineEdit_search = new QLineEdit;
    lineEdit_search->setPlaceholderText("搜索音乐、歌手、歌词、用户");
    lineEdit_search->setFixedWidth(200);
    hbox->addWidget(lineEdit_search);

    pushButton_search = new QPushButton;
    pushButton_search->setFixedSize(24,24);
    pushButton_search->setIcon(QIcon(":/search.svg"));
    pushButton_search->setIconSize(QSize(20,20));
    pushButton_search->setFlat(true);
    pushButton_search->setFocusPolicy(Qt::NoFocus);    
    pushButton_search->setObjectName("search");
    pushButton_search->setCursor(Qt::PointingHandCursor);
    hbox->addWidget(pushButton_search);

    hbox->addStretch();

    QPushButton *pushButton_menu = new QPushButton;
    pushButton_menu->setFixedSize(24,24);
    pushButton_menu->setIcon(QIcon(":/menu.svg"));
    pushButton_menu->setIconSize(QSize(20,20));
    pushButton_menu->setFlat(true);
    pushButton_menu->setFocusPolicy(Qt::NoFocus);
    QMenu *submenu = new QMenu(this);
    QAction *login=new QAction("登录",this);
    QAction *about=new QAction("关于",this);
    QAction *quit=new QAction("退出",this);
    submenu->addAction(login);
    submenu->addAction(about);
    submenu->addAction(quit);
    pushButton_menu->setMenu(submenu);
//    connect(login,SIGNAL(triggered()),this,SLOT(login()));
    connect(about,SIGNAL(triggered()),this,SLOT(about()));
    connect(quit,SIGNAL(triggered()),qApp,SLOT(quit()));
    hbox->addWidget(pushButton_menu);

    pushButton_minimize = new QPushButton;
    pushButton_minimize->setFixedSize(24,24);
    pushButton_minimize->setIcon(QIcon(":/minimize.svg"));
    pushButton_minimize->setIconSize(QSize(20,20));
    pushButton_minimize->setFlat(true);
    pushButton_minimize->setFocusPolicy(Qt::NoFocus);
    hbox->addWidget(pushButton_minimize);

    pushButton_maximize = new QPushButton;
    pushButton_maximize->setFixedSize(24,24);
    pushButton_maximize->setIcon(QIcon(":/maximize.svg"));
    pushButton_maximize->setIconSize(QSize(20,20));
    pushButton_maximize->setFlat(true);
    pushButton_maximize->setFocusPolicy(Qt::NoFocus);
    hbox->addWidget(pushButton_maximize);

    pushButton_close = new QPushButton;
    pushButton_close->setFixedSize(24,24);
    pushButton_close->setIcon(QIcon(":/close.svg"));
    pushButton_close->setIconSize(QSize(20,20));
    pushButton_close->setFlat(true);
    pushButton_close->setFocusPolicy(Qt::NoFocus);    
    hbox->addWidget(pushButton_close);

    setLayout(hbox);
}

void TitleBar::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        //qDebug() << "mousePress" << event->pos();
        relativePos = event->pos();
    }
}

void TitleBar::mouseMoveEvent(QMouseEvent *event)
{
    //qDebug() << event->globalPos() << "-" << relativePos << "=" << event->globalPos() - relativePos;
    emit moveMainWindow(event->globalPos() - relativePos);
}

void TitleBar::about()
{
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("关于");
    dialog->setFixedSize(500,300);
    QVBoxLayout *vbox = new QVBoxLayout;
    QLabel *label = new QLabel;
    label->setPixmap(QPixmap(":/icon.jpg").scaled(80,80,Qt::KeepAspectRatioByExpanding,Qt::SmoothTransformation));
    label->setAlignment(Qt::AlignCenter);
    vbox->addWidget(label);
    label = new QLabel;
    label->setText("网易云音乐 V1.0");
    label->setAlignment(Qt::AlignCenter);
    label->setStyleSheet("color:white;font-size:20px;");
    vbox->addWidget(label);
    label = new QLabel;
    label->setText("         一款基于 Qt 的网易云音乐播放器。\n作者：黄颖\nE-mail: sonichy@163.com\n主页：http://sonichy.gitee.io\n音乐版权：网页云音乐\n参考：\nhttps://github.com/gcmwhite/CloudMusic-Bc-5\nhttp://get.ftqq.com/7430.get");
    label->setStyleSheet("color:white;font-size:15px;");
    label->setWordWrap(true);
    label->setAlignment(Qt::AlignTop);
    vbox->addWidget(label);
    vbox->addStretch();
    dialog->setLayout(vbox);
    dialog->show();
}
