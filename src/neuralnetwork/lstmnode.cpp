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
    // создаем комбинированный вход Z - обьединение
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
                .simplifiedMult(&input["C_in"])
                ->addition(_forwardPassValues["i"]
                               .simplifiedMult(&_forwardPassValues["C_bar"])
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
    // обновление производных слоя данных на основе выходных градиентов
    layerParams["W_v"]["deriv"] = Matrix2d<double>(
        layerParams["W_v"]["deriv"]
            .addition(
                _forwardPassValues["H_out"]
                    .transposition()
                    ->multiplication(&outputGrad["X_out_grad"])
                    .get()
                )->data()
        );
    layerParams["B_v"]["deriv"] = Matrix2d<double>(
        layerParams["B_v"]["deriv"]
            .addition(
                outputGrad["X_out_grad"]
                    .axisSumMatrix(0).get()
                )->data()
        );
    // вычисление производной по состоянию слоя
    // и добавление к ней градиента предыдущего шага
    Matrix2d<double> dHOut(
        outputGrad["X_out_grad"]
            .multiplication(
                layerParams["W_v"]["value"].transposition().get()
                )
            ->addition(&outputGrad["H_out_grad"])->data()
        );
    // вычисление производной по выходному затвору 'output gate'
    // и производной его промежуточного значения
    Matrix2d<double> dO(
        dHOut.simplifiedMult(
                 ActivationFunctions<double>
                 ::tanh(&_forwardPassValues["C_out"]).get())->data()
        );
    Matrix2d<double> dOInter(
        dO.simplifiedMult(
              ActivationFunctions<double>
              ::dsigmoid(&_forwardPassValues["o_inter"]).get())->data()
        );
    // обновление производных слоя для выходного затвора(шлюза)
    layerParams["W_o"]["deriv"] = Matrix2d<double>(
        layerParams["W_o"]["deriv"]
            .addition(
                _forwardPassValues["Z"]
                    .transposition()
                    ->multiplication(&dOInter)
                    .get()
                )->data()
        );
    layerParams["B_o"]["deriv"] = Matrix2d<double>(
        layerParams["B_o"]["deriv"]
            .addition(
                dOInter.axisSumMatrix(0).get()
                )->data()
        );
    // производная по выходному состоянию ячейки
    // и добавление к ней градиента предыдущего шага
    Matrix2d<double> dCOut(
        dHOut.simplifiedMult(&_forwardPassValues["o"])
            ->simplifiedMult(
                ActivationFunctions<double>
                ::dtanh(&_forwardPassValues["C_out"]).get()
                )
            ->addition(&outputGrad["C_out_grad"])->data()
        );
    // вычисление производной по входному состоянию ячейки
    // и производной ее промежуточного значения
    Matrix2d<double> dCBar(
        dCOut.simplifiedMult(&_forwardPassValues["i"])->data()
        );
    Matrix2d<double> dCBarInter(
        dCBar.simplifiedMult(
            ActivationFunctions<double>
            ::dtanh(&_forwardPassValues["C_bar_inter"]).get())->data()
        );
    // обновление производных слоя для состояния ячейки
    layerParams["W_c"]["deriv"] = Matrix2d<double>(
        layerParams["W_c"]["deriv"]
            .addition(
                _forwardPassValues["Z"]
                    .transposition()
                    ->multiplication(&dCBarInter)
                    .get()
                )->data()
        );
    layerParams["B_c"]["deriv"] = Matrix2d<double>(
        layerParams["B_c"]["deriv"]
            .addition(
                dCBarInter.axisSumMatrix(0).get()
                )->data()
        );
    // вычисление производной по входному затвору 'output gate'
    // и производной его промежуточного значения
    Matrix2d<double> dI(
        dCOut.simplifiedMult(&_forwardPassValues["C_bar"])->data()
        );
    Matrix2d<double> dIInter(
        dI.simplifiedMult(
              ActivationFunctions<double>
              ::dsigmoid(&_forwardPassValues["i_inter"]).get())->data()
        );
    // обновление производных слоя для входного затвора(шлюза)
    layerParams["W_i"]["deriv"] = Matrix2d<double>(
        layerParams["W_i"]["deriv"]
            .addition(
                _forwardPassValues["Z"]
                    .transposition()
                    ->multiplication(&dIInter)
                    .get()
                )->data()
        );
    layerParams["B_i"]["deriv"] = Matrix2d<double>(
        layerParams["B_i"]["deriv"]
            .addition(
                dIInter.axisSumMatrix(0).get()
                )->data()
        );
    // вычисление производной по затвору забывания 'forget gate'
    // и производной его промежуточного значения
    Matrix2d<double> dF(
        dCOut.simplifiedMult(&_forwardPassValues["C_in"])->data()
        );
    Matrix2d<double> dFInter(
        dF.simplifiedMult(
              ActivationFunctions<double>
              ::dsigmoid(&_forwardPassValues["f_inter"]).get())->data()
        );
    // обновление производных слоя для затвора(шлюза) забывания
    layerParams["W_f"]["deriv"] = Matrix2d<double>(
        layerParams["W_f"]["deriv"]
            .addition(
                _forwardPassValues["Z"]
                    .transposition()
                    ->multiplication(&dFInter)
                    .get()
                )->data()
        );
    layerParams["B_f"]["deriv"] = Matrix2d<double>(
        layerParams["B_f"]["deriv"]
            .addition(
                dFInter.axisSumMatrix(0).get()
                )->data()
        );
}
