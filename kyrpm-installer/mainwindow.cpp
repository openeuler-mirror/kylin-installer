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
#include <QDesktopServices>
#include <QFileDialog>
#include <QMessageBox>

#include "RPMCommandWorker.h"
#include "common.h"
#include <QMovie>
#include "GetRPMInfoBackend.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_process = nullptr;
    m_infoWidget = nullptr;
    helpWindow = new HelpDlg();
    versionWindow = new VersionDlg();
    detailWindow = new detailDlg();
    messageWindow = new MessageDlg();
    installedWindow = new installedPackageDlg();
    yumlistWindow = new yumlistPackageDlg();
    //ui->textEdit->hide();
    this->setWindowTitle("rpm installer");

    initSignals();
    label_list << ui->label_name << ui->label_summary
               << ui->label_version << ui->label_description
               << ui->packageName_Label << ui->version_Label
               << ui->result_label;
    btn_list << ui->web_Btn << ui->install_Btn << ui->detail_Btn << ui->uninstall_Btn;
    edt_list << ui->summary_textEdit << ui->description_textEdit;
    ui->summary_textEdit->setReadOnly(true);
    ui->description_textEdit->setReadOnly(true);
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

void MainWindow::showInfoMessage(bool)
{
    messageWindow->setOptions(m_resultList);
    messageWindow->show();
    messageWindow->activateWindow();
}

void MainWindow::initSignals()
{
    connect(ui->actionShowMessageLog,SIGNAL(triggered(bool)),this, SLOT(showInfoMessage(bool)));
    connect(ui->install_Btn,SIGNAL(clicked()), this, SLOT(dnfInstall()));
    connect(ui->actionhelp,SIGNAL(triggered(bool)), this, SLOT(help(bool)));
    connect(ui->actionOpen, SIGNAL(triggered(bool)), this, SLOT(slotFileChoose(bool)));
    connect(ui->actionYum_list, SIGNAL(triggered(bool)), this, SLOT(getyumlists(bool)));
    connect(ui->actionVersion, SIGNAL(triggered(bool)), this, SLOT(displayVersion(bool)));
    connect(ui->web_Btn, SIGNAL(clicked()), this, SLOT(on_web_Btn_clicked()));
    connect(ui->detail_Btn, SIGNAL(clicked()), this, SLOT(displayDetailInfo()));
    connect(ui->actionSelect_installed_package, SIGNAL(triggered(bool)), this, SLOT(displayInstalledPackage(bool)));
    connect(ui->uninstall_Btn,SIGNAL(clicked()), this, SLOT(dnfUninstall()));
}

void MainWindow::selectInstalledPackage(QString pkgName)
{
    m_packagePath = pkgName;
    ui->install_Btn->setEnabled(false);
    ui->uninstall_Btn->setEnabled(true);
    displayPackageInfo(m_packagePath);
}

void MainWindow::selectYumListPackage(QString pkgName)
{
    m_yumlistPackage = pkgName;
    displayYumListPackage(m_yumlistPackage);
}

