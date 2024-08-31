#ifndef NEWMODELGROUPBOX_H
#define NEWMODELGROUPBOX_H

#include <QDoubleSpinBox>
#include <QFileDialog>
#include <QGroupBox>
#include <QSpinBox>

#include "aboutlearningdatadialog.h"
#include "softmaxcrossentropyloss.h"
#include "charasvectorembedding.h"
#include "aboutmodeldatadialog.h"
#include "aboutlayersdialog.h"
#include "lstmmodel.h"

///
/// \brief The ColumnName enum
/// названия столбцов таблицы со слоями
/// ради удобства вынесены в перечисление
enum class ColumnName {
    NAME = 0,
    SCALE,
    HIDDEN_SIZE,
    DELETE_BUTTON
};

namespace Ui {
class NewModelGroupBox;
}

///
/// \brief The NewModelGroupBox class
/// виджет со всем необходимым содержимым для создания
/// нового экземпляра модели нейронной сети типа LSTM
class NewModelGroupBox : public QGroupBox
{
    Q_OBJECT

private:
    Ui::NewModelGroupBox *ui;
    AboutLayersDialog *_layersHelpDialog; // окно справка о слоях нейр. сети
    AboutLearningDataDialog *_learningDataHelpDialog; // справка об обуч. данных
    AboutModelDataDialog *_modelDataHelpDialog; // справка об основн. параметрах сети
    static long LAYERS_CREATED;
    static int STANDART_FONT_SIZE;
    static QString STANDART_FONT_NAME;
    static double MIN_LAYER_SCALE; // минимальная точность создаваемого слоя модели
    static double MAX_LAYER_SCALE; // максимальная точность создаваемого слоя модели
    static double LAYER_SCALE_STEP; // шаг изменения точности слоя модели для виджета
    static int LAYER_SCALE_DECIMALS_COUNT;
    static int MIN_LAYER_HIDDEN_SIZE; // минимальный скрытый размер созд. слоя модели
    static int MAX_LAYER_HIDDEN_SIZE; // максимальный скрытый размер созд. слоя модели
    static long MIN_NAME_MODEL_LENGTH;
    static long MIN_COUNT_MODEL_LAYERS;
    static int LAYERS_COLUMN_NAME_WIDTH;
    static int LAYERS_COLUMN_SCALE_WIDTH;
    static int LAYERS_COLUMN_HIDDEN_SIZE_WIDTH;
    static int LAYERS_COLUMN_DELETE_BUTTON_WIDTH;
    static int LAYERS_COLUMN_DELETE_BUTTON_HEIGHT;

private:
    ///
    ///\brief layersFromTable получение списка
    /// слоев с формы заполнения в виде таблицы
    /// \param outputSize размер выхода для слоя
    /// \return текущий список с виджета таблицы
    QList<INeuralNetworkLayer *> layersFromTable(int outputSize) const;

private slots:
    ///
    /// \brief newModelDataCheck слот проверки
    /// всех полей ввода и выбора перед созданием новой модели
    void newModelDataCheck();
    ///
    /// \brief createAndSaveNewModel создание и сохранение
    /// свежесозданной модели после удачной проверки
    void createAndSaveNewModel();
    ///
    /// \brief openLearningData слот выбора
    /// текстовых обучающих данных для модели
    void chooseLearningData();
    ///
    /// \brief chooseModelSavePath слот выбора
    /// пути сохранения модели
    void chooseModelSavePath();
    ///
    /// \brief addNewLayer слот создания
    /// нового слоя нейронной сети
    void addNewLayer();
    ///
    /// \brief deleteSelectedLayer слот удаления
    /// созданного слоя по индексу строки в которой
    /// находится непосредственно кнопка
    void deleteSelectedLayer();    

public:
    explicit NewModelGroupBox(QWidget *parent = nullptr);
    ~NewModelGroupBox();

signals:
    ///
    /// \brief modelReadyToBeCreated после проверки
    /// корректности данных для создания при успешном
    /// исходе посылается данный сигнал
    void modelReadyToBeCreated();

};

#endif // NEWMODELGROUPBOX_H
