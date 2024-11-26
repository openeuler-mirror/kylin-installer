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
#include "detaildlg.h"
#include "ui_detaildlg.h"

detailDlg::detailDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::detailDlg)
{
    ui->setupUi(this);
}

detailDlg::~detailDlg()
{
    delete ui;
}

void detailDlg::setOptions(QStringList detailInfoList)
{
    ui->textEdit->clear();
    for(int i = 0; i < detailInfoList.length(); i++)
    {
        ui->textEdit->append(detailInfoList.at(i));
    }
}
