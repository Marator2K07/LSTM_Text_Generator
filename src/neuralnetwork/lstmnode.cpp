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
                ->data()
            )
        );
    _forwardPassValues.insert(
        "f",
        Matrix2d<double>(
            ActivationFunctions<double>::sigmoid(&_forwardPassValues["f_inter"])
                ->data()
            )
        );
    // промежуточное и икончательное значения входного затвора 'input gate'
    _forwardPassValues.insert(
        "i_inter",
        Matrix2d<double>(
            _forwardPassValues["Z"]
                .multiplication(&layerParams["W_i"]["value"])
                ->addition(&layerParams["B_i"]["value"])
                ->data()
            )
        );
    _forwardPassValues.insert(
        "i",
        Matrix2d<double>(
            ActivationFunctions<double>::sigmoid(&_forwardPassValues["i_inter"])
                ->data()
            )
        );
    // промежуточное и икончательное кандидатные значения состояния памяти
    _forwardPassValues.insert(
        "С_bar_inter",
        Matrix2d<double>(
            _forwardPassValues["Z"]
                .multiplication(&layerParams["W_c"]["value"])
                ->addition(&layerParams["B_c"]["value"])
                ->data()
            )
        );
    _forwardPassValues.insert(
        "C_bar",
        Matrix2d<double>(
            ActivationFunctions<double>::tanh(&_forwardPassValues["С_bar_inter"])
                ->data()
            )
        );
    // промежуточное и икончательное значения выходного затвора 'output gate'
    _forwardPassValues.insert(
        "o_inter",
        Matrix2d<double>(
            _forwardPassValues["Z"]
                .multiplication(&layerParams["W_o"]["value"])
                ->addition(&layerParams["B_o"]["value"])
                ->data()
            )
        );
    _forwardPassValues.insert(
        "o",
        Matrix2d<double>(
            ActivationFunctions<double>::sigmoid(&_forwardPassValues["o_inter"])
                ->data()
            )
        );
    // выходное значение состояния ячейки
    _forwardPassValues.insert(
        "C_out",
        Matrix2d<double>(
            _forwardPassValues["f"]
                .multiplication(&input["C_in"])
                ->addition(_forwardPassValues["i"]
                               .multiplication(&_forwardPassValues["C_bar"])
                               .get())
                ->data()
            )
        );
    // выходное значение скрытого состояния
    _forwardPassValues.insert(
        "H_out",
        Matrix2d<double>(
            _forwardPassValues["o"]
                .simplifiedMult(&_forwardPassValues["C_out"])
                ->data()
            )
        );
    // выходные данные
    _forwardPassValues.insert(
        "X_out",
        Matrix2d<double>(
            _forwardPassValues["H_out"]
                .multiplication(&layerParams["W_v"]["value"])
                ->addition(&layerParams["B_v"]["value"])
                ->data()
            )
        );
    // формируем и возвращаем ответ
    QMap<QString, Matrix2d<double>> result;
    result.insert("X_out", _forwardPassValues["X_out"]);
    result.insert("H_out", _forwardPassValues["H_out"]);
    result.insert("C_out", _forwardPassValues["C_out"]);
    return result;
}

QMap<QString, Matrix2d<double>>
LSTMNode::backward(QMap<QString, Matrix2d<double>> outputGrad,
                   QMap<QString, QMap<QString, Matrix2d<double>>> &layerParams)
{

}
