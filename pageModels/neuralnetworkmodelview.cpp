#include "neuralnetworkmodelview.h"

NeuralNetworkModelView::NeuralNetworkModelView(QObject *parent)
    : QAbstractListModel{parent}
{

}

int NeuralNetworkModelView::rowCount(const QModelIndex &parent) const
{
    return _dataList.size();
}

QVariant NeuralNetworkModelView::data(const QModelIndex &index, int role) const
{

}
