#ifndef DIRECTORYMODELVIEW_H
#define DIRECTORYMODELVIEW_H

#include <QAbstractListModel>
#include <QObject>

#include "ineuralnetworkmodel.h"

///
/// \brief The FolderData class
/// свое представление данных о папке
struct FolderData {
    QString path;
    QString name;
    FolderData(QString pathD, QString nameD) {
        path = pathD;
        name = nameD;
    }
};

///
/// \brief The DirectoryModelView class
/// модель для представления папок в виде
/// ее названия - отображаемой части и пути к ней
class DirectoryModelView : public QAbstractListModel
{
    Q_OBJECT

private:
    QList<FolderData> _data; // список данных для папок

public:
    explicit DirectoryModelView(QObject *parent = nullptr);

public:
    ///
    /// \brief The Roles enum
    /// роли для данного представления модели
    enum Roles {
        ValueRole = Qt::UserRole + 1,
        InfoRole
    };

    ///
    /// \brief addFolder добавление новой папки в модель
    /// \param path путь до добавленной папки
    /// \param name путь до добавленной папки
    void addFolder(QString path, QString name);

    // QAbstractItemModel interface
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    //

};

#endif // DIRECTORYMODELVIEW_H
