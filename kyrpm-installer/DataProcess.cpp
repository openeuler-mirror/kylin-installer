#include "DataProcess.h"

DataProcess::DataProcess(QObject *parent)
    : QObject{parent}
{

}

DataProcess::~DataProcess()
{

}

bool DataProcess::QStringToRPMInfo(QString &str, RPMInfo &info)
{
    if(str.isEmpty()) {
        return false;
    }
    info.clear();
    //todo
}
