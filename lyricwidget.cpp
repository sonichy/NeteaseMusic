#include "lyricwidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDir>
#include <QSettings>

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

    label_lyric = new QLabel;
    label_lyric->setAlignment(Qt::AlignCenter);
    QFont font;
    font.setPointSize(30);
    label_lyric->setFont(font);
    vbox->addWidget(label_lyric);

    setLayout(vbox);

    pushButton_set->hide();
    pushButton_close->hide();
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
