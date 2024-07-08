#ifndef DIRECTORYMODELVIEW_H
#define DIRECTORYMODELVIEW_H

#include <QAbstractListModel>
#include <QObject>
#include <QMap>

#include "ineuralnetworkmodel.h"

///
/// \brief The DirectoryModelView class
/// модель для представления папок в виде
/// ее названия - отображаемой части и пути к ней
class DirectoryModelView : public QAbstractListModel
{
    Q_OBJECT

private:
    // данные в виде словаря имени папки -> пути к ней
    QMap<QString, QString> _data;

public:
    explicit DirectoryModelView(QObject *parent = nullptr);

    // QAbstractItemModel interface
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    //

};

#endif // DIRECTORYMODELVIEW_H
