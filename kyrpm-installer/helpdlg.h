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
#ifndef HELPDLG_H
#define HELPDLG_H

#include <QDialog>
#include <QListWidgetItem>
namespace Ui {
class HelpDlg;
}

class HelpDlg : public QDialog
{
    Q_OBJECT

public:
    explicit HelpDlg(QWidget *parent = nullptr);
    ~HelpDlg();

private slots:
    void on_listWidget_itemClicked(QListWidgetItem *item);

private:
    Ui::HelpDlg *ui;
    void listWidgetInit();
};

#endif // HELPDLG_H
