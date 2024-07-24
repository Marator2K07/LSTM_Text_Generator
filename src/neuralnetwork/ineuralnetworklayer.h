#ifndef INEURALNETWORKLAYER_H
#define INEURALNETWORKLAYER_H

#include <QList>
#include <QFile>
#include <QDir>

#include "matrix3d.h"
#include "lstmnode.h"
#include "activationfunctions.h"
#include "neuralnetworkexception.h"

///
/// \brief The INeuralNetworkLayer interface
/// описание функциональности слоя нейронной сети
class INeuralNetworkLayer
{
public:
    ///
    /// \brief name геттер имени слоя
    /// \return текущее имя слоя
    virtual QString name() const = 0;
    ///
    /// \brief compare сравнение с другим слоем
    /// \param layer другой слой для сравнения
    virtual bool compareLayer(const INeuralNetworkLayer *layer) = 0;
    ///
    /// \brief paramAt получение параметра слоя сети по заданным ключам
    /// \param firstKey - вторичный ключ параметров слоя
    /// \param secondKey - вторичный ключ параметров слоя
    /// \return текущее значение определенного параметра слоя
    virtual Matrix2d<double> paramAt(const QString firstKey,
                                     const QString secondKey) const = 0;
    ///
    /// \brief updateParam обновление параметра
    /// слоя сети в процессе оптимизации
    /// \param firstKey - вторичный ключ параметров слоя
    /// \param secondKey - вторичный ключ параметров слоя
    /// \param value - новое значение
    virtual void updateParam(const QString firstKey,
                             const QString secondKey,
                             const Matrix2d<double> value) = 0;
    ///
    /// \brief initParams инициализация параметров слоя
    /// по размерам входящей трехмерной матрицы
    /// \param initMatrix матрица для инициализации
    virtual void initParams(const Matrix3d<double> initMatrix) = 0;
    ///
    /// \brief saveParams сохрание значений параметров слоя в файл
    /// \param path уточнение пути для сохранения
    virtual void saveParams(const QString path = QDir::currentPath()) = 0;
    ///
    /// \brief loadParams загрузка значений параметров из файла
    /// \param path уточнение пути для загрузки
    virtual void loadParams(const QString path = QDir::currentPath()) = 0;
    ///
    /// \brief params геттер параметров слоя в виде словаря
    /// \return словарь параметров(не гипер) слоя
    virtual QMap<QString, QMap<QString, Matrix2d<double>>> params() const = 0;
    ///
    /// \brief saveHyperParams сохранение гиперпараметров слоя
    /// \param path путь сохранения
    virtual void saveHyperParams(const QString path = QDir::currentPath()) = 0;
    ///
    /// \brief loadHyperParams сохранение гиперпараметров слоя
    /// \param path путь загрузки
    virtual void loadHyperParams(const QString path = QDir::currentPath()) = 0;
    ///
    /// \brief clearGraients чистка накопившихся градиентов слоя
    virtual void clearGradients() = 0;
    ///
    /// \brief forward вычисление предсказания на основе
    /// текущего состояния нейронов
    /// \param xSequenceIn трехмерная матрица партии входящих значений
    /// \return обработанная слоем партия значений
    virtual Matrix3d<double> forward(Matrix3d<double> xSequenceIn) = 0;
    ///
    /// \brief backward обратное распостранение ошибки - корректировка
    /// коэффициентов слоя/модели в направлении уменьшения ошибки предсказания
    /// \param xSequenceOutGrad трехмерная матрица партии градиентов по выходу
    /// \return партия градиентов по входу
    virtual Matrix3d<double> backward(Matrix3d<double> xSequenceOutGrad) = 0;
};

#endif // INEURALNETWORKLAYER_H
