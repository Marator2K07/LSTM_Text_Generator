#ifndef MODELTRAININGGROUPBOX_H
#define MODELTRAININGGROUPBOX_H

#include <QMessageBox>
#include <QFileDialog>
#include <QGroupBox>
#include <QFile>

#include "lstmmodel.h"
#include "adagrad.h"
#include "sgd.h"

///
/// \brief The OptimizerType enum
/// перечисление для доступных оптимизиаторов при обучении
enum class OptimizerType {
    SGD = 0,
    ADA_GRAD,
    NONE
};

namespace Ui {
class ModelTrainingGroupBox;
}

///
/// \brief The ModelTrainingGroupBox class
/// виджет со всем необходимым содержимым для
/// тренировки(обучения или дообучения) уже
/// существующей модели нейронной сети
class ModelTrainingGroupBox : public QGroupBox
{
    Q_OBJECT

private:
    Ui::ModelTrainingGroupBox *ui;
    QString _modelNameMainPart; // основная часть имени загруженной модели
    double _trainingRate; // обученность выбранной модели
    double _epochsCompleted; // количество пройденных эпох обучения
    OptimizerType _currentOptimizerType;
    IOptimizer *_currentOptimizer;

private slots:
    ///
    /// \brief checkCurrentModel просмотр доступности текущей модели
    /// \param modelPathAndName путь по которому проверяется доступность
    void checkCurrentModel(const QString modelPathAndName);
    ///
    /// \brief chooseCurrentModel слот выбора
    /// папки с моделью для обучения
    void chooseCurrentModel();

public:
    explicit ModelTrainingGroupBox(QWidget *parent = nullptr);
    ~ModelTrainingGroupBox();

    // суффикс именования файла с данными об обучении
    static QString TRAINING_DATA_NAME;

};

#endif // MODELTRAININGGROUPBOX_H
