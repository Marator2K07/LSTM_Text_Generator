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

}
