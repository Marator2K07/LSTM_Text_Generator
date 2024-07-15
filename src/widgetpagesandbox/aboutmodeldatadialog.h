#ifndef ABOUTMODELDATADIALOG_H
#define ABOUTMODELDATADIALOG_H

#include <QDialog>

namespace Ui {
class AboutModelDataDialog;
}

///
/// \brief The AboutModelDataDialog class
/// вспомогательный виджет с основной
/// информацией об основных модельных данных
class AboutModelDataDialog : public QDialog
{
    Q_OBJECT

private:
    Ui::AboutModelDataDialog *ui;

public:
    explicit AboutModelDataDialog(QWidget *parent = nullptr);
    ~AboutModelDataDialog();

};

#endif // ABOUTMODELDATADIALOG_H
