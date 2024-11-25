/*
 *    rpm installer
 *    Copyright (c) KylinSoft  Co., Ltd. 2024. All rights reserved.
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
#include <QProcess>
#include "common.h"

bool Common::getTerminalOutput(const QString& strCmd, QString& result, QStringList* resultList, int timeout)
{
     QProcess pro;
     pro.start("sh",QStringList()<< "-c"<< strCmd);
     pro.waitForFinished(timeout);

     result = pro.readAllStandardError();

     if(result.size() != 0)
         return false;
     else
     {
         result = pro.readAllStandardOutput();
         if(resultList != nullptr)
             *resultList =result.split('\n',QString::SkipEmptyParts);
     }

    return true;
}
