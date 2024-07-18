#include "modeltraininggroupbox.h"
#include "ui_modeltraininggroupbox.h"

void ModelTrainingGroupBox::checkCurrentModel(const QString modelPathAndName)
{
    // находим основную часть имени модели
    QString fileNameMainPart = modelPathAndName.right(
        modelPathAndName.length() - modelPathAndName.lastIndexOf("/") - 1
        );
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
    } else {
        ui->frame->setEnabled(false);
        _modelNameMainPart = QString();
        QMessageBox::warning(
            this,
            "Предупреждение",
            "По указанному пути не существует модели для обучения"
            );
    }
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

ModelTrainingGroupBox::ModelTrainingGroupBox(QWidget *parent)
    : QGroupBox(parent)
    , ui(new Ui::ModelTrainingGroupBox)
    , _modelNameMainPart{QString()}
{
    ui->setupUi(this);

    connect(ui->chooseCurrentModelButton, SIGNAL(pressed()),
            this, SLOT(chooseCurrentModel()));
    connect(ui->currentModelLineEdit, SIGNAL(textChanged(QString)),
            this, SLOT(checkCurrentModel(QString)));
}

ModelTrainingGroupBox::~ModelTrainingGroupBox()
{
    delete ui;
}
