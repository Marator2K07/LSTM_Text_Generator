#include "aboutoptimizerdialog.h"
#include "ui_aboutoptimizerdialog.h"

AboutOptimizerDialog::AboutOptimizerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutOptimizerDialog)
{
    ui->setupUi(this);
}

AboutOptimizerDialog::~AboutOptimizerDialog()
{
    delete ui;
}
