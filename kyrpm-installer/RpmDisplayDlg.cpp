#include "RpmDisplayDlg.h"
#include "ui_RpmDisplayDlg.h"

#include "GetRPMInfoBackend.h"

RpmDisplayDlg::RpmDisplayDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RpmDisplayDlg)
{
    ui->setupUi(this);

    GetRPMInfoBackend *backend = GetRPMInfoBackend::getInstance();
    RPMinfo info;
    QString strPath = "test";
    backend->getRPMInfoFromPackage(info,strPath);

}

RpmDisplayDlg::~RpmDisplayDlg()
{
    delete ui;
}
