/*
 *    rpm installer
 *    Copyright (c) KylinSoft  Co., Ltd. 2023. All rights reserved.
 *
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, version 2.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program; if not, write to the Free Software
 *    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
 */

#include "GetRPMInfoBackend.h"
#include <QProcess>
#include <QDebug>
#include "DataProcess.h"

GetRPMInfoBackend * GetRPMInfoBackend::instance = nullptr;

GetRPMInfoBackend::GetRPMInfoBackend(QObject *parent)
    : QObject{parent}
{
    m_process = new QProcess();
}

GetRPMInfoBackend::~GetRPMInfoBackend()
{
    if(m_process){
        m_process->close();
        delete m_process;
    }
}

GetRPMInfoBackend *GetRPMInfoBackend::getInstance()
{
    if(instance == nullptr) {
        instance = new GetRPMInfoBackend();
    }
    return instance;
}

bool GetRPMInfoBackend::getRPMInfoFromPackage(RPMInfo &info, QString strPath)
{
    if(strPath.isEmpty() || m_process == nullptr)
    {
        qDebug()<<"path is empty";
        return false;
    }

    connect(m_process,&QProcess::readyReadStandardOutput,this,[=, &info](){
        QString temp = m_process->readAllStandardOutput();
        qDebug()<<"read success! ";
        qDebug()<<temp;
        DataProcess::QStringToRPMInfo(temp, info);
    });
    connect(m_process,&QProcess::readyReadStandardError,this, [=](){
        QString error = m_process->readAllStandardError();
        qDebug()<<"excute cmd error: " << error;

    });

    QStringList arguments;
    arguments << "-qi" << strPath;

    m_process->start(KYRPM_RPMPATH,arguments);
    //wait process start
    if (!m_process->waitForStarted())
    {
        qDebug()<<"process start failed!";
        return false;
    }

    m_process->waitForFinished();
    return true;
}

bool GetRPMInfoBackend::getRPMInfoFromPackage1(RPMInfo &info, QString strPath)
{
//    if(strPath.isEmpty())
//    {
//        qDebug()<<"path is empty";
//        return false;
//    }
//    QProcess  process;
//    process.start(KYRPM_RPMPATH,arguments);
//    //wait process start
//    if (!process.waitForStarted())
//    {
//        qDebug()<<"process start failed!";
//        return false;
//    }

//    process.waitForFinished();

//    QString result = process.readAllStandardOutput();
    return true;
}
