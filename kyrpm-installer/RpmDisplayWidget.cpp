#include "RpmDisplayWidget.h"
#include "ui_RpmDisplayWidget.h"

RpmDisplayWidget::RpmDisplayWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RpmDisplayWidget)
{
    ui->setupUi(this);
}

RpmDisplayWidget::~RpmDisplayWidget()
{
    delete ui;
}
