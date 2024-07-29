#include "modeltraininggroupbox.h"
#include "ui_modeltraininggroupbox.h"

QString ModelTrainingGroupBox::TRAINING_DATA_NAME = "trainingData";

void ModelTrainingGroupBox::selectSGDOptimizer()
{
    // только если связанная радио кнопка включена
    if (ui->optimizerSGDRadioButton->isChecked()) {
        // если память ранее была уже занята
        if (_currentOptimizer != nullptr) {
            delete _currentOptimizer;
        }
        // в заключении создаем новый оптимизатор
        _currentOptimizer = new SGD(_loadedModel,
                                    ui->optimizerLearningRateSpinBox->value());
    }
}

void ModelTrainingGroupBox::selectAdaGradOptimizer()
{
    // только если связанная радио кнопка включена
    if (ui->optimizerAdaGradRadioButton->isChecked()) {
        // если память ранее была уже занята
        if (_currentOptimizer != nullptr) {
            delete _currentOptimizer;
        }
        // в заключении создаем новый оптимизатор
        _currentOptimizer = new AdaGrad(_loadedModel,
                                        ui->optimizerLearningRateSpinBox->value());
    }
}

void ModelTrainingGroupBox::updateOptimizerLearningRate(const double newRate)
{
    if (_currentOptimizer != nullptr) {
        _currentOptimizer->newLearningRate(newRate);
    }
}

void ModelTrainingGroupBox::checkCurrentModel(const QString modelPathAndName)
{
    // находим основную часть имени и пути модели
    QString fileNameMainPart = modelPathAndName.right(
        modelPathAndName.length() - modelPathAndName.lastIndexOf("/") - 1
        );
    QString filePath = modelPathAndName.left(modelPathAndName.lastIndexOf("/"));
    // конфигурируем предполагаемые файлы
    QFile currentModelLayersFile(QString("%1/%2_%3.txt")
                                     .arg(modelPathAndName,
                                          fileNameMainPart,
                                          LSTMModel::LAYERS_DATA_NAME)
                                 );
    QFile currentModelEmbeddingFile(QString("%1/%2_%3.txt")
                                        .arg(modelPathAndName,
                                             fileNameMainPart,
                                             LSTMModel::EMBEDDING_DATA_NAME)
                                    );
    // в зависимости от существования модели блокируем/разблокируем доступ
    // и ставим/убираем основную часть имени модели
    if (currentModelLayersFile.exists() && currentModelEmbeddingFile.exists()) {
        ui->frame->setEnabled(true);
        _modelNameMainPart = fileNameMainPart;
        // подгружаем модель для обучения
        _loadedModel = new LSTMModel(
            filePath,
            fileNameMainPart,
            new SoftmaxCrossEntropyLoss()
            );
        // посылаем сигнал о корректности
        emit selectedModelCorrect();
    } else {
        ui->frame->setEnabled(false);
        _modelNameMainPart = QString();
        QMessageBox::warning(
            this,
            "Предупреждение",
            "По указанному пути не существует модели для обучения"
            );
        // в любом случае отгружаем модель, если она была выбрана
        if (_loadedModel != nullptr) {
            delete _loadedModel;
            _loadedModel = nullptr;
        }
    }
}

void ModelTrainingGroupBox::checkForTrainBefore()
{
    // подготовка
    QString trainerFilePath = QString("%1/%2_%3.txt").arg(
        ui->currentModelLineEdit->text(),
        _modelNameMainPart,
        ConsistentTrainer::TRAINER_DATA_NAME
        );
    QFile trainerFile(trainerFilePath);
    // проверяем наличие файла обучения
    if (!trainerFile.exists()) {
        QMessageBox::information(
            this,
            "Информация",
            "Выбранная модель нейронной сети ранее не обучалась.");
        return;
    }
    // если дошли до сюда, то файл обучения существует
    emit trainerExists();
}

void ModelTrainingGroupBox::chooseCurrentModel()
{
    QString currentModelPath = QFileDialog::getExistingDirectory(
        this,
        "Выбор директории с существующей моделью для обучения",
        QString()
        );
    ui->currentModelLineEdit->setText(currentModelPath);
}

void ModelTrainingGroupBox::loadExistingTrainer()
{
    // если ранее тренер уже создавался
    if (_trainer != nullptr) {
        delete _trainer;
    }
    // иницилизируем новый из файла
    _trainer = new ConsistentTrainer(
        ui->currentModelLineEdit->text(), _loadedModel
        );
}

ModelTrainingGroupBox::ModelTrainingGroupBox(QWidget *parent)
    : QGroupBox(parent)
    , ui(new Ui::ModelTrainingGroupBox)
    , _modelNameMainPart{QString()}
    , _loadedModel{nullptr}
    , _trainingRate{0.0}
    , _epochsCompleted{0.0}
    , _currentOptimizer{nullptr}
    , _trainer{nullptr}
{
    ui->setupUi(this);
    ui->frame->setEnabled(false);

    connect(ui->chooseCurrentModelButton, SIGNAL(pressed()),
            this, SLOT(chooseCurrentModel()));
    connect(ui->currentModelLineEdit, SIGNAL(textChanged(QString)),
            this, SLOT(checkCurrentModel(QString)));
    connect(ui->optimizerSGDRadioButton, SIGNAL(toggled(bool)),
            this, SLOT(selectSGDOptimizer()));
    connect(ui->optimizerAdaGradRadioButton, SIGNAL(toggled(bool)),
            this, SLOT(selectAdaGradOptimizer()));
    connect(ui->optimizerLearningRateSpinBox, SIGNAL(valueChanged(double)),
            this, SLOT(updateOptimizerLearningRate(double)));
    connect(this, SIGNAL(selectedModelCorrect()),
            this, SLOT(checkForTrainBefore()));
    connect(this, SIGNAL(trainerExists()),
            this, SLOT(loadExistingTrainer()));
}

ModelTrainingGroupBox::~ModelTrainingGroupBox()
{
    delete ui;
}
