#ifndef ITEXTGENERATOR_H
#define ITEXTGENERATOR_H

#include "matrix2d.h"

using namespace std;

///
/// \brief The ITextGenerator interface
/// определение функциональности генератора текста
class ITextGenerator
{
public:
    ///
    /// \brief genSymbol предсказание символа на основе контекста
    /// \param context контекст текста (индексы символов в строке)
    /// \return предсказанный символ
    virtual QChar genSymbol(const vector<int> context) = 0;
};

#endif // ITEXTGENERATOR_H
