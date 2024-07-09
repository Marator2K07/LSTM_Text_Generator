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
    connect(ui->modelsListView, SIGNAL(activated(QModelIndex)),
            this, SLOT(selectNeuralNetworkModel(QModelIndex)));
}

PageModel::~PageModel()
{
    delete ui;
}
