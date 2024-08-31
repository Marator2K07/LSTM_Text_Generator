#include "newmodelgroupbox.h"
#include "ui_newmodelgroupbox.h"

long NewModelGroupBox::LAYERS_CREATED = 0;
int NewModelGroupBox::STANDART_FONT_SIZE = 12;
QString NewModelGroupBox::STANDART_FONT_NAME = "Bahnschrift SemiCondensed";
double NewModelGroupBox::MIN_LAYER_SCALE = 0.001;
double NewModelGroupBox::MAX_LAYER_SCALE = 0.01;
double NewModelGroupBox::LAYER_SCALE_STEP = 0.001;
int NewModelGroupBox::LAYER_SCALE_DECIMALS_COUNT = 3;
int NewModelGroupBox::MIN_LAYER_HIDDEN_SIZE = 16;
int NewModelGroupBox::MAX_LAYER_HIDDEN_SIZE = 512;
long NewModelGroupBox::MIN_NAME_MODEL_LENGTH = 5;
long NewModelGroupBox::MIN_COUNT_MODEL_LAYERS = 1;
int NewModelGroupBox::LAYERS_COLUMN_NAME_WIDTH = 65;
int NewModelGroupBox::LAYERS_COLUMN_SCALE_WIDTH = 105;
int NewModelGroupBox::LAYERS_COLUMN_HIDDEN_SIZE_WIDTH = 85;
int NewModelGroupBox::LAYERS_COLUMN_DELETE_BUTTON_WIDTH = 55;
int NewModelGroupBox::LAYERS_COLUMN_DELETE_BUTTON_HEIGHT = 33;

QList<INeuralNetworkLayer *> NewModelGroupBox::layersFromTable(int outputSize) const
{
    // подготовка
    QList<INeuralNetworkLayer *> layers;
    // проходимся по строкам виджета таблицы
    for (int rowI = 0; rowI < ui->layersTableWidget->rowCount(); ++rowI) {
        // считываем данные с ячеек
        QString layerName = ui->layersTableWidget
                                ->item(rowI, (int)ColumnName::NAME)->text();
        QDoubleSpinBox *scaleSpinBox
            = (QDoubleSpinBox*)ui->layersTableWidget
                  ->cellWidget(rowI, (int)ColumnName::SCALE);
        double layerScale = scaleSpinBox->value();
        QSpinBox *hiddenSizeSpinBox
            = (QSpinBox*)ui->layersTableWidget
                  ->cellWidget(rowI, (int)ColumnName::HIDDEN_SIZE);
        int layerHiddenSize = hiddenSizeSpinBox->value();
        // наконец создаем свежий слой по данным выше
        layers.push_back(
            new LSTMLayer(layerName, layerHiddenSize, outputSize, layerScale)
            );
    }

    return layers;
}

void NewModelGroupBox::newModelDataCheck()
{
    // проверка существования обучающих данных
    QFile learningDataFile(ui->learningDataPathLineEdit->text());
    if (!learningDataFile.exists()) {
        QMessageBox::warning(
            this,
            "Предупреждение",
            "Обучающие данные не выбраны/не существуют."
            );
        return;
    }
    // проверка(пока простая) корректности имени модели
    if (ui->modelNameLineEdit->text().length() <= MIN_NAME_MODEL_LENGTH) {
        QMessageBox::warning(
            this,
            "Предупреждение",
            "Слишком простое/короткое имя модели.\n"
            "Выбирайте содержательное и не короткое имя для модели."
            );
        return;
    }
    // проверка количества слоев будущей модели
    if (ui->layersTableWidget->rowCount() < MIN_COUNT_MODEL_LAYERS) {
        QMessageBox::warning(
            this,
            "Предупреждение",
            "Любая модель должна содержать хотябы один слой."
            );
        return;
    }
    // проверка существования директории для сохранения
    QDir modelSavePathDir(ui->saveModelPathLineEdit->text());
    if (!modelSavePathDir.exists() || ui->saveModelPathLineEdit->text()
                                              .length() == 0) {
        QMessageBox::warning(
            this,
            "Предупреждение",
            "Путь для сохранения модели не существует/ не задан."
            );
        return;
    }
    // проверка на существование такой же модели(с таким же именем)
    QDir possibleExistingModel(
        ui->saveModelPathLineEdit->text() + "/" + ui->modelNameLineEdit->text()
        );
    if (possibleExistingModel.exists()) {
        QMessageBox::warning(
            this,
            "Предупреждение",
            "Модель с таким именем уже существует."
            );
        return;
    }
    // если дошли до данной строчки, то можно создавать модель
    emit modelReadyToBeCreated();
}

