#include <QCoreApplication>
#include "systemmanager.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    SystemManager* manager = new SystemManager(0);
    manager->start();
    return a.exec();
}