bool MainWindow::dnfInstall()
{
    QFile packageFilePath(m_packagePath);
    if(!packageFilePath.exists())
    {
        QMessageBox::information(nullptr, tr("Error"), tr("rpm file is not exist！") );
        return false;
    }
    RPMInfo info;
    GetRPMInfoBackend *backend = GetRPMInfoBackend::getInstance();
    backend->getRPMInfoFromPackage(info, m_packagePath);
    QString tmpAllInfo,tmp;
    QStringList rpmNVSAllInfo,rpmNVS;
    int exitCode;
    Common::getTerminalOutput(QString(KYRPM_RPMPATH) + QString(RPM_NVS) + m_packagePath
                                + QString(" 2> /dev/null"), tmpAllInfo, &rpmNVSAllInfo, &exitCode);
    Common::getTerminalOutput(QString(KYRPM_RPMPATH) + QString(RPM_QI) + rpmNVSAllInfo[0]
                                + QString(" 2> /dev/null"), tmp, &rpmNVS, &exitCode);
    RPMCommandWorker::ACTION_TYPE action = RPMCommandWorker::ACTION_TYPE::install;
    if(exitCode == 0){
        if(QMessageBox::question(nullptr, "question", "this package has been installed, reinstall it?", QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes){
            action = RPMCommandWorker::ACTION_TYPE::reinstall;
        }else{
            return false;
        }
    }
    installMove = new QMovie(":/image/movie.gif");
    ui->move_label->setMovie(installMove);
    ui->move_label->show();
    installMove->start();
    ui->result_label->clear();

    ui->install_Btn->setEnabled(false);
    RPMCommandWorker *rpmWork = new RPMCommandWorker();
    connect(rpmWork,SIGNAL(cmdEnd(QString,int)),this,SLOT(installEnd(QString,int)));
    rpmWork->setOptions(m_packagePath, action);
    rpmWork->start();
    return true;
}

bool MainWindow::dnfUninstall()
{
    uninstallMove = new QMovie(":/image/movie.gif");
    ui->move_label->setMovie(uninstallMove);
    ui->move_label->show();
    uninstallMove->start();
    ui->result_label->clear();

    ui->uninstall_Btn->setEnabled(false);
    RPMCommandWorker *rpmWork = new RPMCommandWorker();
    connect(rpmWork, SIGNAL(cmdEnd(QString,int)), this, SLOT(UninstallEnd(QString, int)));
    rpmWork->setOptions(m_packagePath, RPMCommandWorker::ACTION_TYPE::remove);
    rpmWork->start();
    return true;
}

void MainWindow::slotFileChoose(bool)
{
    QStringList path = QFileDialog::getOpenFileNames(this,
                                                     tr("Select RPM File"),
                                                     "/home",
                                                     tr("RPM Files (*.rpm);;All Files (*)"));

    if(path.isEmpty()) {
        return;
    }

    if(path.at(0).isEmpty()) {
        QMessageBox::information(nullptr, tr("Error"), tr("Please check again!") );
        return;
    }

    m_packagePath = path.at(0);

    QFileInfo fileInfo(m_packagePath);
    if(fileInfo.suffix() != "rpm" && fileInfo.suffix() != "src.rpm")
    {
        QMessageBox::information(nullptr, tr("Error"), tr("the file is not rpm package！") );
        return ;
    }

    QString rpmArch,osArch;
    Common::getTerminalOutput(QString(KYRPM_RPMPATH) + QString(RPM_ARCH) + m_packagePath
                                + QString(" 2> /dev/null"), rpmArch);
    Common::getTerminalOutput("arch", osArch, nullptr);
    osArch = osArch.trimmed();
    qInfo()<<rpmArch<<osArch;
    if(rpmArch != osArch && rpmArch != "noarch" )
    {
        QMessageBox::information(nullptr, tr("Error"), tr("os arch and rpm arch are inconsistent！") );
        return ;
    }
    ui->uninstall_Btn->setEnabled(false);
    ui->install_Btn->setEnabled(true);
    displayPackageInfo(m_packagePath);
}

void MainWindow::getyumlists(bool)
{
    yumlistWindow->setWindowTitle("yum Packages List, select one to install or update");
    yumlistWindow->getYumlistPackages();
    yumlistWindow->show();
    yumlistWindow->activateWindow();
    connect(yumlistWindow, SIGNAL(selectYumListPackage(QString)), this, SLOT(selectYumListPackage(QString)));
}

void MainWindow::displayPackageInfo(QString packagePath)
{
    QString rpmDescription;
    QStringList rpmNVS;
    Common::getTerminalOutput(QString(KYRPM_RPMPATH) + QString(RPM_NVS) + packagePath
                                + QString(" 2> /dev/null"), rpmDescription, &rpmNVS);
    Common::getTerminalOutput(QString(KYRPM_RPMPATH) + QString(RPM_DESCRIPTION) + packagePath
                                + QString(" 2> /dev/null"), rpmDescription);

    ui->packageName_Label->setText(rpmNVS[0]);
    ui->version_Label->setText(rpmNVS[1]);
    ui->summary_textEdit->setText(rpmNVS[2]);
    ui->description_textEdit->setText(rpmDescription);
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
    ui->result_label->clear();
}

void MainWindow::help(bool)
{
    helpWindow->show();
    helpWindow->activateWindow();
}

void MainWindow::installEnd(QString result,int exitCode)
{
    if(exitCode == 0)
    {
        ui->result_label->setText("install success");
        ui->install_Btn->setEnabled(false);
        ui->uninstall_Btn->setEnabled(false);
    }else
    {
       ui->result_label->setText("install failed");
       ui->install_Btn->setEnabled(true);
       ui->uninstall_Btn->setEnabled(false);
    }
    m_resultList = result.split("\n");
    installMove->stop();
    ui->move_label->hide();
}

void MainWindow::UninstallEnd(QString result,int exitCode)
{
    if(exitCode == 0){
        ui->result_label->setText("uninstall success");
        ui->install_Btn->setEnabled(false);
        ui->uninstall_Btn->setEnabled(false);
    }else
    {
        ui->result_label->setText("uninstall failed");
        ui->install_Btn->setEnabled(false);
        ui->uninstall_Btn->setEnabled(true);
    }
    m_resultList = result.split("\n");
    uninstallMove->stop();
    ui->move_label->hide();
}

void MainWindow::displayYumListPackage(QString package)
{
    QString rpmName;
    QString yumrpmVersionReleaseArch;
    QString rpmVersionReleaseArch;
    QString result;
    QStringList resultList;
    QString installedFlag = "(not install)";
    Common::getTerminalOutput(QString(KYRPM_YUMPATH) + KYRPM_YUM_INFO + package, result, &resultList);

    for(int i=2; i<resultList.size(); i++)
    {
        QString tmp = resultList[i];
        if(tmp.contains("Name"))
        {
            rpmName = tmp.split(":")[1].trimmed();
            continue;
        }
        
        if(tmp.contains("Version"))
        {
            yumrpmVersionReleaseArch = tmp.split(":")[1].trimmed()+ "-" + resultList[i+1].split(":")[1].trimmed() + "." + resultList[i+2].split(":")[1].trimmed();
            i += 2;
            continue;
        }

        if(tmp.contains("Summary"))
        {
            QString strSummary;
            int j=i;
            for(; j<resultList.size(); j++)
            {
                strSummary += resultList[j].split(":")[1].trimmed()+" ";
                if(resultList[j+1].split(":")[0].trimmed().size()>0)
                    break;
            }
            j = i;
            ui->summary_textEdit->setText(strSummary);
            continue;
        }

        if(tmp.contains("Description"))
        {
            QString strDescription;
            for(int j=i; j<resultList.size(); j++)
            {
                strDescription += resultList[j].split(":")[1].trimmed()+" ";
            }
            ui->description_textEdit->setText(strDescription);
            break;
        }
    }  

    Common::getTerminalOutput(QString(KYRPM_RPMPATH) + RPM_QI + rpmName, result, &resultList);

    for(int i=0; i<resultList.size(); i++)
    {
        if(resultList[i].contains("Version"))
        {
            rpmVersionReleaseArch = resultList[i].split(":")[1].trimmed()+ "-" + resultList[i+1].split(":")[1].trimmed() + "." + resultList[i+2].split(":")[1].trimmed();
        }
        else if(resultList[i].contains("Install Date"))
        {
            installedFlag = "(installed)";
            break;
        }
    }

    if((installedFlag == "(installed)") && (rpmVersionReleaseArch == yumrpmVersionReleaseArch))
    {
        ui->install_Btn->setEnabled(false);
        ui->uninstall_Btn->setEnabled(true);
    }
    else if(installedFlag == "(installed)")
    {
        ui->install_Btn->setEnabled(true);
        ui->uninstall_Btn->setEnabled(true);       
    }

    ui->packageName_Label->setText(rpmName + installedFlag);
    ui->version_Label->setText(yumrpmVersionReleaseArch);

    showUI();
}    

void MainWindow::displayVersion(bool)
{
    versionWindow->show();
    versionWindow->activateWindow();
}

void MainWindow::displayInstalledPackage(bool)
{
    installedWindow->setWindowTitle("Installed Packages List, select one to uninstall");
    installedWindow->getPackages();
    installedWindow->show();
    installedWindow->activateWindow();
    connect(installedWindow, SIGNAL(selectInstalledPackage(QString)), this, SLOT(selectInstalledPackage(QString)));
}

void MainWindow::displayDetailInfo()
{
    QString rpmInfoStr;
    QStringList rpmInfoList;
    Common::getTerminalOutput(QString(KYRPM_RPMPATH) + QString(RPM_QI) + m_packagePath, rpmInfoStr, &rpmInfoList);
    detailWindow->setOptions(rpmInfoList);
    detailWindow->show();
    detailWindow->activateWindow();

}

void MainWindow::closeEvent(QCloseEvent *event) {
    if (helpWindow) {
        helpWindow->close();
    }
    if (versionWindow) {
        versionWindow->close();
    }
    if (detailWindow) {
        detailWindow->close();
    }
    if (messageWindow) {
        messageWindow->close();
    }
    if(installedWindow) {
        installedWindow->close();
    }
    QMainWindow::closeEvent(event);
}

void MainWindow::on_web_Btn_clicked()
{
    RPMInfo info;
    GetRPMInfoBackend *backend = GetRPMInfoBackend::getInstance();
    info.clear();
    backend->getRPMInfoFromPackage(info, m_packagePath);
    qDebug()<<"open url: "<<info.getInfo(RPMInfo::RPMINFO_KEY::URL);
    QDesktopServices::openUrl(QUrl(info.getInfo(RPMInfo::RPMINFO_KEY::URL)));
}
