#ifndef DISTRIBUTOR_H
#define DISTRIBUTOR_H

///
/// \brief The Distributor class
/// стандартный распределитель случайностей
/// / данный класс является синглтоном /
class Distributor
{
private:
    // основное поле синглтона
    static Distributor *distributor;

private:
    Distributor();
    ~Distributor();

public:
    ///
    /// \brief instance получение текущего единственного
    /// экземпляра распределителя случайностей
    /// \return текущий единственный экземпляр распределителя
    static Distributor *instance();

};

#endif // DISTRIBUTOR_H
