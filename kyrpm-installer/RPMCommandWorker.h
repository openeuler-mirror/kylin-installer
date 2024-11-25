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
#ifndef RPMCOMMANDWORKER_H
#define RPMCOMMANDWORKER_H

#include<DataStructDefines.h>
#include <QThread>
#include <QProcess>

//执行相应的rpm查询命令，放入线程执行不阻塞界面
class RPMCommandWorker : public QThread
{
    Q_OBJECT
public:
    explicit RPMCommandWorker(QObject *parent = nullptr);
     ~RPMCommandWorker();

    void stop();

    void setOptions(const QString m_arguments);
    void setOptions(const QStringList m_arguments);


    QString getInfo();
protected:
    virtual void run();

    //command
    QStringList m_arguments;

private:
    void init();

    QString result;

signals:
    void cmdEnd(QString result);
};

#endif // RPMCOMMANDWORKER_H
