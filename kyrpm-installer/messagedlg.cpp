#include "messagedlg.h"
#include "ui_messagedlg.h"
#include <QDebug>

MessageDlg::MessageDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MessageDlg)
{
    ui->setupUi(this);
}

MessageDlg::~MessageDlg()
{
    delete ui;
}

void MessageDlg::setOptions(QStringList resultList)
{
    for(int i = 0; i < resultList.length(); i++)
    {
        ui->textEdit->append(resultList.at(i));
    }
}
