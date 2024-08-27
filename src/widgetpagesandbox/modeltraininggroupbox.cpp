#include "modeltraininggroupbox.h"
#include "ui_modeltraininggroupbox.h"

QString ModelTrainingGroupBox::TRAINING_DATA_NAME = "trainingData";

void ModelTrainingGroupBox::newTrainerForModel()
{
    // если ранее тренер вдруг уже создавался
    if (_trainer != nullptr) {
        disconnect(_trainer);
        delete _trainer;
    }
    // иницилизируем нового тренера и ставим основные связи
    _trainer = new ConsistentTrainer(_loadedModel, _chosenOptimizer);
    connect(_trainer, SIGNAL(percentageOfTrainingUpdated(double)),
            ui->traningValueLcdNumber, SLOT(display(double)));
    connect(_trainer, SIGNAL(epochsCompletedUpdated(double)),
            ui->epochsCountLcdNumber, SLOT(display(double)));
    connect(_trainer, SIGNAL(recommendedNumberOfTrainingIter(int)),
            this, SLOT(updateMaxTrainCountValue(int)));
    connect(_trainer, SIGNAL(modelIsCorrect()),
            this, SLOT(uploadTrainerDataToForm()));
    connect(_trainer, SIGNAL(modelIsCorrect()),
            this, SLOT(trainFormActiveState()));
    connect(_trainer, SIGNAL(modelIsBroken()),
            this, SLOT(trainFormNotActiveState()));
    connect(_trainer, SIGNAL(modelIsBroken()),
            this, SLOT(processBadModel()));
    connect(_trainer, SIGNAL(showLearningInfo(QString)),
            ui->logTextEdit, SLOT(insertPlainText(QString)));
    // экстра важные связи, связанные с многопоточкой
    connect(&_trainThread, SIGNAL(started()),
            _trainer, SLOT(train()));
    connect(_trainer, SIGNAL(trainingStoped()),
            &_trainThread, SLOT(exit()));
    connect(_trainer, SIGNAL(trainingStoped()),
            this, SLOT(trainFormActiveState()));
    connect(ui->stopTrainButton, SIGNAL(pressed()),
            this, SLOT(stopTrainModel()));
    connect(_trainer, SIGNAL(trainingProgress(int)),
            ui->trainingProgressBar, SLOT(setValue(int)));
    // не забываем поместить тренер в отдельный поток
    _trainer->moveToThread(&_trainThread);
    // в конце получаем все необходимые данные для отображения
    _trainer->updateStatus();
    // вручную активируем форму обучения
    trainFormActiveState();
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

void ModelTrainingGroupBox::trainFormActiveState()
{
    ui->currentModelLineEdit->setEnabled(true);
    ui->optimizerSGDRadioButton->setEnabled(true);
    ui->optimizerAdaGradRadioButton->setEnabled(true);
    ui->optimizerLearningRateSpinBox->setEnabled(true);
    ui->traningValueLcdNumber->setEnabled(true);
    ui->epochsCountLcdNumber->setEnabled(true);
    ui->iterTrainCountSpinBox->setEnabled(true);
    ui->sampleOutputCheckBox->setEnabled(true);
    ui->startTrainButton->setEnabled(true);
    ui->stopTrainButton->setEnabled(false);
    ui->dropModelButton->setEnabled(false);
    ui->sampleEverySpinBox->setEnabled(true);
    ui->epochsCountLabel->setEnabled(true);
    ui->iterTrainCountLabel->setEnabled(true);
    ui->sampleEveryLabel->setEnabled(true);
    ui->trainingValueLabel->setEnabled(true);
    ui->optimizerLearningRateLabel->setEnabled(true);
}

void ModelTrainingGroupBox::trainFormNotActiveState()
{
    ui->currentModelLineEdit->setEnabled(false);
    ui->optimizerSGDRadioButton->setEnabled(false);
    ui->optimizerAdaGradRadioButton->setEnabled(false);
    ui->optimizerLearningRateSpinBox->setEnabled(false);
    ui->traningValueLcdNumber->setEnabled(false);
    ui->epochsCountLcdNumber->setEnabled(false);
    ui->iterTrainCountSpinBox->setEnabled(false);
    ui->sampleOutputCheckBox->setEnabled(false);
    ui->startTrainButton->setEnabled(false);
    ui->sampleEverySpinBox->setEnabled(false);
    ui->epochsCountLabel->setEnabled(false);
    ui->iterTrainCountLabel->setEnabled(false);
    ui->sampleEveryLabel->setEnabled(false);
    ui->trainingValueLabel->setEnabled(false);
    ui->optimizerLearningRateLabel->setEnabled(false);
}

void ModelTrainingGroupBox::selectSGDOptimizer()
{
    // только если связанная радио кнопка включена
    if (ui->optimizerSGDRadioButton->isChecked()) {
        // задаем новый оптимизатор
        _chosenOptimizer = new SGD(
            _loadedModel, ui->optimizerLearningRateSpinBox->value()
            );
        // и ставим его
        _trainer->refreshOptimizerStatus(_chosenOptimizer);
    }
}

void ModelTrainingGroupBox::selectAdaGradOptimizer()
{
    // только если связанная радио кнопка включена
    if (ui->optimizerAdaGradRadioButton->isChecked()) {
        // задаем новый оптимизатор
        _chosenOptimizer = new AdaGrad(
            _loadedModel, ui->optimizerLearningRateSpinBox->value()
            );
        // и ставим его
        _trainer->refreshOptimizerStatus(_chosenOptimizer);
    }
}

void ModelTrainingGroupBox::updateOptimizerLearningRate(const double newRate)
{
    if (_trainer->optimizer() != nullptr) {
        _trainer->optimizer()->newLearningRate(newRate);
    }
}

void ModelTrainingGroupBox::tryLoadModel(const QString modelPathAndName)
{
    // находим основную часть имени и пути модели
    QString fileNameMainPart = modelPathAndName.right(
        modelPathAndName.length() - modelPathAndName.lastIndexOf("/") - 1
        );
    QString filePath = modelPathAndName.left(modelPathAndName.lastIndexOf("/"));
    // конфигурируем предполагаемые файлы
    QFile currentModelLayersFile(
        QString("%1/%2_%3.txt")
            .arg(modelPathAndName, fileNameMainPart, LSTMModel::LAYERS_DATA_NAME)
        );
    QFile currentModelEmbeddingFile(
        QString("%1/%2_%3.txt")
            .arg(modelPathAndName, fileNameMainPart, LSTMModel::EMBEDDING_DATA_NAME)
        );
    // проверяем на наличие уже созданную раннее модель
    if (_loadedModel != nullptr) {
        delete _loadedModel;
        _loadedModel = nullptr;
    }
    // инициализируем модель в случае ее существования
    if (currentModelLayersFile.exists() && currentModelEmbeddingFile.exists()) {
        _modelNameMainPart = fileNameMainPart;
        // подгружаем модель для обучения
        _loadedModel = new LSTMModel(
            filePath,
            fileNameMainPart,
            new SoftmaxCrossEntropyLoss()
            );
        // и проверяем наличие тренера для текущей модели
        checkModelForTrainBefore();
    }
    // предупреждение в случае ее отсутствия
    else {
        _modelNameMainPart = QString();
        QMessageBox::warning(
            this,
            "Предупреждение",
            "По указанному пути не существует модели для обучения"
            );
        // освобождаем тренера, если они был выбран/создан
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
            "Создан тренер по умолчанию."
            );
        // в данном случае инициализируем тренера с нуля
        newTrainerForModel();
        return;
    }
    // если дошли до сюда, то файл обучения существует - создаем и загружаем
    newTrainerForModel();
    _trainer->load(ui->currentModelLineEdit->text());
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

void ModelTrainingGroupBox::uploadTrainerDataToForm()
{
    // ставим все загруженные из файла данные и обновляем
    ui->optimizerLearningRateSpinBox
        ->setValue(_trainer->optimizer()->learningRate());
    switch (_trainer->optimizer()->type()) {
    case OptimizerType::SGD:
        ui->optimizerSGDRadioButton->setChecked(true);
        break;
    case OptimizerType::ADA_GRAD:
        ui->optimizerAdaGradRadioButton->setChecked(true);
        break;
    default:
        break;
    }    
    _trainer->updateStatus();
}

void ModelTrainingGroupBox::processBadModel()
{
    QMessageBox::warning(
        this,
        "Предупреждение",
        "Выбранная модель нейронной сети похоже неисправна.\n"
        "Создайте идентичную новую или выполните сброс с помощью связанной кнопки."
        );
    // разблокируем сброс
    ui->dropModelButton->setEnabled(true);
}

void ModelTrainingGroupBox::trainModel()
{
    // только если прошлое обучение закончилось
    if (!_trainThread.isRunning()) {
        // в случае корректности данных, связанных с обучением,
        // обновляем параметры для нового задания(обучения) и запускаем процесс
        if (trainPreDataIsCorrect()) {
            _trainer->applyAssignmentForTrain(ui->iterTrainCountSpinBox->value(),
                                              ui->sampleOutputCheckBox->isChecked(),
                                              ui->sampleEverySpinBox->value(),
                                              ui->currentModelLineEdit->text());
            _trainThread.start();
            ui->stopTrainButton->setEnabled(true);
            trainFormNotActiveState();
        }
    }
}

void ModelTrainingGroupBox::stopTrainModel()
{
    // только если обучение еще продолжается
    if (_trainThread.isRunning()) {
        _trainer->stop();
        ui->stopTrainButton->setEnabled(false);
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
    , _chosenOptimizer{nullptr}
{
    ui->setupUi(this);
    trainFormNotActiveState();

    connect(ui->chooseCurrentModelButton, SIGNAL(pressed()),
            this, SLOT(chooseModelFolderPath()));
    connect(ui->currentModelLineEdit, SIGNAL(textChanged(QString)),
            this, SLOT(tryLoadModel(QString)));
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
}

ModelTrainingGroupBox::~ModelTrainingGroupBox()
{
    // в случае экстренного выхода мягко стопим поток
    stopTrainModel();
    _trainThread.quit();
    _trainThread.wait();

    delete ui;
}
