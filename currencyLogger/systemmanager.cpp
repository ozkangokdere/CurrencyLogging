#include "systemmanager.h"
#include "filerecorder.h"

SystemManager::SystemManager(QObject *parent) : QObject(parent)
{
}

SystemManager::~SystemManager()
{
    delete m_recorder;
    delete m_parser;
}

void SystemManager::start()
{
    m_parser = new CurrencyParser(this);
    m_recorder = new FileRecorder();
    m_recorder->setFileLimitInMB(1);
    connect(m_parser, SIGNAL(sigStamp(CurrencyParser::OneStamp)), this, SLOT(onStampArrived(CurrencyParser::OneStamp)));
    connect(m_parser, SIGNAL(sigFailed()), this, SLOT(onParserFailed()));
    m_parser->startParsing();
}

void SystemManager::onStampArrived(CurrencyParser::OneStamp pStamp)
{
    qDebug() << "Success" << pStamp.time;
    m_recorder->recordData((char*)&pStamp, sizeof(CurrencyParser::OneStamp));
}

void SystemManager::onParserFailed()
{
    qDebug() << "Failed Signal";
    m_parser->stopParsing();
    m_recorder->stopRecord();
    m_parser->startParsing();
}

