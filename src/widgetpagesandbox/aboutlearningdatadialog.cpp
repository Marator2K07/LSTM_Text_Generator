#include "aboutlearningdatadialog.h"
#include "ui_aboutlearningdatadialog.h"

AboutLearningDataDialog::AboutLearningDataDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutLearningDataDialog)
{
    ui->setupUi(this);
}

AboutLearningDataDialog::~AboutLearningDataDialog()
{
    delete ui;
}
