#include "modeltraininggroupbox.h"
#include "ui_modeltraininggroupbox.h"

ModelTrainingGroupBox::ModelTrainingGroupBox(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::ModelTrainingGroupBox)
{
    ui->setupUi(this);
}

ModelTrainingGroupBox::~ModelTrainingGroupBox()
{
    delete ui;
}
