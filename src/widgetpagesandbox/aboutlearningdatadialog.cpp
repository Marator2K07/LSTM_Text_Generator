#include "aboutlearningdatadialog.h"
#include "ui_aboutlearningdatadialog.h"

AboutLearningDataDialog::AboutLearningDataDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutLearningDataDialog)
AboutLearningDataDialog::AboutLearningDataDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AboutLearningDataDialog)
    , _learningData{QString()}
    , _pathLearningData{QString()}
{
    ui->setupUi(this);
}

AboutLearningDataDialog::~AboutLearningDataDialog()
{
    delete ui;
}
