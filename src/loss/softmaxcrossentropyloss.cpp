#include "softmaxcrossentropyloss.h"
#include "activationfunctions.cpp"

SoftmaxCrossEntropyLoss::SoftmaxCrossEntropyLoss(double stabBorder)
    : _stabBorder{stabBorder}
{
}

SoftmaxCrossEntropyLoss::~SoftmaxCrossEntropyLoss()
{
}

double SoftmaxCrossEntropyLoss::forward(IMatrix<double> *prediction,
                                        IMatrix<double> *target)
{
    // подготовительные операции
    _prediction = prediction;
    _target = target;
    // ...
    // возвращаем расчитанную потерю
    return calcLoss();
}

unique_ptr<IMatrix<double>> SoftmaxCrossEntropyLoss::backward()
{
    // подготовительные операции
    _inputGradient = calcInputGradient();
    // ...
    // вовзращаем расчитанный градиент
    return unique_ptr<IMatrix<double>>(_inputGradient);
}

double SoftmaxCrossEntropyLoss::calcLoss()
{
    try {
        // 1) приводим прогнозы к нужному формату ([0,1])
        _softmaxPrediction
            = ActivationFunctions<double>::softmax(_prediction).release();
        // 2) обрезаем обработанные предсказания
        // ([stabBorder, 1-stabBorder]),
        // дабы избежать числовой нестабильности
        _softmaxPrediction = _softmaxPrediction->clipM(
            _stabBorder,
            1-_stabBorder
        ).release();
        // 3) Вычисление матрицы потерь
        IMatrix<double> *firstOperand
            = _target->multiplication(-1)
                  ->simplifiedMult(
                      _softmaxPrediction->lognM().release()
                      ).release();
        IMatrix<double> *secondOperand
            = _target->subtraction(1.0, true)
                  ->simplifiedMult(
                      _softmaxPrediction->subtraction(1.0, true)
                          ->lognM().get()
                      ).release();

        IMatrix<double> *softmaxCrossEntropyLoss
            = firstOperand->subtraction(secondOperand).release();
        // 4) нахождение и возврат штрафа сети
        return softmaxCrossEntropyLoss->totalSum();
    } catch (const MatrixException &e) {
        // если поймали исключение, то делаем его частью нового
        throw LossException(QString("Catch loss exception:\n[%1]\n")
                                .arg(e.what()));
    }
}

IMatrix<double> *SoftmaxCrossEntropyLoss::calcInputGradient()
{
    try {
        return _softmaxPrediction->subtraction(_target).release();
    } catch (const MatrixException &e) {
        // если поймали исключение, то делаем его частью нового
        throw LossException(QString("Catch loss exception:\n[%1]\n")
                                .arg(e.what()));
    }
}