void NewModelGroupBox::createAndSaveNewModel()
{
    // создаем нужные обьекты
    CharAsVectorEmbedding embedding(
        ui->learningDataPathLineEdit->text(),
        ui->sequenceLengthSpinBox->value(),
        ui->batchSizeSpinBox->value()
        );
    SoftmaxCrossEntropyLoss *loss = new SoftmaxCrossEntropyLoss();
    QList<INeuralNetworkLayer *> layers = layersFromTable(embedding.vocabSize());
    LSTMModel lstmModel(
        ui->modelNameLineEdit->text(), loss, &embedding, layers
        );
    // сохраняем и уведомляем
    lstmModel.forward(Matrix3d<double>::zeroM(
        ui->batchSizeSpinBox->value(),
        ui->sequenceLengthSpinBox->value(),
        embedding.vocabSize()
        ));
    lstmModel.save(ui->saveModelPathLineEdit->text());    
    QMessageBox::information(this, "Информация", "Модель успешно сохранена");
    // освобождаем память
    delete loss;
    foreach (INeuralNetworkLayer *layer, layers) {
        delete layer;
    }
}

void NewModelGroupBox::chooseLearningData()
{
    QString fileName = QFileDialog::getOpenFileName(
        this,
        "Выбор обучающих данных",
        QString(),
        "Text files (*.txt)"
        );
    ui->learningDataPathLineEdit->setText(fileName);
}

void NewModelGroupBox::chooseModelSavePath()
{
    QString savePath = QFileDialog::getExistingDirectory(
        this,
        "Выбор директории для сохранения модели",
        QString()
        );
    ui->saveModelPathLineEdit->setText(savePath);
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
    initScale->setRange(MIN_LAYER_SCALE, MAX_LAYER_SCALE);
    initScale->setDecimals(LAYER_SCALE_DECIMALS_COUNT);
    initScale->setSingleStep(LAYER_SCALE_STEP);
    QSpinBox *initHiddenSize = new QSpinBox();
    initHiddenSize->setRange(MIN_LAYER_HIDDEN_SIZE, MAX_LAYER_HIDDEN_SIZE);
    // стоит также добавить кнопку для удаления данной строки
    QPushButton *deleteBtn = new QPushButton("Убрать");
    deleteBtn->setFont(QFont(STANDART_FONT_NAME, STANDART_FONT_SIZE));
    deleteBtn->setSizePolicy(QSizePolicy::Minimum,
                             QSizePolicy::Minimum);
    deleteBtn->setMaximumSize(LAYERS_COLUMN_DELETE_BUTTON_WIDTH,
                              LAYERS_COLUMN_DELETE_BUTTON_HEIGHT);
    deleteBtn->setBaseSize(LAYERS_COLUMN_DELETE_BUTTON_WIDTH,
                           LAYERS_COLUMN_DELETE_BUTTON_HEIGHT);
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
    ui->layersTableWidget->setColumnWidth((int)ColumnName::NAME,
                                          LAYERS_COLUMN_NAME_WIDTH);
    ui->layersTableWidget->setColumnWidth((int)ColumnName::SCALE,
                                          LAYERS_COLUMN_SCALE_WIDTH);
    ui->layersTableWidget->setColumnWidth((int)ColumnName::HIDDEN_SIZE,
                                          LAYERS_COLUMN_HIDDEN_SIZE_WIDTH);
    ui->layersTableWidget->setColumnWidth((int)ColumnName::DELETE_BUTTON,
                                          LAYERS_COLUMN_DELETE_BUTTON_WIDTH);
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
    , _learningDataHelpDialog{new AboutLearningDataDialog(this)}
    , _modelDataHelpDialog{new AboutModelDataDialog(this)}
{
    ui->setupUi(this);

    connect(ui->newLayerButton, SIGNAL(pressed()),
            this, SLOT(addNewLayer()));
    connect(ui->aboutLayersHelpButton, SIGNAL(pressed()),
            _layersHelpDialog, SLOT(show()));
    connect(ui->aboutLearningDataHelpBtn, SIGNAL(pressed()),
            _learningDataHelpDialog, SLOT(preloadData()));
    connect(ui->aboutLearningDataHelpBtn, SIGNAL(pressed()),
            _learningDataHelpDialog, SLOT(show()));
    connect(ui->aboutModelDataHelpButton, SIGNAL(pressed()),
            _modelDataHelpDialog, SLOT(show()));
    connect(ui->learningDataPathLineEdit, SIGNAL(textChanged(QString)),
            _learningDataHelpDialog, SLOT(updateLearningDataPath(QString)));
    connect(ui->chooseLearningDataBtn, SIGNAL(pressed()),
            this, SLOT(chooseLearningData()));
    connect(ui->chooseSaveModelPathBtn, SIGNAL(pressed()),
            this, SLOT(chooseModelSavePath()));
    connect(ui->createAndSaveNewModelBtn, SIGNAL(pressed()),
            this, SLOT(newModelDataCheck()));
    connect(this, SIGNAL(modelReadyToBeCreated()),
            this, SLOT(createAndSaveNewModel()));
}

NewModelGroupBox::~NewModelGroupBox()
{
    delete ui;
}
