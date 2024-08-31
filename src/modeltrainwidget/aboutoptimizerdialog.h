#ifndef ABOUTOPTIMIZERDIALOG_H
#define ABOUTOPTIMIZERDIALOG_H

#include <QDialog>

namespace Ui {
class AboutOptimizerDialog;
}

///
/// \brief The AboutOptimizerDialog class
/// вспомогательный виджет с основной информацией
/// о доступных оптимизаторах и его выборе
class AboutOptimizerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AboutOptimizerDialog(QWidget *parent = nullptr);
    ~AboutOptimizerDialog();

private:
    Ui::AboutOptimizerDialog *ui;
};

#endif // ABOUTOPTIMIZERDIALOG_H
