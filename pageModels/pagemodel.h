#ifndef PAGEMODEL_H
#define PAGEMODEL_H

#include <QWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QDirIterator>
#include <QDir>

#include "directorymodelview.h"
#include "ineuralnetworkmodel.h"

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

public:
    explicit PageModel(QWidget *parent = nullptr);
    ~PageModel();

};

#endif // PAGEMODEL_H
