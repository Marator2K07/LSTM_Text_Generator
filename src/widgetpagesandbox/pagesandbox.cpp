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

void PageSandbox::selectNewModelMode()
{
    // только если связанный радио буттон включен
    if (ui->newModelRadioButton->isChecked()) {
        _currenWorkMode = WorkMode::NEW_MODEL;
        // если память раннее была уже занята
        if (_currentModeGroupBox != nullptr) {
            delete _currentModeGroupBox;
        }
        // в заключении ставим свой виджет группировки
        _currentModeGroupBox = new NewModelGroupBox(this);
        layout()->addWidget(_currentModeGroupBox);
    }
}

PageSandbox::PageSandbox(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PageSandbox)
    , _currenWorkMode{WorkMode::NONE}
    , _currentModeGroupBox{nullptr}
{
    ui->setupUi(this);

    connect(ui->newModelRadioButton, SIGNAL(toggled(bool)),
            this, SLOT(selectNewModelMode()));
}

PageSandbox::~PageSandbox()
{
    delete ui;
}
