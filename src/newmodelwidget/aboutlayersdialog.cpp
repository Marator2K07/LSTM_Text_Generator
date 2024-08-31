#include "aboutlayersdialog.h"
#include "ui_aboutlayersdialog.h"

AboutLayersDialog::AboutLayersDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutLayersDialog)
{
    ui->setupUi(this);
}

AboutLayersDialog::~AboutLayersDialog()
{
    delete ui;
}
