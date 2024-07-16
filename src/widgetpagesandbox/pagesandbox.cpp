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
    , ui(new Ui::PageSandbox)
    , _currenWorkMode{WorkMode::NONE}
    , _currentModeGroupBox{nullptr}
{
    ui->setupUi(this);
}

PageSandbox::~PageSandbox()
{
    delete ui;
}
