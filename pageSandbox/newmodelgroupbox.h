#ifndef NEWMODELGROUPBOX_H
#define NEWMODELGROUPBOX_H

#include <QDoubleSpinBox>
#include <QGroupBox>
#include <QSpinBox>

///
/// \brief The ColumnName enum
/// названия столбцов таблицы со слоями
/// ради удобства вынесены в перечисление
enum class ColumnName {
    NAME = 0,
    SCALE,
    HIDDEN_SIZE
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
    static long LAYERS_CREATED;

private slots:
    ///
    /// \brief addNewLayer слот создания
    /// нового слоя нейронной сети
    void addNewLayer();

public:
    explicit NewModelGroupBox(QWidget *parent = nullptr);
    ~NewModelGroupBox();

};

#endif // NEWMODELGROUPBOX_H
