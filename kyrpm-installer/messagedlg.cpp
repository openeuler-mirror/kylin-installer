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
#include "messagedlg.h"
#include "ui_messagedlg.h"
#include <QDebug>
#include <QTextCursor>

MessageDlg::MessageDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MessageDlg)
{
    ui->setupUi(this);
    ui->textEdit->setReadOnly(true);
}

MessageDlg::~MessageDlg()
{
    delete ui;
}

void MessageDlg::setOptions(QStringList resultList)
{
    ui->textEdit->clear();
    for(int i = 0; i < resultList.length(); i++)
    {
        ui->textEdit->append(resultList.at(i));
    }
    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.movePosition(QTextCursor::Start);
    ui->textEdit->setTextCursor(cursor);
}
