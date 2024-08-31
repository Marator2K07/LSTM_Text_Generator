#include "abouttrainingdialog.h"
#include "ui_abouttrainingdialog.h"

AboutTrainingDialog::AboutTrainingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutTrainingDialog)
{
    ui->setupUi(this);
}

AboutTrainingDialog::~AboutTrainingDialog()
{
    delete ui;
}
