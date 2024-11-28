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

#include "mainwindow.h"

#include <QApplication>
#include <QDebug>
#include "RPMCommandWorker.h"
#include "RpmDisplayDlg.h"
#include <QSharedMemory>
#include <QMessageBox>
#include <unistd.h>

int main(int argc, char *argv[])
{
#if (QT_VERSION >= QT_VERSION_CHECK(5, 12, 0))
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
#endif
#if (QT_VERSION >= QT_VERSION_CHECK(5, 14, 0))
    QApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
#endif

    setenv("QT_QPA_PLATFORMTHEME" , "ukui" , true);


    QApplication a(argc, argv);
    if (getuid() != 0)
    {
        QMessageBox::critical(nullptr, "Permission error",
                              "Programs must be run with root privileges!");
        return -1;
    }

    QSharedMemory *shareMem = new QSharedMemory(QString("SingleInstanceIdentify"));
    volatile short i = 2;
    while (i--)
    {
        if (shareMem->attach(QSharedMemory::ReadOnly))
        {
            shareMem->detach();
        }
    }
    if(shareMem->create(1)){
        MainWindow w;
        w.show();
        a.exec();

        if (shareMem->isAttached())
            shareMem->detach();

        delete shareMem;
    }
    else {
        QMessageBox::information(nullptr, "info", "process already running");
    }

    return 0;
}
