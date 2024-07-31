#ifndef MODELTRAININGGROUPBOX_H
#define MODELTRAININGGROUPBOX_H

#include <QMessageBox>
#include <QFileDialog>
#include <QGroupBox>
#include <QFile>

#include "softmaxcrossentropyloss.h"
#include "consistenttrainer.h"
#include "lstmmodel.h"
#include "adagrad.h"
#include "sgd.h"

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
    LSTMModel *_loadedModel; // текущая загруженная модель нейронной сети
    double _trainingRate; // обученность выбранной модели
    double _epochsCompleted; // количество пройденных эпох обучения
    IOptimizer *_currentOptimizer; // оптимизатор, используемый в тренере
    ConsistentTrainer *_trainer; // основной обьект виджета обучения

private:
    ///
    /// \brief newTrainerForModel инициализация
    /// тренера для загруженной модели с нуля
    void newTrainerForModel();
    ///
    /// \brief trainPreDataIsCorrect проверки
    /// корректности заполнения всех связанных виджетов тренировки
    /// \return флаг корректности
    bool trainPreDataIsCorrect();

private slots:    
    ///
    /// \brief selectSGDOptimizer если был выбран оптимизатор
    /// типа SGD с помощью радио кнопки
    void selectSGDOptimizer();
    ///
    /// \brief selectAdaGradOptimizer если был выбран оптимизатор
    /// типа AdaGrad c помощью соотвествующей ради кнопки
    void selectAdaGradOptimizer();
    ///
    /// \brief updateOptimizerLearningRate обновление
    /// рейтинга обучения текущего оптимизатора
    /// \param newRate новый рейтинг обучения из виджета спинбокс
    void updateOptimizerLearningRate(const double newRate);
    ///
    /// \brief checkCurrentModel просмотр доступности текущей модели
    /// \param modelPathAndName путь по которому проверяется доступность
    void checkCurrentModel(const QString modelPathAndName);
    ///
    /// \brief checkModelForTrainBefore просмотр наличия файла обучения
    /// (тренера) в папке с выбранной моделью нейронной сети
    /// \param modelPath путь до папки с моделью
    void checkModelForTrainBefore();
    ///
    /// \brief chooseModelFolderPath слот выбора
    /// папки с моделью для обучения
    void chooseModelFolderPath();
    ///
    /// \brief loadExistingTrainer загрузка
    /// (при наличии) данных тренера
    /// \param path путь до папки с тренером(его файлом)
    void loadExistingTrainer();
    ///
    /// \brief trainModel главный метод-слот данного
    /// виджета для тренировки выбранной модели
    void trainModel();

public:
    explicit ModelTrainingGroupBox(QWidget *parent = nullptr);
    ~ModelTrainingGroupBox();

    // суффикс именования файла с данными об обучении
    static QString TRAINING_DATA_NAME;

signals:
    ///
    /// \brief selectedModelCorrect
    /// когда модель для обучения успешно выбрана и загружена
    void selectedModelCorrect();
    ///
    /// \brief trainerExists
    /// в случае, если модель ранее обучалась
    void trainerExists();

};

#endif // MODELTRAININGGROUPBOX_H
