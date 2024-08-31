#include "pagesandbox.h"
#include "ui_pagesandbox.h"

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
