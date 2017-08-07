#ifndef CURRENCYPARSER_H
#define CURRENCYPARSER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QTimer>

class CurrencyParser : public QObject
{
    Q_OBJECT
public:
    explicit CurrencyParser(QObject *parent = 0);

    struct OneStamp{
        quint64 time;
        unsigned short usdtry;
        unsigned short eurtry;
        unsigned short eurusd;
        unsigned short flag;
    };

    QString url() const;
    void setUrl(const QString &url);

    int timerInterval() const;
    void setTimerInterval(int timerInterval);

    void startParsing();
    void stopParsing();

private:
    QNetworkAccessManager* m_nam;
    QTimer* m_timer;
    QTimer* m_watchDogTimer;
    QString m_url;
    int m_timerInterval;

private slots:
    void onFinishedRequest(QNetworkReply* reply);
    void onTimeout();
    void onFailed();

signals:
    void sigStamp(CurrencyParser::OneStamp);
    void sigFailed();
};

#endif // CURRENCYPARSER_H
