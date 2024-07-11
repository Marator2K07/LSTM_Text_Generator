#include "newmodelgroupbox.h"
#include "ui_newmodelgroupbox.h"

NewModelGroupBox::NewModelGroupBox(QWidget *parent)
    : QGroupBox(parent)
    , ui(new Ui::NewModelGroupBox)
{
    ui->setupUi(this);
}

NewModelGroupBox::~NewModelGroupBox()
{
    delete ui;
}
