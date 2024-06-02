#include "softmaxcrossentropyloss.h"

SoftmaxCrossEntropyLoss::SoftmaxCrossEntropyLoss(double stabBorder)
    : stabBorder{stabBorder}
{
}

double SoftmaxCrossEntropyLoss::forward(vector<vector<double>> prediction,
                                        vector<vector<double>> target)
{
    // остальные операции...
    _prediction = prediction;
    _target = target;
    // возвращаем расчитанную потерю
    return calculate();
}

vector<vector<double>> SoftmaxCrossEntropyLoss::backward()
{

}

double SoftmaxCrossEntropyLoss::calculate()
{
    try {
        // 1) приводим прогнозы к нужному формату ([0,1])
        _softmaxPrediction = ActivationFunctions::batchSoftmax(_prediction);
        // 2) обрезаем обработанные предсказания
        // ([stabBorder, 1-stabBorder]),
        // дабы избежать числовой нестабильности
        _softmaxPrediction = Matrix2d<double>::clip(
            _softmaxPrediction,
            stabBorder
            );
        // 3) Вычисление матрицы потерь
        vector<vector<double>> firstOperand
            = Matrix2d<double>::multiplication(
                Matrix2d<double>::multiplication(_target, -1),
                Matrix2d<double>::logn(_softmaxPrediction)
                );
        vector<vector<double>> secondOperand
            = Matrix2d<double>::multiplication(
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
        cout << "Matrix exception:\n[" << e.what() << "]" << endl;
    }
}

vector<vector<double>> SoftmaxCrossEntropyLoss::inputGradient()
{

}
