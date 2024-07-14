#ifndef NEWMODELGROUPBOX_H
#define NEWMODELGROUPBOX_H

#include <QDoubleSpinBox>
#include <QFileDialog>
#include <QGroupBox>
#include <QSpinBox>

#include "aboutlayersdialog.h"
#include "aboutlearningdatadialog.h"

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
    static long LAYERS_CREATED;

private slots:
    ///
    /// \brief openLearningData слот выбора
    /// текстовых обучающих данных для модели
    void chooseLearningData();
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

};

#endif // NEWMODELGROUPBOX_H
