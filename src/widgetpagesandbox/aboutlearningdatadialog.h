#ifndef ABOUTLEARNINGDATADIALOG_H
#define ABOUTLEARNINGDATADIALOG_H

#include <QDialog>

namespace Ui {
class AboutLearningDataDialog;
}

///
/// \brief The AboutLearningDataDialog class
/// вспомогательный виджет для просмотра и анализа
/// текущего выбранного обучающего текста
class AboutLearningDataDialog : public QDialog
{
    Q_OBJECT

private:
    Ui::AboutLearningDataDialog *ui;

public:
    explicit AboutLearningDataDialog(QWidget *parent = nullptr);
    ~AboutLearningDataDialog();

};

#endif // ABOUTLEARNINGDATADIALOG_H
