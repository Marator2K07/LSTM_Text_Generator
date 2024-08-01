#ifndef INEURALNETWORKMODEL_H
#define INEURALNETWORKMODEL_H

#include "iloss.h"
#include "itextembedding.h"
#include "ineuralnetworklayer.h"

///
/// \brief The INeuralNetworkModel interface
/// организация функциональности модели нейронной сети
class INeuralNetworkModel
{
public:
    ///
    /// \brief save cохранение всех необходимых
    /// параметров модели в отдельной папке
    /// \param path путь сохранения
    virtual void save(const QString path = QDir::currentPath()) = 0;
    ///
    /// \brief load загрузка всех необходимых параметров из папки с моделью
    /// \param path путь к папке с моделью
    virtual void load(const QString path = QDir::currentPath()) = 0;
    ///
    /// \brief name получение имени модели
    /// \return заданное имя модели нейронной сети
    virtual QString name() const = 0;
    ///
    /// \brief power получение оценки совокупности всех параметров модели
    /// \return оценка параметров модели в виде целого числа
    virtual int power() const = 0;
    ///
    /// \brief embedding доступ к текстовому эмбеддингу для модели
    /// \return текущий эмбеддинг
    virtual ITextEmbedding<double> *embedding() const = 0;
    ///
    /// \brief layers доступ к слоям нейронной сети
    /// \return список слоев данной модели
    virtual QList<INeuralNetworkLayer *> layers() const = 0;
    ///
    /// \brief forward прямой проход по слоям модели
    /// \param batch трехмерное представление входящих символов
    /// \return трехмерное предсказание после обработки слоями
    virtual Matrix3d<double> forward(Matrix3d<double> batch) = 0;
    ///
    /// \brief backward градиентный спуск по слоям сети
    /// \param gradient конечный градиент потерь
    /// \return итоговый(стартовый) градиент после прохода по слоям
    virtual Matrix3d<double> backward(Matrix3d<double> gradient) = 0;
    ///
    /// \brief singleStep один проход по нейронной модели:
    /// нахождение предсказания модели, вычисление потерь,
    /// обратный проход и обновление параметров сети.
    /// \param xBatch входная матрица
    /// \param yBatch целевая матриц
    /// \return потери при проходе сети
    virtual double singleStep(Matrix3d<double> xBatch,
                              Matrix3d<double> yBatch) = 0;
};

#endif // INEURALNETWORKMODEL_H
