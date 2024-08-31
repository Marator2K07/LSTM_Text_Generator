#ifndef ABOUTCURMODELSTATEDIALOG_H
#define ABOUTCURMODELSTATEDIALOG_H

#include <QDialog>

namespace Ui {
class AboutCurModelStateDialog;
}

///
/// \brief The AboutCurModelStateDialog class
/// вспомогательный виджет с основной
/// информацией о степени обученности модели
class AboutCurModelStateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AboutCurModelStateDialog(QWidget *parent = nullptr);
    ~AboutCurModelStateDialog();

private:
    Ui::AboutCurModelStateDialog *ui;
};

#endif // ABOUTCURMODELSTATEDIALOG_H
