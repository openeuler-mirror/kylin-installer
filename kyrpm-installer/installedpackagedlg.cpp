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
#include "installedpackagedlg.h"
#include "ui_installedpackagedlg.h"
#include "common.h"
#include "DataStructDefines.h"
#include <QDebug>
#include <QPushButton>

installedPackageDlg::installedPackageDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::installedPackageDlg)
{
    item = new QStringListModel(this);
    ui->setupUi(this);
    ui->listView->setEditTriggers(QListView::NoEditTriggers);
    connect(ui->search_Btn,SIGNAL(clicked()), this, SLOT(searchRpm()));
    ui->search_lineEdit->setPlaceholderText(tr("input package name..."));
}

installedPackageDlg::~installedPackageDlg()
{
    delete ui;
}

void installedPackageDlg::getPackages()
{
    QString tmp;
    QStringList lst;
    Common::getTerminalOutput(QString(KYRPM_RPMPATH) + QString(RPM_INSTALLED_PACKAGE) + "|sort", tmp, &lst);
    item->setStringList(lst);
    ui->listView->setModel(item);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
}


void installedPackageDlg::on_buttonBox_accepted()
{
    int idx = ui->listView->currentIndex().row();
    if(idx == -1){
        qInfo()<<"select error!";
        return;
    }
    qInfo()<<"selected "<<item->stringList()[idx];
    emit selectInstalledPackage(item->stringList()[idx]);
}

void installedPackageDlg::on_listView_clicked(const QModelIndex &index)
{
    if(index.row()!=-1){
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    }
}

void installedPackageDlg::searchRpm()
{
    QString tmp;
    if(ui->search_lineEdit->text().isEmpty())
    {
        tmp = "-";
    }else{
        tmp = ui->search_lineEdit->text();
    }
    ui->listView->model()->removeRows(0,ui->listView->model()->rowCount());

    QStringList lst;
    Common::getTerminalOutput(QString(KYRPM_RPMPATH) + QString(RPM_INSTALLED_PACKAGE) + "|grep " + tmp, tmp, &lst);
    item->setStringList(lst);
    ui->listView->setModel(item);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
}

void installedPackageDlg::on_search_lineEdit_returnPressed()
{
    searchRpm();
}
