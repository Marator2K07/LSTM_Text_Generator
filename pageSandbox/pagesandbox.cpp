#include "pagesandbox.h"
#include "ui_pagesandbox.h"

PageSandbox::PageSandbox(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PageSandbox)
{
    ui->setupUi(this);
}

PageSandbox::~PageSandbox()
{
    delete ui;
}
