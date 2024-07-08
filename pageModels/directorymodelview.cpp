#include "directorymodelview.h"

DirectoryModelView::DirectoryModelView(QObject *parent)
    : QAbstractListModel{parent}
{
}

int DirectoryModelView::rowCount(const QModelIndex &parent) const
{
    return _data.size();
}

QVariant DirectoryModelView::data(const QModelIndex &index, int role) const
{
    // всевозможные проверки корректности пришедших данных
    if (!hasIndex(index.row(),
                  index.column(),
                  index.parent())) {
        return QVariant{};
    }
    // получаем информацию по роли
    switch (role) {
    case ValueRole:
        return _data.at(index.row()).path;
    case InfoRole:
        return _data.at(index.row()).name;
    case Qt::DisplayRole:
        return _data.at(index.row()).name;
    }

    return QVariant{};
}
