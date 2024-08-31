#include "aboutlearningdatadialog.h"
#include "ui_aboutlearningdatadialog.h"

void AboutLearningDataDialog::preloadData()
{
    // подготовка
    ui->learningDataTextEdit->clear();
    QFile file(_pathLearningData);
    // пытаемся открыть обучающие данные
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // если все впорядке построчно пишем данные в текстовое поле
        QTextStream txtStream(&file);
        while (!txtStream.atEnd()) {
            QString line = txtStream.readLine();
            ui->learningDataTextEdit->appendPlainText(line);
        }
    } else {
        QMessageBox::warning(
            this,
            "Предупреждение",
            "Обучающие данные не выбраны"
            );
        ui->learningDataTextEdit->appendPlainText(
            "Обучающие данные не выбраны"
            );
    }
}

AboutLearningDataDialog::AboutLearningDataDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AboutLearningDataDialog)
    , _learningData{QString()}
    , _pathLearningData{QString()}
{
    ui->setupUi(this);

    connect(ui->buttonBox, SIGNAL(accepted()),
            this, SLOT(accept()));
}

AboutLearningDataDialog::~AboutLearningDataDialog()
{
    delete ui;
}

void AboutLearningDataDialog::updateLearningDataPath(const QString &path)
{
    _pathLearningData = path;
}
