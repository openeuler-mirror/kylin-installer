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
#ifndef RPMDISPLAYDLG_H
#define RPMDISPLAYDLG_H

#include <QDialog>
#include <DataStructDefines.h>

namespace Ui {
class RpmDisplayDlg;
}

//local rpm package installer

class RpmDisplayDlg : public QDialog
{
    Q_OBJECT

public:
    explicit RpmDisplayDlg(QWidget *parent = nullptr);
    ~RpmDisplayDlg();

private slots:
    void slotFileChoose();

private:
    void initUI();
    bool getRPMInfo(QString filePath);

    Ui::RpmDisplayDlg *ui;
    RPMInfo m_info;
    QString m_strPath;
};

#endif // RPMDISPLAYDLG_H
