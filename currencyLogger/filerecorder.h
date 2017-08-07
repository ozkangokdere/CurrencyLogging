#ifndef FILERECORDER_H
#define FILERECORDER_H
#include <QFile>

class FileRecorder
{
public:
    FileRecorder();
    void recordData(const char *dataPtr, int dataLen);
    void stopRecord();

    int fileLimitInMB() const;
    void setFileLimitInMB(int fileLimitInMB);

private:
    bool openNextFile();
    QFile m_currentFile;
    int m_fileLimitInMB;
};

#endif // FILERECORDER_H
