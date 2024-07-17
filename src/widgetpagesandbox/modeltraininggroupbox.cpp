#include "modeltraininggroupbox.h"
#include "ui_modeltraininggroupbox.h"


void ModelTrainingGroupBox::chooseCurrentModel()
{
    QString currentModelPath = QFileDialog::getExistingDirectory(
        this,
        "Выбор директории с существующей моделью для обучения",
        QString()
        );
    ui->currentModelLineEdit->setText(currentModelPath);
}

ModelTrainingGroupBox::ModelTrainingGroupBox(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::ModelTrainingGroupBox)
{
    ui->setupUi(this);

    connect(ui->chooseCurrentModelButton, SIGNAL(pressed()),
            this, SLOT(chooseCurrentModel()));
}

ModelTrainingGroupBox::~ModelTrainingGroupBox()
{
    delete ui;
}
