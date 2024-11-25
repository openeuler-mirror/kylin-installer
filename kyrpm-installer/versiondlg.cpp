#include "versiondlg.h"
#include "ui_versiondlg.h"
#include "DataStructDefines.h"

VersionDlg::VersionDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VersionDlg)
{
    ui->setupUi(this);
    this->setWindowTitle("version");
    ui->version_label->setText(QString(VERSION));
}

VersionDlg::~VersionDlg()
{
    delete ui;
}
