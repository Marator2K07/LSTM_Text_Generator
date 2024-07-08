#include "pagemodel.h"
#include "./ui_pagemodel.h"

PageModel::PageModel(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PageModel)
    , _dirModelView(nullptr)
{
    ui->setupUi(this);

    connect(ui->chooseFolderButton, SIGNAL(pressed()),
            this, SLOT(openFolderWithModels()));
}

PageModel::~PageModel()
{
    delete ui;
}
