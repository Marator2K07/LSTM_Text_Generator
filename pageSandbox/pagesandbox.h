#ifndef PAGESANDBOX_H
#define PAGESANDBOX_H

#include <QWidget>

///
/// \brief The WorkMode enum
/// определение режима работы виджета
enum class WorkMode {
    EXISTING_MODEL = 0,
    NEW_MODEL,
    NONE
};

namespace Ui {
class PageSandbox;
}

///
/// \brief The PageSandbox class
/// Виджет/страница создания новых моделей нейронной сети
/// и их тренировка,своего рода - песочница
class PageSandbox : public QWidget
{
    Q_OBJECT

private:
    Ui::PageSandbox *ui;
    WorkMode _currenWorkMode; // текущим режим работы виджета


public:
    explicit PageSandbox(QWidget *parent = nullptr);
    ~PageSandbox();

};

#endif // PAGESANDBOX_H
