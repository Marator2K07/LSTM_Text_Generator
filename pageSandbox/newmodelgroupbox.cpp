#include "newmodelgroupbox.h"
#include "ui_newmodelgroupbox.h"

long NewModelGroupBox::LAYERS_CREATED = 0;

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
