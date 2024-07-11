#ifndef PAGEMODEL_H
#define PAGEMODEL_H

#include <QWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QDirIterator>
#include <QDir>

#include "neuralnetworktextgenerator.h"
#include "softmaxcrossentropyloss.h"
#include "directorymodelview.h"
#include "lstmmodel.h"

using namespace std;

namespace Ui {
class PageModel;
}

class PageModel : public QWidget
{
    Q_OBJECT

private:
    Ui::PageModel *ui;
    DirectoryModelView *_dirModelView; // текущая модель с папками моделей
    INeuralNetworkModel *_neuralNetworkModel; // выбранная модель нейронной сети
    NeuralNetworkTextGenerator _textGenerator;

private slots:
    ///
    /// \brief openFolderWithModels
    /// слот открытия папки с моделями нейронной сети для генерации
    void openFolderWithModels();
    ///
    /// \brief selectNeuralNetworkModel слот выбора модели
    /// нейронной сети из списка представления типа list view
    /// \param index выбранный индекс модели в представлении
    void selectNeuralNetworkModel(QModelIndex index);
    ///
    /// \brief strToVector преобразование строки в вектор
    /// на основе индексов словаря эмбеддинга модели нейронной сети
    /// \param str строка для преобразования
    /// \return представление строки в виде вектора
    void stringToVector(const QString str);
    ///
    /// \brief adaptFormElements анализ текущего
    /// состояния экземпляра обьекта данной формы
    /// и блокировка/разблокировка необходимых элементов
    void adaptFormElements();

public:
    explicit PageModel(QWidget *parent = nullptr);
    ~PageModel();

signals:
    ///
    /// \brief modelChanged уведомление о смене
    /// состояния модели нейронной сети
    void neuralNetworkModelChanged();
    ///
    /// \brief strAsVectorReady сигнал о готовности строки
    /// \param context преобразованная строка
    void strAsVectorReady(const vector<int> context);

};

#endif // PAGEMODEL_H
