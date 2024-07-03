#include "pagemodel.h"
#include "./ui_pagemodel.h"

PageModel::PageModel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageModel)
{
    ui->setupUi(this);
}

PageModel::~PageModel()
{
    delete ui;
}
