#include "lyricwidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDir>
#include <QSettings>
#include <QPainter>
#include <QStyleOption>
#include <QDebug>

LyricWidget::LyricWidget(QWidget *parent) : QWidget(parent)
{
    resize(600,120);

    setAttribute(Qt::WA_TranslucentBackground,true);
    setWindowFlags(Qt::WindowStaysOnTopHint);
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowFlags(Qt::X11BypassWindowManagerHint);

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->setSpacing(0);

    QHBoxLayout *hbox = new QHBoxLayout;
    hbox->addStretch();
    pushButton_set = new QPushButton;
    pushButton_set->setFixedSize(24,24);
    pushButton_set->setIcon(QIcon(":/set.svg"));
    pushButton_set->setFocusPolicy(Qt::NoFocus);
    pushButton_set->setFlat(true);
    hbox->addWidget(pushButton_set);

    pushButton_close = new QPushButton;
    pushButton_close->setFixedSize(24,24);
    pushButton_close->setIcon(QIcon(":/close.svg"));
    pushButton_close->setFocusPolicy(Qt::NoFocus);
    pushButton_close->setFlat(true);
    hbox->addWidget(pushButton_close);
    vbox->addLayout(hbox);

    vbox->addStretch();
    setLayout(vbox);

    pushButton_set->hide();
    pushButton_close->hide();

    //使用PaintEvent之后setStyleSheet不生效的解决办法: https://blog.csdn.net/zzwdkxx/article/details/78224958
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    //QWidget::paintEvent(event);
}

void LyricWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        //m_bPressed = true;
        m_point = event->pos();
    }
}

void LyricWidget::mouseMoveEvent(QMouseEvent *event)
{
    //if(m_bPressed)
        move(event->pos() - m_point + pos());
}

void LyricWidget::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    //m_bPressed = false;
    writeSettings(QDir::currentPath() + "/config.ini", "config", "LyricX", QString::number(x()));
    writeSettings(QDir::currentPath() + "/config.ini", "config", "LyricY", QString::number(y()));
}

void LyricWidget::enterEvent(QEvent *event)
{
    Q_UNUSED(event);
    setStyleSheet("background-color: rgba(255,255,255,30);");
    pushButton_close->setVisible(true);
    pushButton_set->setVisible(true);
}

void LyricWidget::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    setStyleSheet("");
    pushButton_close->setVisible(false);
    pushButton_set->setVisible(false);
}

void LyricWidget::writeSettings(QString path, QString group, QString key, QString value)
{
    QSettings *config = new QSettings(path, QSettings::IniFormat);
    config->beginGroup(group);
    config->setValue(key, value);
    config->endGroup();
}

void LyricWidget::paintEvent(QPaintEvent *event)
{
    // https://bbs.csdn.net/topics/350233731
    Q_UNUSED(event);
    QPainter p(this);
    p.setRenderHints(QPainter::Antialiasing);
    QRegion left(0,30,width()*lp,100);//左边唱过的部分,这里的值我是随便弄的作效果
    QRegion right(width()*lp,30,width(),height()); //右边未唱过的部分
    QPainterPath path;
    path.addText(0,70,font,text); //歌词文字作为路径
    p.setBrush(color_left);       //文字填充颜色
    p.setPen(color_left);         //文字边框颜色
    p.setClipRegion(left);        //设置栽剪区域,Painter只在其中绘图
    p.drawPath(path);             //画出左边歌词
    p.setBrush(color_right);        //改变填充字体颜色为绿色
    p.setPen(color_right);          //改变字体边框为绿色
    p.setClipRegion(right);       //设置栽剪区域为右边未唱过的部分
    p.drawPath(path);             //画右边未唱过的歌词
}
