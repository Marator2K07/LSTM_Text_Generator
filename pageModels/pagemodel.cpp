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
                       QDir::Dirs | QDir::NoDotAndDotDot,
                       QDirIterator::Subdirectories);
    // заполняем модель и присваиваем текущую
    while (dirIt.hasNext()) {
        dirIt.next();
        _dirModelView->addFolder(dirIt.filePath(), dirIt.fileName());
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
    }
    // пытаемся поставить новую модель
    try {
        _neuralNetworkModel = new LSTMModel(modelPath,
                                            modelName,
                                            new SoftmaxCrossEntropyLoss());
    } catch (...) {
        QMessageBox::warning(
            this,
            "Ошибка",
            "Невозможно открыть модель по указанному пути:\n" + modelPath
            );
    }
}

PageModel::PageModel(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PageModel)
    , _dirModelView{nullptr}
    , _neuralNetworkModel{nullptr}
{
    ui->setupUi(this);

    connect(ui->chooseFolderButton, SIGNAL(pressed()),
            this, SLOT(openFolderWithModels()));
}

PageModel::~PageModel()
{
    delete ui;
}
