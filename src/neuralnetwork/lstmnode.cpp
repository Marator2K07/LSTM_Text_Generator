#include "lstmnode.h"
#include "matrix2d.cpp"
#include "activationfunctions.cpp"

void LSTMNode::cleanUp()
{
    // очищаем память по указателям
    if (_xIn != nullptr) {
        delete _xIn;
        _xIn = nullptr;
    }
    if (_cIn != nullptr) {
        delete _cIn;
        _cIn = nullptr;
    }
    if (_z != nullptr) {
        delete _z;
        _z = nullptr;
    }
    if (_fInter != nullptr) {
        delete _fInter;
        _fInter = nullptr;
    }
    if (_f != nullptr) {
        delete _f;
        _f = nullptr;
    }
    if (_iInter != nullptr) {
        delete _iInter;
        _iInter = nullptr;
    }
    if (_i != nullptr) {
        delete _i;
        _i = nullptr;
    }
    if (_cBarInter != nullptr) {
        delete _cBarInter;
        _cBarInter = nullptr;
    }
    if (_cBar != nullptr) {
        delete _cBar;
        _cBar = nullptr;
    }
    if (_oInter != nullptr) {
        delete _oInter;
        _oInter = nullptr;
    }
    if (_o != nullptr) {
        delete _o;
        _o = nullptr;
    }
    if (_cOut != nullptr) {
        delete _cOut;
        _cOut = nullptr;
    }
    if (_hOut != nullptr) {
        delete _hOut;
        _hOut = nullptr;
    }
    if (_xOut != nullptr) {
        delete _xOut;
        _xOut = nullptr;
    }
}

LSTMNode::LSTMNode()
    : _xIn{nullptr}
    , _cIn{nullptr}
    , _z{nullptr}
    , _fInter{nullptr}
    , _f{nullptr}
    , _iInter{nullptr}
    , _i{nullptr}
    , _cBarInter{nullptr}
    , _cBar{nullptr}
    , _oInter{nullptr}
    , _o{nullptr}
    , _cOut{nullptr}
    , _hOut{nullptr}
    , _xOut{nullptr}
{
}
{
}

QMap<QString, Matrix2d<double>>
LSTMNode::forward(Matrix2d<double> xIn,
                  Matrix2d<double> hIn,
                  Matrix2d<double> cIn,
                  QMap<QString, QMap<QString, Matrix2d<double>>> &layerParams)
{
    try {
        // запоминаем входные данные
        _forwardPassValues.insert("X_in", new Matrix2d(xIn));
        // запоминаем скрытое состояние ячейки
        _forwardPassValues.insert("C_in", new Matrix2d(cIn));
        // создаем комбинированный вход Z - обьединение
        // входных данных и скрытого состояния
        _forwardPassValues.insert(
            "Z",
            xIn.columnStack(&hIn).release()
            );
        // промежуточное и окончательное значения затвора забывания 'forget gate'
        _forwardPassValues.insert(
            "f_inter",            
            _forwardPassValues["Z"]
                ->multiplication(&layerParams["W_f"]["value"])
                ->addition(&layerParams["B_f"]["value"])
                .release()
            );
        _forwardPassValues.insert(
            "f",
            ActivationFunctions<double>::sigmoid(_forwardPassValues["f_inter"])
                .release()
            );
        // промежуточное и икончательное значения входного затвора 'input gate'
        _forwardPassValues.insert(
            "i_inter",
            _forwardPassValues["Z"]
                ->multiplication(&layerParams["W_i"]["value"])
                ->addition(&layerParams["B_i"]["value"])
                .release()
            );
        _forwardPassValues.insert(
            "i",
            ActivationFunctions<double>::sigmoid(_forwardPassValues["i_inter"])
                .release()
            );
        // промежуточное и икончательное кандидатные значения состояния памяти
        _forwardPassValues.insert(
            "C_bar_inter",
            _forwardPassValues["Z"]
                ->multiplication(&layerParams["W_c"]["value"])
                ->addition(&layerParams["B_c"]["value"])
                .release()
            );
        _forwardPassValues.insert(
            "C_bar",
            ActivationFunctions<double>::tanh(_forwardPassValues["C_bar_inter"])
                .release()
            );
        // промежуточное и икончательное значения выходного затвора 'output gate'
        _forwardPassValues.insert(
            "o_inter",
            _forwardPassValues["Z"]
                ->multiplication(&layerParams["W_o"]["value"])
                ->addition(&layerParams["B_o"]["value"])
                .release()
            );
        _forwardPassValues.insert(
            "o",
            ActivationFunctions<double>::sigmoid(_forwardPassValues["o_inter"])
                .release()
            );
        // выходное значение состояния ячейки
        _forwardPassValues.insert(
            "C_out",
            _forwardPassValues["f"]
                ->simplifiedMult(&cIn)
                ->addition(_forwardPassValues["i"]
                               ->simplifiedMult(_forwardPassValues["C_bar"])
                               .get())
                .release()
            );
        // выходное значение скрытого состояния
        _forwardPassValues.insert(
            "H_out",
            _forwardPassValues["o"]
                ->simplifiedMult(_forwardPassValues["C_out"])
                .release()
            );
        // выходные данные
        _forwardPassValues.insert(
            "X_out",
            _forwardPassValues["H_out"]
                ->multiplication(&layerParams["W_v"]["value"])
                ->addition(&layerParams["B_v"]["value"])
                .release()
            );
        // формируем и возвращаем ответ
        QMap<QString, Matrix2d<double>> result;
        result.insert("X_out",
                      Matrix2d<double>((Matrix2d<double>*)_forwardPassValues["X_out"]));
        result.insert("H_out",
                      Matrix2d<double>((Matrix2d<double>*)_forwardPassValues["H_out"]));
        result.insert("C_out",
                      Matrix2d<double>((Matrix2d<double>*)_forwardPassValues["C_out"]));
        return result;
    } catch (const MatrixException &e) {
        throw NeuralNetworkException(
            QString("\nNeural network node exception \n[%1]<-[%2]\n")
                .arg("Error in forward pass", e.what())
            );
    }
}

