#include "modeltraininggroupbox.h"
#include "ui_modeltraininggroupbox.h"

QString ModelTrainingGroupBox::TRAINING_DATA_NAME = "trainingData";

void ModelTrainingGroupBox::newTrainerForModel()
{
    // если ранее тренер вдруг уже создавался
    if (_trainer != nullptr) {
        return;
    }
    // иницилизируем нового неполноценного тренера
    // (без инициализации оптимизатора) и ставим связи
    _trainer = new ConsistentTrainer(_loadedModel, nullptr);
    connect(_trainer, SIGNAL(percentageOfTrainingUpdated(double)),
            ui->traningValueLcdNumber, SLOT(display(double)));
    connect(_trainer, SIGNAL(epochsCompletedUpdated(double)),
            ui->epochsCountLcdNumber, SLOT(display(double)));
    connect(_trainer, SIGNAL(recommendedNumberOfTrainingIter(int)),
            this, SLOT(updateMaxTrainCountValue(int)));
    connect(_trainer, SIGNAL(showLearningInfo(QString)),
            ui->logTextEdit, SLOT(append(QString)));
    // в конце получаем все необходимые данные для отображения
    _trainer->updateStatus();
}

bool ModelTrainingGroupBox::trainPreDataIsCorrect()
{
    // проверка выбранного оптимизатора
    if (!ui->optimizerSGDRadioButton->isChecked() &&
        !ui->optimizerAdaGradRadioButton->isChecked() &&
        _trainer->optimizer() == nullptr) {
        QMessageBox::warning(
            this,
            "Предупреждение",
            "Оптимизатор не выбран."
            );
        return false;
    }

    // если дошли до этого участка, то все впорядке
    return true;
}

void ModelTrainingGroupBox::selectSGDOptimizer()
{
    // только если связанная радио кнопка включена
    if (ui->optimizerSGDRadioButton->isChecked()) {
        // задаем новый оптимизатор
        _trainer->refreshOptimizerStatus(
            new SGD(_loadedModel, ui->optimizerLearningRateSpinBox->value())
            );
    }
}

void ModelTrainingGroupBox::selectAdaGradOptimizer()
{
    // только если связанная радио кнопка включена
    if (ui->optimizerAdaGradRadioButton->isChecked()) {
        // задаем новый оптимизатор
        _trainer->refreshOptimizerStatus(
            new AdaGrad(_loadedModel, ui->optimizerLearningRateSpinBox->value())
            );
    }
}

void ModelTrainingGroupBox::updateOptimizerLearningRate(const double newRate)
{
    if (_trainer->optimizer() != nullptr) {
        _trainer->optimizer()->newLearningRate(newRate);
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
        // в любом случае отгружаем(удаляем) модель
        // и тренера, если они были выбраны/созданы
        if (_loadedModel != nullptr) {
            delete _loadedModel;
            _loadedModel = nullptr;
        }
        if (_trainer != nullptr) {
            disconnect(_trainer);
            delete _trainer;
            _trainer = nullptr;
        }
    }
}

void ModelTrainingGroupBox::checkModelForTrainBefore()
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
            "Выбранная модель нейронной сети ранее не обучалась.\n"
            "Создан тренер по умолчанию.");
        // в данном случае инициализируем тренера с нуля
        newTrainerForModel();
        return;
    }
    // если дошли до сюда, то файл обучения существует
    emit trainerExists();
}

void ModelTrainingGroupBox::chooseModelFolderPath()
{
    QString currentModelPath = QFileDialog::getExistingDirectory(
        this,
        "Выбор директории с существующей моделью для обучения",
        QString()
        );
    ui->currentModelLineEdit->setText(currentModelPath);
}

void ModelTrainingGroupBox::updateMaxTrainCountValue(int newValue)
{
    ui->iterTrainCountSpinBox->setMaximum(newValue);
    ui->sampleEverySpinBox->setMaximum(newValue);
}

void ModelTrainingGroupBox::loadExistingTrainer()
{
    // если ранее тренер уже создавался
    if (_trainer != nullptr) {
        disconnect(_trainer);
        delete _trainer;        
    }
    // иницилизируем новый из файла и ставим связи
    _trainer = new ConsistentTrainer(
        ui->currentModelLineEdit->text(), _loadedModel
        );
    connect(_trainer, SIGNAL(percentageOfTrainingUpdated(double)),
            ui->traningValueLcdNumber, SLOT(display(double)));
    connect(_trainer, SIGNAL(epochsCompletedUpdated(double)),
            ui->epochsCountLcdNumber, SLOT(display(double)));
    connect(_trainer, SIGNAL(recommendedNumberOfTrainingIter(int)),
            this, SLOT(updateMaxTrainCountValue(int)));
    connect(_trainer, SIGNAL(showLearningInfo(QString)),
            ui->logTextEdit, SLOT(append(QString)));
    // в конце получаем все необходимые данные для отображения
    _trainer->updateStatus();
}

void ModelTrainingGroupBox::trainModel()
{
    // в случае корректности данных, связанных с обучением
    if (trainPreDataIsCorrect()) {
        _trainer->train(ui->iterTrainCountSpinBox->value(),
                        ui->sampleOutputCheckBox->isChecked(),
                        ui->sampleEverySpinBox->value()
                        );
    }
}

ModelTrainingGroupBox::ModelTrainingGroupBox(QWidget *parent)
    : QGroupBox(parent)
    , ui(new Ui::ModelTrainingGroupBox)
    , _modelNameMainPart{QString()}
    , _loadedModel{nullptr}
    , _trainingRate{0.0}
    , _epochsCompleted{0.0}
    , _trainer{nullptr}
{
    ui->setupUi(this);
    ui->frame->setEnabled(false);

    connect(ui->chooseCurrentModelButton, SIGNAL(pressed()),
            this, SLOT(chooseModelFolderPath()));
    connect(ui->currentModelLineEdit, SIGNAL(textChanged(QString)),
            this, SLOT(checkCurrentModel(QString)));
    connect(ui->optimizerSGDRadioButton, SIGNAL(toggled(bool)),
            this, SLOT(selectSGDOptimizer()));
    connect(ui->optimizerAdaGradRadioButton, SIGNAL(toggled(bool)),
            this, SLOT(selectAdaGradOptimizer()));
    connect(ui->optimizerLearningRateSpinBox, SIGNAL(valueChanged(double)),
            this, SLOT(updateOptimizerLearningRate(double)));
    connect(ui->startTrainButton, SIGNAL(pressed()),
            this, SLOT(trainModel()));
    connect(ui->cleanTrainLogButton, SIGNAL(pressed()),
            ui->logTextEdit, SLOT(clear()));
    connect(this, SIGNAL(selectedModelCorrect()),
            this, SLOT(checkModelForTrainBefore()));
    connect(this, SIGNAL(trainerExists()),
            this, SLOT(loadExistingTrainer()));
}

ModelTrainingGroupBox::~ModelTrainingGroupBox()
{
    delete ui;
}
