#include "modeltextgenerationgroupbox.h"
#include "ui_modeltextgenerationgroupbox.h"

void ModelTextGenerationGroupBox::openFolderWithModels()
{
    // открываем нужную папку с помощью менеджера
    QString directory = QFileDialog::getExistingDirectory();
    ui->folderModelsLineEdit->setText(directory);
    // готовимся к проходу по всем папкам
    if (_dirModelView != nullptr) {
        delete _dirModelView;
    }
    _dirModelView = new DirectoryModelView();
    QDir dir(directory);
    QDirIterator dirIt(dir.absolutePath(),
                       QDir::Dirs | QDir::NoDotAndDotDot);
    // заполняем модель и присваиваем текущую
    while (dirIt.hasNext()) {
        dirIt.next();
        int idx = dirIt.filePath().lastIndexOf('/');
        QString correctPath = dirIt.filePath().left(idx);
        _dirModelView->addFolder(correctPath, dirIt.fileName());
    }
    ui->modelsListView->setModel(_dirModelView);
}

void ModelTextGenerationGroupBox::selectNeuralNetworkModel(QModelIndex index)
{
    // подготовка
    QString modelPath
        = _dirModelView->data(index, DirectoryModelView::ValueRole).toString();
    QString modelName
        = _dirModelView->data(index, Qt::DisplayRole).toString();
    // если модель уже была выбрана, то освобождаем память
    if (_neuralNetworkModel != nullptr) {
        delete _neuralNetworkModel;
        _neuralNetworkModel = nullptr;
    }
    // пытаемся поставить новую модель
    try {
        _neuralNetworkModel = new LSTMModel(
            modelPath,
            modelName,
            new SoftmaxCrossEntropyLoss()
            );
        _textGenerator->setNeuralNetworkModel(_neuralNetworkModel);
        // если все успешно, уведомляем пользователя
        QMessageBox::information(
            this,
            "Уведомление",
            "Модель успешно загружена!"
            );
    } catch (...) {
        // если не успешно, то тоже уведомляем пользователя
        QMessageBox::warning(
            this,
            "Ошибка",
            "Невозможно открыть модель по указанному пути:\n" + modelPath
            );
    }
    emit neuralNetworkModelChanged();
}

void ModelTextGenerationGroupBox::generateWithModel()
{
    // подготовка
    QString context = ui->sampleGenLineEdit->text();
    QList<QChar> missingChars;
    // только если прошлая генерация закончилась
    if (!_generateThread.isRunning()) {
        missingChars
            = _neuralNetworkModel->embedding()->checkStrForCompatibility(context);
        // можем генерировать, если нет ни одного отсутствующего в эмбеддинге символа
        if (missingChars.size() == 0) {
            // преобразуем контекст в нужный вид
            QList<int> convertedStr
                = _neuralNetworkModel->embedding()->textToIndeces(context);
            // обновляем данные для нового задания(генерации) и запускаем процесс
            _textGenerator->applyAssignmentForGenerate(convertedStr);
            _generateThread.start();
        }
        // иначе показываем какие символы не распознаются моделью
        else {
            QString errorSymbols;
            for (const QChar &symbol : missingChars) {
                errorSymbols.append("`").append(symbol).append("` ");
            }
            QMessageBox::warning(
                this,
                "Ошибка при попытке генерации",
                "Данные символы не распознаются моделью:\n " + errorSymbols
                );
        }
    }
}

void ModelTextGenerationGroupBox::adaptFormElements()
{
    // открываем/закрываем доступ к разделу генерации
    if (_neuralNetworkModel == nullptr) {
        ui->generateFrame->setEnabled(false);
    } else {
        ui->generateFrame->setEnabled(true);
    }
}

ModelTextGenerationGroupBox::ModelTextGenerationGroupBox(QWidget *parent)
    : QGroupBox(parent)
    , ui(new Ui::ModelTextGenerationGroupBox)
    , _dirModelView{nullptr}
    , _neuralNetworkModel{nullptr}
    , _textGenerator{new NeuralNetworkTextGenerator()}
{
    ui->setupUi(this);
    adaptFormElements();

    connect(ui->chooseFolderButton, SIGNAL(pressed()),
            this, SLOT(openFolderWithModels()));
    connect(ui->modelsListView, SIGNAL(activated(QModelIndex)),
            this, SLOT(selectNeuralNetworkModel(QModelIndex)));
    connect(ui->genSampleButton, SIGNAL(pressed()),
            this, SLOT(generateWithModel()));
    connect(ui->cleanLogButton, SIGNAL(pressed()),
            ui->sampleOutputText, SLOT(clear()));
    connect(this, SIGNAL(neuralNetworkModelChanged()),
            this, SLOT(adaptFormElements()));
    connect(_textGenerator, SIGNAL(showGenerationInfo(QString)),
            ui->sampleOutputText, SLOT(insertPlainText(QString)));
    // экстра важные связи связанные с многопоточкой
    connect(&_generateThread, SIGNAL(started()),
            _textGenerator, SLOT(generate()));
    connect(_textGenerator, SIGNAL(generationStoped()),
            &_generateThread, SLOT(exit()));
    // не забываем поместить тренер в отдельный поток
    _textGenerator->moveToThread(&_generateThread);
}

ModelTextGenerationGroupBox::~ModelTextGenerationGroupBox()
{
    delete ui;
}
