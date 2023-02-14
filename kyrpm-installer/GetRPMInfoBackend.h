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
#ifndef GETRPMINFOBACKEND_H
#define GETRPMINFOBACKEND_H

#include <QObject>
#include <DataStructDefines.h>

class QProcess;


//use command instead of rpm library

class GetRPMInfoBackend : public QObject
{
    Q_OBJECT
public:
    ~GetRPMInfoBackend();
    static GetRPMInfoBackend* getInstance();

signals:
    void readRPMInfoFinished();
    void readRPMInfoError();

private slots:

public:
    bool getRPMInfoFromPackage(RPMInfo &info, QString strPath);
    bool getRPMInfoFromPackage1(RPMInfo &info, QString strPath);

private:
    explicit GetRPMInfoBackend(QObject *parent = nullptr);

    static GetRPMInfoBackend* instance;

    QProcess* m_process;


};

#endif // GETRPMINFOBACKEND_H
