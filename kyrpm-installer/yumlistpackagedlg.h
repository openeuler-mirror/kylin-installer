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
#ifndef YUMLISTPACKAGEDLG_H
#define YUMLISTPACKAGEDLG_H

#include <QDialog>
#include <QStringListModel>

namespace Ui {
class yumlistPackageDlg;
}


class yumlistPackageDlg: public QDialog
{
    Q_OBJECT

public:
    explicit yumlistPackageDlg(QWidget *parent = nullptr);
    ~yumlistPackageDlg();
    
    bool  getYumlistPackages();
private:
    Ui::yumlistPackageDlg *ui;
    QStringListModel *item;
signals:
    void selectYumListPackage(QString);
public slots:
    void searchRpm();    
    void on_listView_clicked(const QModelIndex &index);
    void on_buttonBox_accepted();
private slots:
    void on_search_lineEdit_returnPressed();
};

#endif // YUMLISTPACKAGEDLG_H
