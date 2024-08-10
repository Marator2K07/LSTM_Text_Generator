#include "pagemodel.h"
#include "./ui_pagemodel.h"

void PageModel::openFolderWithModels()
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

void PageModel::selectNeuralNetworkModel(QModelIndex index)
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
        _textGenerator.setNeuralNetworkModel(_neuralNetworkModel);
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

void PageModel::stringToVector(const QString str)
{
    vector<int> convertedStr
        = _neuralNetworkModel->embedding()->textToIndeces(str);

}

void PageModel::generateWithModel()
{
    vector<int> convertedStr
        = _neuralNetworkModel->embedding()->textToIndeces(
            ui->sampleGenLineEdit->text()
            );
    _textGenerator.genSymbols(convertedStr);
}

void PageModel::adaptFormElements()
{
    // открываем/закрываем доступ к разделу генерации
    if (_neuralNetworkModel == nullptr) {
        ui->genSampleGroupBox->setEnabled(false);
    } else {
        ui->genSampleGroupBox->setEnabled(true);
    }
}

PageModel::PageModel(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PageModel)
    , _dirModelView{nullptr}
    , _neuralNetworkModel{nullptr}
    , _textGenerator{NeuralNetworkTextGenerator(this)}
{
    ui->setupUi(this);
    adaptFormElements();

    connect(ui->chooseFolderButton, SIGNAL(pressed()),
            this, SLOT(openFolderWithModels()));
    connect(ui->modelsListView, SIGNAL(activated(QModelIndex)),
            this, SLOT(selectNeuralNetworkModel(QModelIndex)));
    connect(ui->genSampleButton, SIGNAL(pressed()),
            this, SLOT(generateWithModel()));

    connect(this, SIGNAL(neuralNetworkModelChanged()),
            this, SLOT(adaptFormElements()));
    connect(&_textGenerator, SIGNAL(symbolReady(QString)),
            ui->sampleOutputText, SLOT(insertPlainText(QString)));

}

PageModel::~PageModel()
{
    delete ui;
}
