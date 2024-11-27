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
#include "yumlistpackagedlg.h"
#include "ui_yumlistpackagedlg.h"
#include "DataStructDefines.h"
#include "common.h"
#include <QDebug>
#include <QPushButton>

yumlistPackageDlg::yumlistPackageDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::yumlistPackageDlg)
{
    item = new QStringListModel(this);
    ui->setupUi(this);
    ui->listView->setEditTriggers(QListView::NoEditTriggers);
    connect(ui->search_Btn,SIGNAL(clicked()), this, SLOT(searchRpm()));
    ui->search_lineEdit->setPlaceholderText(tr("input package name..."));
}

yumlistPackageDlg::~yumlistPackageDlg()
{
    delete ui;
}

bool yumlistPackageDlg::getYumlistPackages()
{
    bool ret = true;
    QString tmp;
    QStringList lst;
    Common::getTerminalOutput(QString(KYRPM_YUMPATH) + QString(KYRPM_YUM_LIST) + "|sort | tail -n +4", tmp, &lst);
    for(int i=0; i<lst.size(); i++)
    {
        QStringList strlist = lst[i].simplified().split(" ");
        QString rpm = 
        lst[i] = strlist[0].split(".")[0] + "-" + strlist[1] + "." + strlist[0].split(".")[1];
    }
    item->setStringList(lst);
    ui->listView->setModel(item);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);

    return ret;
}

void yumlistPackageDlg::searchRpm()
{
    QString tmp = ui->search_lineEdit->text();
    if(tmp.isEmpty())
    {
        getYumlistPackages();
        return;
    }

    QStringList lst;
    for(int i=0; i<item->stringList().size(); i++)
    {
        if(item->stringList()[i].contains(tmp))
            lst.append(item->stringList()[i]);
    }

    if(lst.size())
    {
        item->setStringList(lst);
        ui->listView->setModel(item);
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    }
}

void yumlistPackageDlg::on_listView_clicked(const QModelIndex &index)
{
    if(index.row()!=-1){
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    }
}

void yumlistPackageDlg::on_buttonBox_accepted()
{
    int idx = ui->listView->currentIndex().row();
    if(idx == -1){
        qInfo()<<"select error!";
        return;
    }
    qInfo()<<"selected "<<item->stringList()[idx];
    emit selectYumListPackage(item->stringList()[idx]);
}

void yumlistPackageDlg::on_search_lineEdit_returnPressed()
{
    searchRpm();
}
