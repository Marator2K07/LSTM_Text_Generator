#ifndef PAGESANDBOX_H
#define PAGESANDBOX_H

#include <QWidget>

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

public:
    explicit PageSandbox(QWidget *parent = nullptr);
    ~PageSandbox();

};

#endif // PAGESANDBOX_H
