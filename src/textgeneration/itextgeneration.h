#ifndef ITEXTGENERATION_H
#define ITEXTGENERATION_H

#include "matrix2d.h"

using namespace std;

///
/// \brief The ITextGeneration interface
/// определение функциональности генератора текста
class ITextGeneration
{
public:
    ///
    /// \brief predictSymbol предсказание символа на основе контекста
    /// \param context контекст текста (первые символы/слова в тексте)
    /// \return предсказанный символ
    virtual QChar predictSymbol(const Matrix2d<double> context) = 0;
};

#endif // ITEXTGENERATION_H
