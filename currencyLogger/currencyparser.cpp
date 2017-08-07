#include "currencyparser.h"
#include <QDateTime>
#include <QDebug>

CurrencyParser::CurrencyParser(QObject *parent) : QObject(parent)
{
    m_timerInterval = 2000;
    m_url = QString("http://download.finance.yahoo.com/d/quotes.csv?e=.csv&f=c4l1&s=USDTRY=X,EURTRY=X,EURUSD=X");
    m_nam = new QNetworkAccessManager(this);
    m_timer = new QTimer(this);
    m_watchDogTimer = new QTimer(this);
    connect(m_nam, SIGNAL(finished(QNetworkReply*)), this, SLOT(onFinishedRequest(QNetworkReply*)));
    connect(m_timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
    connect(m_watchDogTimer, SIGNAL(timeout()), this, SLOT(onFailed()));
    m_timer->setInterval(m_timerInterval);
    m_watchDogTimer->setInterval(15000);

}

QString CurrencyParser::url() const
{
    return m_url;
}

void CurrencyParser::setUrl(const QString &url)
{
    m_url = url;
}

int CurrencyParser::timerInterval() const
{
    return m_timerInterval;
}

void CurrencyParser::setTimerInterval(int timerInterval)
{
    m_timerInterval = timerInterval;
}

void CurrencyParser::startParsing()
{
    m_timer->stop();
    m_timer->start();
}

void CurrencyParser::stopParsing()
{
    m_timer->stop();
}

void CurrencyParser::onFinishedRequest(QNetworkReply *reply)
{
    m_watchDogTimer->stop();
    qint64 time = QDateTime::currentMSecsSinceEpoch();
    QByteArray buf = reply->readAll();
    QString content = QString::fromUtf8(buf);
    QStringList list = content.split("\n", QString::SkipEmptyParts);
    if (list.size() != 3) {
        qDebug() << "Data Read ERROR. Reply:" << buf;
        onFailed();
        return;
    }
    float d2t;
    float e2t;
    float e2d;
    QString tinyBuf;
    tinyBuf = list.at(0);
    tinyBuf = tinyBuf.split(",", QString::SkipEmptyParts).at(1);
    d2t = tinyBuf.toFloat();

    tinyBuf = list.at(1);
    tinyBuf = tinyBuf.split(",", QString::SkipEmptyParts).at(1);
    e2t = tinyBuf.toFloat();

    tinyBuf = list.at(2);
    tinyBuf = tinyBuf.split(",", QString::SkipEmptyParts).at(1);
    e2d = tinyBuf.toFloat();

    OneStamp tStamp;

    tStamp.time = time;
    tStamp.usdtry = (unsigned short)(d2t * 10000);
    tStamp.eurtry = (unsigned short)(e2t * 10000);
    tStamp.eurusd = (unsigned short)(e2d * 10000);
    tStamp.flag = 0xfcfc;

    emit sigStamp(tStamp);

    m_timer->start();
}

void CurrencyParser::onTimeout()
{
    m_timer->stop();
    m_nam->get(QNetworkRequest(QUrl(m_url)));
    m_watchDogTimer->start();
}

void CurrencyParser::onFailed()
{
    stopParsing();
    m_watchDogTimer->stop();
    emit sigFailed();
}

