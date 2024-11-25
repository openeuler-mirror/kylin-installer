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
#include <QFileDialog>
#include <QMessageBox>

#include "RPMCommandWorker.h"
#include "common.h"
#include "helpdlg.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_process = nullptr;
    m_infoWidget = nullptr;
    //ui->textEdit->hide();
    this->setWindowTitle("rpm installer");

    initSignals();
    label_list << ui->label_name << ui->label_summary
               << ui->label_version << ui->label_description
               << ui->packageName_Label << ui->version_Label;
    btn_list << ui->web_Btn << ui->install_Btn << ui->detail_Btn;
    edt_list << ui->summary_textEdit << ui->description_textEdit;
    hideUI();
}

MainWindow::~MainWindow()
{
    if(m_process != nullptr)
    {
        delete m_process;
        m_process = nullptr;
    }

    if(m_infoWidget != nullptr)
    {
        delete m_infoWidget;
        m_infoWidget = nullptr;
    }

    delete ui;
}

void MainWindow::showInfoMessage(bool isShown)
{
    qDebug()<<"test++++++++++++++++"<< isShown;
    //ui->textEdit->setVisible(isShown);
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
    //connect(ui->actionShowMessageLog,SIGNAL(triggered(bool)),this, SLOT(showInfoMessage(bool)));
    //connect(ui->installButton,SIGNAL(clicked()), this, SLOT(dnfInstall()));
    connect(ui->actionhelp,SIGNAL(triggered(bool)), this, SLOT(help(bool)));
    connect(ui->actionOpen, SIGNAL(triggered(bool)), this, SLOT(slotFileChoose(bool)));
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

void MainWindow::slotFileChoose(bool)
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    const QStringList filters({"RPM files (*.rpm)",
                                "Any files (*)"
                               });
    dialog.setNameFilters(filters);

    QStringList path;
    if(dialog.exec())
        path = dialog.selectedFiles();

    if(path.isEmpty()) {
        QMessageBox::information(nullptr, tr("Error"), tr("Please check again!") );
        return;
    }

    QString newPath = path.at(0);
    if(newPath.isEmpty()) {
        QMessageBox::information(nullptr, tr("Error"), tr("Please check again!") );
        return;
    }

    m_packagePath = newPath;

    displayPackageInfo(m_packagePath);
}

void MainWindow::displayPackageInfo(QString packagePath)
{
    QFile packageFilePath(packagePath);
    if(!packageFilePath.exists())
    {
        QMessageBox::information(nullptr, tr("Error"), tr("Please check the directory！ The directory can not be \"/\" or empty.") );
        return ;
    }
    QString rpmName,rpmVersion,rpmInfo;
    QStringList rpmNameList,rpmVersionList,rpmSummary,rpmInfoList;
    Common::getTerminalOutput(QString(KYRPM_RPMPATH) + QString(RPM_NAME) + packagePath, rpmName, &rpmNameList);
    Common::getTerminalOutput(QString(KYRPM_RPMPATH) + QString(RPM_VERSION) + packagePath, rpmVersion, &rpmVersionList);
    Common::getTerminalOutput(QString(KYRPM_RPMPATH) + " -qpi " + packagePath, rpmInfo, &rpmInfoList);
    qInfo()<<rpmName<<rpmVersion<<rpmInfoList.at(15).split(":").at(1);

    ui->packageName_Label->setText(rpmName);
    ui->version_Label->setText(rpmVersion);
    ui->summary_textEdit->setText(rpmInfoList.at(15).split(":").at(1));
    ui->description_textEdit->setText(rpmInfoList.at(17));
    showUI();
}

void MainWindow::hideUI()
{
    for (int i = 0; i < label_list.length(); i++) {
        QLabel* label = label_list.at(i);
        label->hide();
    }

    for (int i = 0; i < btn_list.length(); i++) {
        QPushButton* btn = btn_list.at(i);
        btn->hide();
    }

    for (int i = 0; i < edt_list.length(); i++) {
        QTextEdit* edt = edt_list.at(i);
        edt->hide();
    }
}

void MainWindow::showUI()
{
    for (int i = 0; i < label_list.length(); i++) {
        QLabel* label = label_list.at(i);
        label->show();
    }

    for (int i = 0; i < btn_list.length(); i++) {
        QPushButton* btn = btn_list.at(i);
        btn->show();
    }

    for (int i = 0; i < edt_list.length(); i++) {
        QTextEdit* edt = edt_list.at(i);
        edt->show();
    }
}

void MainWindow::help(bool)
{
    HelpDlg *helpDlg = new HelpDlg();
    helpDlg->show();
}



