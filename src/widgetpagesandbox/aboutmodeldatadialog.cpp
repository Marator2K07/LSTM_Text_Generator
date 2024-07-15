#include "aboutmodeldatadialog.h"
#include "ui_aboutmodeldatadialog.h"

AboutModelDataDialog::AboutModelDataDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutModelDataDialog)
{
    ui->setupUi(this);
}

AboutModelDataDialog::~AboutModelDataDialog()
{
    delete ui;
}
