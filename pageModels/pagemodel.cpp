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

PageModel::PageModel(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PageModel)
    , _dirModelView(nullptr)
{
    ui->setupUi(this);

    connect(ui->chooseFolderButton, SIGNAL(pressed()),
            this, SLOT(openFolderWithModels()));
}

PageModel::~PageModel()
{
    delete ui;
}
