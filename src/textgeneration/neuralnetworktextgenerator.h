#ifndef NEURALNETWORKTEXTGENERATOR_H
#define NEURALNETWORKTEXTGENERATOR_H

#include <QObject>

#include "itextgenerator.h"

///
/// \brief The NeuralNetworkTextGenerator class
/// генератор текста на основе модели нейронной сети
class NeuralNetworkTextGenerator : public QObject,
                                   public ITextGenerator
{
    Q_OBJECT

private:
    INeuralNetworkModel *_neuralNetworkModel;

    // поле для работы метода generation в отдельном потоке
    vector<int> _contextOnAssignment; // полученный контекст по заданию

public:
    explicit NeuralNetworkTextGenerator(INeuralNetworkModel *neuralNetworkModel,
                                        QObject *parent = nullptr);
    explicit NeuralNetworkTextGenerator(QObject *parent = nullptr);

public:
    // ITextGeneration interface
    INeuralNetworkModel *neuralNetworkModel() const override;
    void setNeuralNetworkModel(INeuralNetworkModel *model) override;
    //

public slots:
    // ITextGeneration interface
    void generate() override;
    void applyAssignmentForGenerate(vector<int> context) override;
    //

signals:
    // ITextGenerator interface
    void showGenerationInfo(const QString symbol) override;
    void generationStoped() override;
    //

};

#endif // NEURALNETWORKTEXTGENERATOR_H
