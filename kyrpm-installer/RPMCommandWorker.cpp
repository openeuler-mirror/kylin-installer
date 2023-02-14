#include "RPMCommandWorker.h"
#include <QDebug>

RPMCommandWorker::RPMCommandWorker(QObject *parent)
{
    init();
}

RPMCommandWorker::~RPMCommandWorker()
{

}

void RPMCommandWorker::stop()
{
    this->quit();
    this->wait();
}

void RPMCommandWorker::setOptions(const QString arguments)
{
    m_arguments << arguments;

    result = "";
}

void RPMCommandWorker::setOptions(const QStringList arguments)
{
    m_arguments = arguments;

    result = "";
}

QString RPMCommandWorker::getInfo()
{
    return result;
}

void RPMCommandWorker::run()
{
    if(m_arguments.isEmpty()){
        qDebug()<<"RPMCommandWorker command is empty";
    }
    //temp use command instead of rpm library
    QProcess  process;
    process.start(KYRPM_RPMPATH,m_arguments);

    //wait process start
    if (!process.waitForStarted())
    {
        qDebug()<<"process start failed!";
        qDebug()<<process.error();
        return;
    }

    process.waitForFinished();

    result = process.readAllStandardOutput();

    qDebug()<<"+++++++++++++++++++"<<m_arguments;
    qDebug()<<result <<"++++++  " << process.readAllStandardError();
}

void RPMCommandWorker::init()
{
    m_arguments.clear();
}
