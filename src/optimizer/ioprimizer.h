#ifndef IOPRIMIZER_H
#define IOPRIMIZER_H

///
/// \brief The IOprimizer interface
/// определение функционала оптимизатора модели
/// нейронной сети (обновление параметров сети при обучении)
class IOprimizer
{
private:
    ///
    virtual void updateRule() = 0;

public:
    ///
    /// \brief step шаг прохода по параметрам
    /// модели сети для их обновления
    virtual void step() = 0;
};

#endif // IOPRIMIZER_H
