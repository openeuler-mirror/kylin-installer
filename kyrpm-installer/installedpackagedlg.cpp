#include "installedpackagedlg.h"
#include "ui_installedpackagedlg.h"
#include "common.h"
#include "DataStructDefines.h"
#include <QDebug>
#include <QPushButton>

installedPackageDlg::installedPackageDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::installedPackageDlg)
{
    item = new QStringListModel(this);
    ui->setupUi(this);
}

installedPackageDlg::~installedPackageDlg()
{
    delete ui;
}

void installedPackageDlg::getPackages()
{
    QString tmp;
    QStringList lst;
    Common::getTerminalOutput(QString(KYRPM_RPMPATH) + QString(RPM_INSTALLED_PACKAGE) + "|sort", tmp, &lst);
    item->setStringList(lst);
    ui->listView->setModel(item);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
}


void installedPackageDlg::on_buttonBox_accepted()
{
    int idx = ui->listView->currentIndex().row();
    if(idx == -1){
        qInfo()<<"select error!";
        return;
    }
    qInfo()<<"selected "<<item->stringList()[idx];
    emit selectInstalledPackage(item->stringList()[idx]);
}

void installedPackageDlg::on_listView_clicked(const QModelIndex &index)
{
    if(index.row()!=-1){
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    }
}
