#include "newmodelgroupbox.h"
#include "ui_newmodelgroupbox.h"

long NewModelGroupBox::LAYERS_CREATED = 0;

void NewModelGroupBox::chooseLearningData()
{
    QString fileName = QFileDialog::getOpenFileName(
        this,
        "Выбор обучающих данных",
        QString(),
        "Text files (*.txt)"
        );
    ui->embeddingDataPathLineEdit->setText(fileName);
}

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
    connect(deleteBtn, SIGNAL(pressed()),
            this, SLOT(deleteSelectedLayer())); // само удаление    
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
    // вручную подвправляем размеры(ширину) колонок
    ui->layersTableWidget->setColumnWidth((int)ColumnName::NAME, 65);
    ui->layersTableWidget->setColumnWidth((int)ColumnName::SCALE, 105);
    ui->layersTableWidget->setColumnWidth((int)ColumnName::HIDDEN_SIZE, 85);
    ui->layersTableWidget->setColumnWidth((int)ColumnName::DELETE_BUTTON, 65);
}

void NewModelGroupBox::deleteSelectedLayer()
{
    int row = ui->layersTableWidget->currentRow();
    // получаем нажатую кнопку удаления и чистим ее
    QPushButton *deleteBtn = (QPushButton*)QObject::sender();
    deleteBtn->disconnect();
    delete deleteBtn;
    // находим остальные элементы строкиы
    QWidget *nameCell = ui->layersTableWidget
                            ->cellWidget(row, (int)ColumnName::NAME);
    QWidget *scaleCell = ui->layersTableWidget
                             ->cellWidget(row, (int)ColumnName::SCALE);
    QWidget *hiddenSizeCell = ui->layersTableWidget
                                  ->cellWidget(row, (int)ColumnName::HIDDEN_SIZE);
    // чистим остальную выделенную на строку память
    delete nameCell;
    delete scaleCell;
    delete hiddenSizeCell;
    // и наконец удаляем саму строку
    ui->layersTableWidget->removeRow(row);
}

NewModelGroupBox::NewModelGroupBox(QWidget *parent)
    : QGroupBox(parent)
    , ui(new Ui::NewModelGroupBox)
    , _layersHelpDialog{new AboutLayersDialog(this)}
{
    ui->setupUi(this);

    connect(ui->newLayerButton, SIGNAL(pressed()),
            this, SLOT(addNewLayer()));
    connect(ui->aboutLayersHelpButton, SIGNAL(pressed()),
            _layersHelpDialog, SLOT(show()));
    connect(ui->chooseEmbeddingDataBtn, SIGNAL(pressed()),
            this, SLOT(chooseLearningData()));
}

NewModelGroupBox::~NewModelGroupBox()
{
    delete ui;
}
