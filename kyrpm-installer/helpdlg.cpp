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
#include "helpdlg.h"
#include "ui_helpdlg.h"
#include <QDebug>
HelpDlg::HelpDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HelpDlg)
{
    ui->setupUi(this);
    this->setWindowTitle("help");
    listWidgetInit();
}

HelpDlg::~HelpDlg()
{
    delete ui;
}

void HelpDlg::listWidgetInit()
{
    QStringList strList;
    strList << "Overview" << "Software Installation" << "Software Uninstallation";
    ui->listWidget->addItems(strList);
}

void HelpDlg::on_listWidget_itemClicked(QListWidgetItem *item)
{
    if(item->text() == "Overview")
    {
        ui->stackedWidget->setCurrentIndex(0);
    }else if (item->text() == "Software Installation")
    {
        ui->stackedWidget->setCurrentIndex(1);
    }else if (item->text() == "Software Uninstallation")
    {
        ui->stackedWidget->setCurrentIndex(2);
    }
}
