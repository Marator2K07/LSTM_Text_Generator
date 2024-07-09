#ifndef PAGEMODEL_H
#define PAGEMODEL_H

#include <QWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QDirIterator>
#include <QDir>

#include "softmaxcrossentropyloss.h"
#include "directorymodelview.h"
#include "lstmmodel.h"

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

};

#endif // PAGEMODEL_H
