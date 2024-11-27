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
#ifndef INSTALLEDPACKAGEDLG_H
#define INSTALLEDPACKAGEDLG_H

#include <QDialog>
#include <QStringListModel>

namespace Ui {
class installedPackageDlg;
}

class installedPackageDlg : public QDialog
{
    Q_OBJECT

public:
    explicit installedPackageDlg(QWidget *parent = nullptr);
    ~installedPackageDlg();
    void getPackages();
signals:
    void selectInstalledPackage(QString);

private slots:
    void on_buttonBox_accepted();

    void on_listView_clicked(const QModelIndex &index);
    void searchRpm();

private:
    Ui::installedPackageDlg *ui;
    QStringListModel *item;
};

#endif // INSTALLEDPACKAGEDLG_H
