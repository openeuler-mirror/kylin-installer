#ifndef DATAPROCESS_H
#define DATAPROCESS_H

#include <QObject>
#include "DataStructDefines.h"

//data Process
//all static method

class DataProcess  :  public QObject
{
    Q_OBJECT
public:
    //todo: make this private
    explicit DataProcess(QObject *parent = nullptr);
    ~DataProcess();

     static bool QStringToRPMInfo(QString &str, RPMInfo &info);
     static QStringList QStringlistToRPMInfo(QString &str);

};

#endif // DATAPROCESS_H
