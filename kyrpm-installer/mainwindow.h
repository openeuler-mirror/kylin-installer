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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include "RpmDisplayWidget.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void showInfoMessage(bool isShown);
    void runCommand();
    void processCommandResult();
    bool dnfInstall(QString strPackageName);
    bool dnfInstall();
    void slotFileChoose(bool);


private:
    void initSignals();
    void initUI();

private:
    Ui::MainWindow *ui;
    QProcess *m_process;
    RpmDisplayWidget* m_infoWidget;

    QString m_strPath;
};
#endif // MAINWINDOW_H
