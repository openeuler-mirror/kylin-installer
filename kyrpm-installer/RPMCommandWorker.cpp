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

#include "RPMCommandWorker.h"
#include <QDebug>

RPMCommandWorker::RPMCommandWorker(QObject *parent) : QThread(parent)
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
    process.start(QString(KYRPM_YUMPATH) + " -y install " + m_arguments.at(0));

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
    emit cmdEnd();
}

void RPMCommandWorker::init()
{
    m_arguments.clear();
}
