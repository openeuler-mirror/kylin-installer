#include "DataProcess.h"
#include <QDebug>

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

    QStringList RPMInfoList = QStringlistToRPMInfo(str);
    info.packageName = RPMInfoList.at(0);
    info.epoch = RPMInfoList.at(1);
    info.version = RPMInfoList.at(2);
    info.release = RPMInfoList.at(3);
    if(RPMInfoList.at(4).contains(QString("x86_64"))){
        info.arch =Architecuture(0);
    }else if(RPMInfoList.at(4).contains(QString("aarch"))){
        info.arch =Architecuture(1);
    }else{
        info.arch =Architecuture(2);
    }
    info.installDate = RPMInfoList.at(5);
    info.group = RPMInfoList.at(6);
    info.size = RPMInfoList.at(7).toInt();
    info.licenses = RPMInfoList.at(8);
    info.signature = RPMInfoList.at(9);
    info.source = RPMInfoList.at(10);
    info.buildDate = RPMInfoList.at(11);
    info.buildHost = RPMInfoList.at(12);
    info.url = RPMInfoList.at(13);
    info.summary = RPMInfoList.at(14);
    info.description = RPMInfoList.at(15);

    return true;
}

QStringList DataProcess::QStringlistToRPMInfo(QString &str)
{
    QStringList RPMInfoList;
    QStringList strList;
    QStringList strspl;
    QString Description;
    bool Descriptionflag = false;

    strList=str.split("\n");
    for(int i=0;i<strList.count();i++)
    {
        QString strstr;
        //        qDebug() << strList[i];
        if(strList[i].contains(QString("Description"))){
            Descriptionflag = true;
            continue;
        }
        if(Descriptionflag){
            Description += strList[i];
        }else{
            strspl = strList[i].split(":");
            for(int i=1;i<strspl.count();i++)
            {
                strstr += strspl.at(i);
            }
            //            qDebug() << strstr;
            RPMInfoList << strstr;
        }
    }
    //    qDebug() << Description;
    RPMInfoList << Description;
    return  RPMInfoList;
}
