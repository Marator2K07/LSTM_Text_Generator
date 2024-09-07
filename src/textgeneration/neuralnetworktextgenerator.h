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
    bool _generateStoped; // флаг преждевременной остановки генерации

    // поле для работы метода generation в отдельном потоке
    QList<int> _contextOnAssignment; // полученный контекст по заданию

public:
    explicit NeuralNetworkTextGenerator(INeuralNetworkModel *neuralNetworkModel,
                                        QObject *parent = nullptr);
    explicit NeuralNetworkTextGenerator(QObject *parent = nullptr);

    static QChar DEFAULT_ENDING_SYMBOL;// символ окончания генерации по умолчанию
    static double DEFAULT_BATCH_NUM; // цифра по умолчанию для заполнения партии

public:
    // ITextGeneration interface
    INeuralNetworkModel *neuralNetworkModel() const override;
    void setNeuralNetworkModel(INeuralNetworkModel *model) override;
    //

public slots:
    // ITextGeneration interface
    void generate() override;
    void applyAssignmentForGenerate(QList<int> context) override;
    void stop() override;
    //

signals:
    // ITextGenerator interface
    void showGenerationInfo(const QString symbol) override;
    void generationStoped() override;
    //

};

#endif // NEURALNETWORKTEXTGENERATOR_H
