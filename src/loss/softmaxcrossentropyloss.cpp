#include "softmaxcrossentropyloss.h"

SoftmaxCrossEntropyLoss::SoftmaxCrossEntropyLoss(double stabBorder)
    : _stabBorder{stabBorder}
{
}

double SoftmaxCrossEntropyLoss::forward(IMatrix<double> *prediction,
                                        IMatrix<double> *target)
{
    // подготовительные операции
    _prediction = prediction;
    _target = target;
    // возвращаем расчитанную потерю
    return calcLoss();
}

unique_ptr<IMatrix<double> > SoftmaxCrossEntropyLoss::backward()
{
    // подготовительные операции
    _inputGradient = calcInputGradient();
    // ...
    // вовзращаем расчитанный градиент
    return _inputGradient;
}

double SoftmaxCrossEntropyLoss::calcLoss()
{
    try {
        // 1) приводим прогнозы к нужному формату ([0,1])
        _softmaxPrediction = ActivationFunctions::batchSoftmax(_prediction);
        // 2) обрезаем обработанные предсказания
        // ([stabBorder, 1-stabBorder]),
        // дабы избежать числовой нестабильности
        _softmaxPrediction = Matrix2d<double>::clip(
            _softmaxPrediction,
            _stabBorder
        );
        // 3) Вычисление матрицы потерь
        vector<vector<double>> firstOperand
            = Matrix2d<double>::simplifiedMult(
                Matrix2d<double>::multiplication(_target, -1),
                Matrix2d<double>::logn(_softmaxPrediction)
            );
        vector<vector<double>> secondOperand
            = Matrix2d<double>::simplifiedMult(
                Matrix2d<double>::subtraction(_target, 1.0, true),
                Matrix2d<double>::logn(
                    Matrix2d<double>::subtraction(
                        _softmaxPrediction,
                        1.0,
                        true
                    )
                )
            );
        vector<vector<double>> softmaxCrossEntropyLoss
            = Matrix2d<double>::subtraction(firstOperand, secondOperand);
        // 4) нахождение и возврат штрафа сети
        return Matrix2d<double>::totalSum(softmaxCrossEntropyLoss);
    } catch (const MatrixException &e) {
        // если поймали исключение, то делаем его частью нового
        throw LossException(QString("Catch loss exception:\n[%1]\n")
                                .arg(e.what()));
    }
}

unique_ptr<IMatrix<double>> SoftmaxCrossEntropyLoss::calcInputGradient()
{
    try {
        return Matrix2d<double>::subtraction(_softmaxPrediction, _target);
    } catch (const MatrixException &e) {
        // если поймали исключение, то делаем его частью нового
        throw LossException(QString("Catch loss exception:\n[%1]\n")
                                .arg(e.what()));
    }
}
