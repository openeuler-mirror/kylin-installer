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