QMap<QString, Matrix2d<double>>
LSTMNode::backward(Matrix2d<double> xOutGrad,
                   Matrix2d<double> hOutGrad,
                   Matrix2d<double> cOutGrad,
                   QMap<QString, QMap<QString, Matrix2d<double>>> &layerParams)
{
    try {
        // обновление производных слоя данных на основе выходных градиентов
        layerParams["W_v"]["deriv"] = Matrix2d<double>(
            layerParams["W_v"]["deriv"]
                .addition(
                    _forwardPassValues["H_out"]
                        ->transposition()
                        ->multiplication(&xOutGrad)
                        .get()
                    )
            );
        layerParams["B_v"]["deriv"] = Matrix2d<double>(
            layerParams["B_v"]["deriv"]
                .addition(
                    xOutGrad.axisSum(0).get()
                    )
            );
        // вычисление производной по состоянию слоя
        // и добавление к ней градиента предыдущего шага
        Matrix2d<double> dHOut(
            xOutGrad
                .multiplication(
                    layerParams["W_v"]["value"].transposition().get()
                    )
                ->addition(&hOutGrad)
            );
        // вычисление производной по выходному затвору 'output gate'
        // и производной его промежуточного значения
        Matrix2d<double> dO(
            dHOut.simplifiedMult(
                     ActivationFunctions<double>
                     ::tanh(_forwardPassValues["C_out"]).get())
            );
        Matrix2d<double> dOInter(
            dO.simplifiedMult(
                  ActivationFunctions<double>
                  ::dsigmoid(_forwardPassValues["o_inter"]).get())
            );
        // обновление производных слоя для выходного затвора(шлюза)
        layerParams["W_o"]["deriv"] = Matrix2d<double>(
            layerParams["W_o"]["deriv"]
                .addition(
                    _forwardPassValues["Z"]
                        ->transposition()
                        ->multiplication(&dOInter)
                        .get()
                    )
            );
        layerParams["B_o"]["deriv"] = Matrix2d<double>(
            layerParams["B_o"]["deriv"]
                .addition(
                    dOInter.axisSum(0).get()
                    )
            );
        // производная по выходному состоянию ячейки
        // и добавление к ней градиента предыдущего шага
        Matrix2d<double> dCOut(
            dHOut.simplifiedMult(_forwardPassValues["o"])
                ->simplifiedMult(
                    ActivationFunctions<double>
                    ::dtanh(_forwardPassValues["C_out"]).get()
                    )
                ->addition(&cOutGrad)
            );
        // вычисление производной по входному состоянию ячейки
        // и производной ее промежуточного значения
        Matrix2d<double> dCBar(
            dCOut.simplifiedMult(_forwardPassValues["i"])
            );
        Matrix2d<double> dCBarInter(
            dCBar.simplifiedMult(
                ActivationFunctions<double>
                ::dtanh(_forwardPassValues["C_bar_inter"]).get())
            );
        // обновление производных слоя для состояния ячейки
        layerParams["W_c"]["deriv"] = Matrix2d<double>(
            layerParams["W_c"]["deriv"]
                .addition(
                    _forwardPassValues["Z"]
                        ->transposition()
                        ->multiplication(&dCBarInter)
                        .get()
                    )
            );
        layerParams["B_c"]["deriv"] = Matrix2d<double>(
            layerParams["B_c"]["deriv"]
                .addition(
                    dCBarInter.axisSum(0).get()
                    )
            );
        // вычисление производной по входному затвору 'output gate'
        // и производной его промежуточного значения
        Matrix2d<double> dI(
            dCOut.simplifiedMult(_forwardPassValues["C_bar"])
            );
        Matrix2d<double> dIInter(
            dI.simplifiedMult(
                  ActivationFunctions<double>
                  ::dsigmoid(_forwardPassValues["i_inter"]).get())
            );
        // обновление производных слоя для входного затвора(шлюза)
        layerParams["W_i"]["deriv"] = Matrix2d<double>(
            layerParams["W_i"]["deriv"]
                .addition(
                    _forwardPassValues["Z"]
                        ->transposition()
                        ->multiplication(&dIInter)
                        .get()
                    )
            );
        layerParams["B_i"]["deriv"] = Matrix2d<double>(
            layerParams["B_i"]["deriv"]
                .addition(
                    dIInter.axisSum(0).get()
                    )
            );
        // вычисление производной по затвору забывания 'forget gate'
        // и производной его промежуточного значения
        Matrix2d<double> dF(
            dCOut.simplifiedMult(_forwardPassValues["C_in"])
            );
        Matrix2d<double> dFInter(
            dF.simplifiedMult(
                  ActivationFunctions<double>
                  ::dsigmoid(_forwardPassValues["f_inter"]).get())
            );
        // обновление производных слоя для затвора(шлюза) забывания
        layerParams["W_f"]["deriv"] = Matrix2d<double>(
            layerParams["W_f"]["deriv"]
                .addition(
                    _forwardPassValues["Z"]
                        ->transposition()
                        ->multiplication(&dFInter)
                        .get()
                    )
            );
        layerParams["B_f"]["deriv"] = Matrix2d<double>(
            layerParams["B_f"]["deriv"]
                .addition(
                    dFInter.axisSum(0).get()
                    )
            );
        // вычисление заключительной производной по содержанию
        Matrix2d<double> dZOperandF(
            dFInter.multiplication(layerParams["W_f"]["value"]
                                       .transposition().get())
            );
        Matrix2d<double> dZOperandI(
            dIInter.multiplication(layerParams["W_i"]["value"]
                                       .transposition().get())
            );
        Matrix2d<double> dZOperandCBar(
            dCBarInter.multiplication(layerParams["W_c"]["value"]
                                          .transposition().get())
            );
        Matrix2d<double> dZOperandO(
            dOInter.multiplication(layerParams["W_o"]["value"]
                                       .transposition().get())
            );
        Matrix2d<double> dZ(
            dZOperandF
                .addition(&dZOperandI)
                ->addition(&dZOperandCBar)
                ->addition(&dZOperandO)
            );
        // получение производных исходного входа, скрытого состояния
        // и внутреннего состояния ячейки для передачи их на предыдущий уровень
        Matrix2d<double> dXPrev(
            dZ.slice(vector<int>{-1,-1,-1,_forwardPassValues["X_in"]->sizes()[1]})
            );
        Matrix2d<double> dHPrev(
            dZ.slice(vector<int>{-1,-1,_forwardPassValues["X_in"]->sizes()[1],-1})
            );
        Matrix2d<double> dCPrev(
            _forwardPassValues["f"]->simplifiedMult(&dCOut)
            );
        // подчищаем память
        cleanUp();
        // формируем и возвращаем ответ
        QMap<QString, Matrix2d<double>> result;
        result.insert("dX_prev", dXPrev);
        result.insert("dH_prev", dHPrev);
        result.insert("dC_prev", dCPrev);
        return result;
    } catch (const MatrixException &e) {
        throw NeuralNetworkException(
            QString("\nNeural network node exception \n[%1]<-[%2]\n")
                .arg("Error in backward pass", e.what())
            );
    }
}
