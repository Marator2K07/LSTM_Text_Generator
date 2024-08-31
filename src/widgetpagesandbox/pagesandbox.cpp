#include "pagesandbox.h"
#include "ui_pagesandbox.h"

void PageSandbox::chooseModelTrain()
{
    layout()->addWidget(_modelTrainGroupBox);
    layout()->removeWidget(_newModelGroupBox);
    _modelTrainGroupBox->show();
    _newModelGroupBox->hide();
}

void PageSandbox::chooseNewModel()
{
    layout()->addWidget(_newModelGroupBox);
    layout()->removeWidget(_modelTrainGroupBox);
    _modelTrainGroupBox->hide();
    _newModelGroupBox->show();
}

PageSandbox::PageSandbox(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PageSandbox)
    , _currenWorkMode{WorkMode::NONE}
    , _modelTrainGroupBox{new ModelTrainingGroupBox(this)}
    , _newModelGroupBox{new NewModelGroupBox(this)}
{
    ui->setupUi(this);

    _modelTrainGroupBox->hide();
    _newModelGroupBox->hide();
}

PageSandbox::~PageSandbox()
{
    delete ui;
}
