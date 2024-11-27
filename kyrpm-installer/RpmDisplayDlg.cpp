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
#include <QFileDialog>
#include <QMessageBox>

#include "RpmDisplayDlg.h"
#include "ui_RpmDisplayDlg.h"

#include "GetRPMInfoBackend.h"
#include <QDebug>

RpmDisplayDlg::RpmDisplayDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RpmDisplayDlg)
{
    ui->setupUi(this);

    m_strPath = "";
    initUI();

}

RpmDisplayDlg::~RpmDisplayDlg()
{
    delete ui;
}

void RpmDisplayDlg::slotFileChoose()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);

    QStringList path;
    if(dialog.exec())
        path = dialog.selectedFiles();

    if(path.isEmpty() || path.at(0).isEmpty()) {
        QMessageBox::information(nullptr, tr("Error"), tr("Please check the directory! The directory can not be \"/\" or empty.") );
        return;
    }

    m_strPath = path.at(0);
}

void RpmDisplayDlg::initUI()
{
    if(m_strPath.isEmpty()){
        slotFileChoose();
    }

    getRPMInfo(m_strPath);

    ui->packageNameLabel->setText(m_info.getInfo(RPMInfo::RPMINFO_KEY::name));
    ui->summaryLabel->setText(m_info.getInfo(RPMInfo::RPMINFO_KEY::summary));
    ui->versionLabel->setText(m_info.getInfo(RPMInfo::RPMINFO_KEY::version) + "-" + m_info.getInfo(RPMInfo::RPMINFO_KEY::release));

    ui->desLabel->setWordWrap(true);
    ui->desLabel->setText(m_info.getInfo(RPMInfo::RPMINFO_KEY::description));

    ui->webLabel->setOpenExternalLinks(true);
    QString webLabelText = QString("<a style='color: blue; text-decoration: none' href=\"%1\">website").arg(m_info.getInfo(RPMInfo::RPMINFO_KEY::URL));
    ui->webLabel->setText(webLabelText);
    ui->webLabel->setToolTip(m_info.getInfo(RPMInfo::RPMINFO_KEY::URL));
}

bool RpmDisplayDlg::getRPMInfo(QString filePath)
{
    GetRPMInfoBackend *backend = GetRPMInfoBackend::getInstance();
    m_info.clear();

    filePath = "test";
    return backend->
            getRPMInfoFromPackage(m_info,filePath);
}
