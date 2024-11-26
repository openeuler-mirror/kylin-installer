#include "DataProcess.h"
#include <QDebug>
#include <QRegExp>

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
    QStringList RPMInfoList = str.split("\n");
    for(auto i : RPMInfoList) {
        static bool is_desc = false;
        if(is_desc){
            auto e = info.getInfo(RPMInfo::RPMINFO_KEY::description);
            info.setInfo(RPMInfo::RPMINFO_KEY::description, e + i);
            continue;
        }
        QRegExp rx("^(.*):(.*)$");
        if(rx.indexIn(i) != -1){
            qDebug()<<"error rpminfo string";
            info.clear();
            return false;
        }
        QString key = rx.cap(1).trimmed();
        QString value = rx.cap(2).trimmed();
        if(key == RPMInfo::rpminfo_key_Qstring[int(RPMInfo::RPMINFO_KEY::description)]){
            is_desc = true;
            continue;
        }
        if(!info.setInfo(key, value)){
            qDebug()<<"error rpminfo key string";
            info.clear();
            return false;
        }
    }

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
        if(strList[i].contains(QString("Description"))){
            Descriptionflag = true;
            continue;
        }
        if(Descriptionflag){
            Description += strList[i];
        }else{
            strspl = strList[i].split(": ");
            for(int j=1;j<strspl.count();j++)
            {
                strstr += strspl.at(j);
            }
            RPMInfoList << strstr;
        }
    }
    RPMInfoList << Description;
    return  RPMInfoList;
}
