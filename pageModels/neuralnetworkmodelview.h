#ifndef NEURALNETWORKMODELVIEW_H
#define NEURALNETWORKMODELVIEW_H

#include <QAbstractListModel>
#include <QObject>

#include "ineuralnetworkmodel.h"

class NeuralNetworkModelView : public QAbstractListModel
{
    Q_OBJECT

private:
    QList<INeuralNetworkModel *> _dataList;

public:
    explicit NeuralNetworkModelView(QObject *parent = nullptr);

    // QAbstractItemModel interface
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    //

};

#endif // NEURALNETWORKMODELVIEW_H
