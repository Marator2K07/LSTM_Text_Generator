#ifndef MODELTEXTGENERATIONGROUPBOX_H
#define MODELTEXTGENERATIONGROUPBOX_H

#include <QDirIterator>
#include <QFileDialog>
#include <QMessageBox>
#include <QGroupBox>
#include <QThread>
#include <QWidget>
#include <QDir>

#include "neuralnetworktextgenerator.h"
#include "softmaxcrossentropyloss.h"
#include "directorymodelview.h"
#include "lstmmodel.h"

namespace Ui {
class ModelTextGenerationGroupBox;
}

///
/// \brief The ModelTextGenerationGroupBox class
/// виджет со всем необходимым содержимым для генерации
/// текста с помощью существующей модели нейронной сети
class ModelTextGenerationGroupBox : public QGroupBox
{
    Q_OBJECT

private:
    Ui::ModelTextGenerationGroupBox *ui;
    DirectoryModelView *_dirModelView; // текущая модель с папками моделей
    INeuralNetworkModel *_neuralNetworkModel; // выбранная модель нейронной сети
    NeuralNetworkTextGenerator *_textGenerator; // основной компонент виджета генерации
    QThread _generateThread; // поток, выделенный под генерацию

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
    /// \brief generateWithModel главный метод-слот данного
    /// виджета для генерации текста на основе выбранной модели
    void generateWithModel();
    ///
    /// \brief stopGenerateWithModel слот преждевременной остановки
    /// генерации вывода текста на основе выбранной модели
    void stopGenerateWithModel();
    ///
    /// \brief adaptFormElements анализ текущего
    /// состояния экземпляра обьекта данной формы
    /// и блокировка/разблокировка необходимых элементов
    void adaptFormElements();
    ///
    /// \brief generateFormActiveState приведение формы генерации текста
    /// к состоянию неактивной генерации(разблокировка всех нужных виджетов)
    void generateFormActiveState();
    ///
    /// \brief generateFormNotActiveState приведение формы генерации текста
    /// к состоянию активной генерации(блокировка всех нужных виджетов)
    void generateFormNotActiveState();

public:
    explicit ModelTextGenerationGroupBox(QWidget *parent = nullptr);
    ~ModelTextGenerationGroupBox();

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

#endif // MODELTEXTGENERATIONGROUPBOX_H
