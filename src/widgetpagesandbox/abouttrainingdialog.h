#ifndef ABOUTTRAININGDIALOG_H
#define ABOUTTRAININGDIALOG_H

#include <QDialog>

namespace Ui {
class AboutTrainingDialog;
}

///
/// \brief The AboutTrainingDialog class
/// вспомогательный виджет с основной
/// информацией о процессе обучения модели
class AboutTrainingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AboutTrainingDialog(QWidget *parent = nullptr);
    ~AboutTrainingDialog();

private:
    Ui::AboutTrainingDialog *ui;
};

#endif // ABOUTTRAININGDIALOG_H
