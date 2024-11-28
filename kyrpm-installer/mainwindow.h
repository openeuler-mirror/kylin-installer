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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QTextEdit>
#include <QLabel>
#include <QPushButton>
#include "RpmDisplayWidget.h"
#include "helpdlg.h"
#include "detaildlg.h"
#include "versiondlg.h"
#include "messagedlg.h"
#include "installedpackagedlg.h"
#include "yumlistpackagedlg.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void showInfoMessage(bool);
    bool dnfInstall();
    void installEnd(QString result,int exitCode);
    void slotFileChoose(bool);
    void getyumlists(bool);
    void help(bool);
    void displayVersion(bool);
    void displayDetailInfo();
    void displayInstalledPackage(bool);
    void selectInstalledPackage(QString);
    void selectYumListPackage(QString);
    bool dnfUninstall();
    void UninstallEnd(QString result,int exitCode);
    void on_web_Btn_clicked();

private:
    void initSignals();
    void initUI();
    void hideUI();
    void showUI();
    void displayPackageInfo(QString packagePath);
    void displayYumListPackage(QString package);
    QList<QTextEdit *> edt_list;
    QList<QLabel *> label_list;
    QList<QPushButton *> btn_list;

private:
    Ui::MainWindow *ui;
    QProcess *m_process;
    RpmDisplayWidget* m_infoWidget;

    QString m_packagePath;
    QStringList m_resultList;

    HelpDlg *helpWindow;
    VersionDlg *versionWindow;
    detailDlg *detailWindow;
    MessageDlg *messageWindow;
    installedPackageDlg *installedWindow;
    yumlistPackageDlg*   yumlistWindow;
    QMovie *installMove;
    QMovie *uninstallMove;


protected:
    void closeEvent(QCloseEvent *event) override;
};
#endif // MAINWINDOW_H
