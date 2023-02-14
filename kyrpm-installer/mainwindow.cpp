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
#include "ui_mainwindow.h"
#include <QDebug>
#include "RPMCommandWorker.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_process = nullptr;

    //ui->textEdit->hide();


    initSignals();
}

MainWindow::~MainWindow()
{
    if(m_process != nullptr)
    {
        delete m_process;
        m_process = nullptr;
    }
    delete ui;
}

void MainWindow::showInfoMessage(bool isShown)
{
    qDebug()<<"test++++++++++++++++"<< isShown;
    ui->textEdit->setVisible(isShown);
}

void MainWindow::runCommand()
{
    QString program = "ls";
    QStringList arguments;
    arguments << "";

    m_process = new QProcess(this);

    m_process->setReadChannel(QProcess::StandardOutput);
    connect(m_process, SIGNAL(readyReadStandardOutput()),this, SLOT(processCommandResult()));

    m_process->start(program, arguments);

    bool b1 = m_process->waitForFinished();
    qDebug()<<"----------------------"<<b1;
}

void MainWindow::processCommandResult()
{
    qDebug()<< "processCommandResult++++++++++++++++++";
    qDebug() << m_process->readAllStandardOutput();
}

void MainWindow::initSignals()
{
    //todo
    //connect(ui->actionShowMessageLog,SIGNAL(triggered(bool)),this, SLOT(showInfoMessage(bool)));
    connect(ui->installButton,SIGNAL(clicked()), this, SLOT(dnfInstall()));

    //


}

bool MainWindow::dnfInstall(QString strPackageName)
{
    if(strPackageName.isEmpty())
    {
        qDebug()<<"can not install empty package!";

//        QString path = "/Users/douyan/temp/ukui-greeter-1.2.1-48.1.p15.ky10.src.rpm";
//        QStringList lst;
//        lst << "-qi" << path;

//        RPMCommandWorker *worker = new RPMCommandWorker();
//        worker->setOptions(lst);
//        worker->start();

        return false;
    }
    //todo check rpm exist

    //start run command
    runCommand();

    return true;
}

bool MainWindow::dnfInstall()
{
    return dnfInstall("");
}

