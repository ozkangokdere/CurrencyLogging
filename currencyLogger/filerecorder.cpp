#include "filerecorder.h"
#include <QDateTime>

FileRecorder::FileRecorder() :
    m_fileLimitInMB(50)
{
}

void FileRecorder::recordData(const char *dataPtr, int dataLen)
{
    if (!m_currentFile.isOpen() || m_currentFile.pos() > 1024*1024*m_fileLimitInMB) {
        if (!openNextFile()) {
            return;
        }
    }
    m_currentFile.write(dataPtr, dataLen);
}

void FileRecorder::stopRecord()
{
    m_currentFile.close();
}

int FileRecorder::fileLimitInMB() const
{
    return m_fileLimitInMB;
}

void FileRecorder::setFileLimitInMB(int fileLimitInMB)
{
    m_fileLimitInMB = fileLimitInMB;
}

bool FileRecorder::openNextFile()
{
    m_currentFile.close();
    QDateTime dateTime = QDateTime::currentDateTime();
    m_currentFile.setFileName(QString("RecordsFolder/data_%1.rec").arg(dateTime.toString("yyyy_MM_dd_HH_mm_ss")));
    return m_currentFile.open(QFile::ReadWrite);
}

