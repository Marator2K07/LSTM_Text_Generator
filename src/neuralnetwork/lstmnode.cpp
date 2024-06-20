#include "lstmnode.h"

LSTMNode::LSTMNode(int hiddenSize, int vocabSize)
    : _hiddenSize{hiddenSize}
    , _vocabSize{vocabSize}
{
}

QMap<QString, Matrix2d<double>>
LSTMNode::forward(QMap<QString, Matrix2d<double>> input,
                  QMap<QString, QMap<QString, Matrix2d<double>>> &layerParams)
{
    // запоминаем входные данные
    _forwardPassValues.insert("X_in", input["X_in"]);
    // запоминаем скрытое состояние ячейки
    _forwardPassValues.insert("C_in", input["C_in"]);
    // создаем комбинированный вход Z - обьединенные
    // входных данных и скрытого состояния
    _forwardPassValues.insert(
        "Z",
        Matrix2d<double>(input["X_in"].columnStack(&input["H_in"])->data())
        );
    // промежуточное и окончательное значения затвора забывания 'forget gate'
    _forwardPassValues.insert(
        "f_inter",
        Matrix2d<double>(
            _forwardPassValues["Z"]
                .multiplication(&layerParams["W_f"]["value"])
                ->addition(&layerParams["B_f"]["value"])
                ->data())
        );
    _forwardPassValues.insert(
        "f",
        Matrix2d<double>(
            ActivationFunctions<double>::sigmoid(&_forwardPassValues["f_inter"])
                ->data())
        );
    // промежуточное и икончательное значения для входного затвора 'input gate'
    _forwardPassValues.insert(
        "i_inter",
        Matrix2d<double>(
            _forwardPassValues["Z"]
                .multiplication(&layerParams["W_i"]["value"])
                ->addition(&layerParams["B_i"]["value"])
                ->data())
        );
    _forwardPassValues.insert(
        "i",
        Matrix2d<double>(
            ActivationFunctions<double>::sigmoid(&_forwardPassValues["i_inter"])
                ->data())
        );
    // промежуточное и икончательное кандидатные значения состояния памяти
    _forwardPassValues.insert(
        "С_bar_inter",
        Matrix2d<double>(
            _forwardPassValues["Z"]
                .multiplication(&layerParams["W_c"]["value"])
                ->addition(&layerParams["B_c"]["value"])
                ->data())
        );
    _forwardPassValues.insert(
        "C_bar",
        Matrix2d<double>(
            ActivationFunctions<double>::tanh(&_forwardPassValues["С_bar_inter"])
                ->data())
        );
    // промежуточное и икончательное значения для выходного затвора 'output gate'
    _forwardPassValues.insert(
        "o_inter",
        Matrix2d<double>(
            _forwardPassValues["Z"]
                .multiplication(&layerParams["W_o"]["value"])
                ->addition(&layerParams["B_o"]["value"])
                ->data())
        );
    _forwardPassValues.insert(
        "o",
        Matrix2d<double>(
            ActivationFunctions<double>::sigmoid(&_forwardPassValues["o_inter"])
                ->data())
            );
}

QMap<QString, Matrix2d<double>>
LSTMNode::backward(QMap<QString, Matrix2d<double>> outputGrad,
                   QMap<QString, QMap<QString, Matrix2d<double>>> &layerParams)
{

}
