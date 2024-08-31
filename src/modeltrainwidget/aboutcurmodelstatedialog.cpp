#include "aboutcurmodelstatedialog.h"
#include "ui_aboutcurmodelstatedialog.h"

AboutCurModelStateDialog::AboutCurModelStateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutCurModelStateDialog)
{
    ui->setupUi(this);
}

AboutCurModelStateDialog::~AboutCurModelStateDialog()
{
    delete ui;
}
