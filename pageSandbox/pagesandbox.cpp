#include "pagesandbox.h"
#include "ui_pagesandbox.h"

void PageSandbox::cleanGroupBox(QGroupBox *groupBox)
{
    QObjectList children = groupBox->children();
    if (children.size() != 0) {
        for (QObject *child : children) {
            child->disconnect(); // на всякий случай рвем все связи
            delete child; // и удаляем ребенка
        }
    }
}

PageSandbox::PageSandbox(QWidget *parent)
    : QWidget(parent)
    , _currenWorkMode{WorkMode::NONE}
    , ui(new Ui::PageSandbox)
{
    ui->setupUi(this);
}

PageSandbox::~PageSandbox()
{
    delete ui;
}
