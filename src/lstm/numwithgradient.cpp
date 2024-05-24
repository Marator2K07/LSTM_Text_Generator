#include "numwithgradient.h"

NumWithGradient::NumWithGradient(double num,
                                 vector<NumWithGradient *> depends_on,
                                 QString creation_op)
    : num_{num}
    , gradient_{0}
    , depends_on{depends_on}
    , creation_op{creation_op}
{
}

NumWithGradient NumWithGradient::operator+(Num *other)
{
    // сначала формируем список зависимостей    
    vector<NumWithGradient *> depends_on{this};
    NumWithGradient *otherNum = ensureNum(other);
    depends_on.push_back(otherNum);
    // и в итоге создаем новый обьект числа с градиентом
    return NumWithGradient(this->num() + otherNum->num(),
                           depends_on,
                           "add");
}

NumWithGradient NumWithGradient::operator*(Num *other)
{
    // сначала формируем список зависимостей
    vector<NumWithGradient *> depends_on{this};
    NumWithGradient *otherNum = ensureNum(other);
    depends_on.push_back(otherNum);
    // и в итоге создаем новый обьект числа с градиентом
    return NumWithGradient(this->num() * otherNum->num(),
                           depends_on,
                           "mul");
}

void NumWithGradient::backward(double backwardGradient)
{
    // в случае первичного вызова обратного прохода
    if (backwardGradient == 0) {
        gradient_ = 1;
    }
    // иначе идет накопление градиентов
    else {
        // причем если собственный градиент пока нулевой,
        // он становится = backwardGradient
        if (gradient_ == 0) {
            gradient_ = backwardGradient;
        }
        // иначе backwardGradient добавляется к
        // существующему градиенту
        else {
            gradient_ += backwardGradient;
        }
    }
    // в случае сложения назад отправляется gradient, так как
    // увеличение любого из этих элементов приведет к такому же
    // увеличению выходного значения
    if (creation_op == "add") {
        depends_on[0]->backward(gradient_);
        depends_on[1]->backward(gradient_);
    }    
    // в случае умножения, назад отправляются производные
    if (creation_op == "mul") {
        // по вервому элементу
        double derivativeOne = depends_on[1]->num() * this->gradient();
        depends_on[0]->backward(derivativeOne);
        // по второму элементу
        double derivativeTwo = depends_on[0]->num() * this->gradient();
        depends_on[1]->backward(derivativeTwo);
    }
}

double NumWithGradient::gradient()
{
    return gradient_;
}

NumWithGradient *NumWithGradient::ensureNum(Num *num)
{
    switch (num->type()) {
    case Num_Type::Simple:
        return new NumWithGradient(num->num());
    case Num_Type::WithGradient:
        return (NumWithGradient*)num;
    default:
        return new NumWithGradient(1);
    }
}

double NumWithGradient::num() const
{
    return num_;
}

Num_Type NumWithGradient::type() const
{
    return Num_Type::WithGradient;
}
