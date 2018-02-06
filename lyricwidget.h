#ifndef LYRICWIDGET_H
#define LYRICWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QMouseEvent>

class LyricWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LyricWidget(QWidget *parent = nullptr);
    QPushButton *pushButton_set, *pushButton_close;
    QLabel *label_lyric;

private:
    QPoint m_point;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void writeSettings(QString path, QString group, QString key, QString value);

signals:

public slots:

};

#endif // LYRICWIDGET_H
