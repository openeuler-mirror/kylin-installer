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
#include "messagedlg.h"

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
               << ui->packageName_Label << ui->version_Label
               << ui->result_label;
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

void MainWindow::showInfoMessage(bool)
{
    MessageDlg *msgDlg = new MessageDlg();
    msgDlg->setOptions(m_resultList);
    msgDlg->show();
}

void MainWindow::initSignals()
{
    connect(ui->actionShowMessageLog,SIGNAL(triggered(bool)),this, SLOT(showInfoMessage(bool)));
    connect(ui->install_Btn,SIGNAL(clicked()), this, SLOT(dnfInstall()));
    connect(ui->actionhelp,SIGNAL(triggered(bool)), this, SLOT(help(bool)));
    connect(ui->actionOpen, SIGNAL(triggered(bool)), this, SLOT(slotFileChoose(bool)));
}

bool MainWindow::dnfInstall()
{
    RPMCommandWorker *rpmWork = new RPMCommandWorker();
    connect(rpmWork,SIGNAL(cmdEnd(QString)),this,SLOT(installEnd(QString)));
    rpmWork->setOptions(m_packagePath);
    rpmWork->start();
    return true;
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
    ui->result_label->clear();
}

void MainWindow::help(bool)
{
    HelpDlg *helpDlg = new HelpDlg();
    helpDlg->show();
}

void MainWindow::installEnd(QString result)
{
    ui->result_label->setText("安装成功");
    m_resultList = result.split("\n");
}

