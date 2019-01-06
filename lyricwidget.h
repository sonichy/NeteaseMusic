#ifndef LYRICWIDGET_H
#define LYRICWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QMouseEvent>
#include <QSettings>

class LyricWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LyricWidget(QWidget *parent = nullptr);
    QPushButton *pushButton_set, *pushButton_close;
    QLabel *label_lyric;
    QString text;
    QFont font;
    QColor color_left, color_right;
    float lp;
    bool isMouseOn, isMLBD;

private:
    QPoint m_point;
    QSettings settings;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void paintEvent(QPaintEvent *event);

};

#endif // LYRICWIDGET_H