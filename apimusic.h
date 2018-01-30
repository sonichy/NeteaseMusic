#ifndef APIMUSIC_H
#define APIMUSIC_H

#include <QObject>
#include <QPixmap>

class APIMusic : public QObject
{
    Q_OBJECT
public:
    explicit APIMusic(QObject *parent = nullptr);
    QByteArray getReply(QString surl);

signals:

public slots:

};

#endif // APIMUSIC_H
