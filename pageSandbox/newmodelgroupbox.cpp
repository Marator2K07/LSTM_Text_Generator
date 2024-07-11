#include "newmodelgroupbox.h"
#include "ui_newmodelgroupbox.h"

long NewModelGroupBox::LAYERS_CREATED = 0;

void NewModelGroupBox::addNewLayer()
{
    // добавляем новую строку
    int row = ui->layersTableWidget->rowCount();
    ui->layersTableWidget->insertRow(row);
    // начальные виджеты для инициализации:
    QTableWidgetItem *initName
        = new QTableWidgetItem(QString("Layer%1").arg(LAYERS_CREATED++));
    QDoubleSpinBox *initScale = new QDoubleSpinBox();
    initScale->setRange(0.001, 0.1);
    initScale->setDecimals(3);
    initScale->setSingleStep(0.001);
    QSpinBox *initHiddenSize = new QSpinBox();
    initHiddenSize->setRange(16, 512);
    // стоит также добавить кнопку для удаления данной строки
    QPushButton *deleteBtn = new QPushButton("Убрать");
    deleteBtn->setFont(QFont("Bahnschrift SemiCondensed", 12));
    deleteBtn->setSizePolicy(QSizePolicy::Maximum,
                             QSizePolicy::Maximum);
    // ставим их в столбцы
    ui->layersTableWidget->setItem(
        row,
        (int)ColumnName::NAME,
        initName
        );
    ui->layersTableWidget->setCellWidget(
        row,
        (int)ColumnName::SCALE,
        initScale
        );
    ui->layersTableWidget->setCellWidget(
        row,
        (int)ColumnName::HIDDEN_SIZE,
        initHiddenSize
        );
    ui->layersTableWidget->setCellWidget(
        row,
        (int)ColumnName::DELETE_BUTTON,
        deleteBtn
        );
}

NewModelGroupBox::NewModelGroupBox(QWidget *parent)
    : QGroupBox(parent)
    , ui(new Ui::NewModelGroupBox)
{
    ui->setupUi(this);

    connect(ui->newLayerButton, SIGNAL(pressed()),
            this, SLOT(addNewLayer()));
}

NewModelGroupBox::~NewModelGroupBox()
{
    delete ui;
}
