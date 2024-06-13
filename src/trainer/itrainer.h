#ifndef ITRAINER_H
#define ITRAINER_H

///
/// \brief The ITrainer interface
/// определение функционала тренера модели
class ITrainer
{
public:
    ///
    /// \brief train тренирует модель генерации текста
    /// \param iterCount количество шагов обучения
    /// \param textSample флаг наличия вывода сгенерированного
    /// текста, используя последнюю версию модели
    void train(int iterCount, bool textSample = false);
};

#endif // ITRAINER_H
