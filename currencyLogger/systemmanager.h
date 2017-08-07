#ifndef SYSTEMMANAGER_H
#define SYSTEMMANAGER_H

#include <QObject>
#include "currencyparser.h"

class FileRecorder;
class SystemManager : public QObject
{
    Q_OBJECT
public:
    explicit SystemManager(QObject *parent = 0);
    ~SystemManager();
    void start();
signals:

public slots:

private:
    CurrencyParser* m_parser;
    FileRecorder* m_recorder;

private slots:
    void onStampArrived(CurrencyParser::OneStamp pStamp);
    void onParserFailed();
};

#endif // SYSTEMMANAGER_H
