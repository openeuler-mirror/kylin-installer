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

const QString RPMCommandWorker::action_string[] = {"install", "uninstall", "reinstall"};

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

void RPMCommandWorker::setOptions(const QString arguments, ACTION_TYPE action)
{
    m_arguments << arguments;
    m_action = action;
    result = "";
}

void RPMCommandWorker::setOptions(const QStringList arguments, ACTION_TYPE action)
{
    m_arguments = arguments;
    m_action = action;
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
    QString command = QString(KYRPM_YUMPATH) + " -y " + action_string[int(m_action)] + " " + m_arguments[0];
    process.start(command);

    //wait process start
    if (!process.waitForStarted())
    {
        qDebug()<<"process start failed!"<<command;
        qDebug()<<process.error();
        return;
    }

    if(!process.waitForFinished())
    {
        qInfo()<<process.error();
    }else
    {
        int exitCode = process.exitCode();
        result = process.readAllStandardOutput();
        qInfo()<<result;
        if(exitCode == 0)
        {
            emit cmdEnd(result,0);
        }else
        {
            emit cmdEnd(result,1);
        }
    }
}

void RPMCommandWorker::init()
{
    m_arguments.clear();
}
