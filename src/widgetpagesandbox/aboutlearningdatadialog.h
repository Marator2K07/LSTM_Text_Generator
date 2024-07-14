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
    QString _pathLearningData; // путь до подгружаемых данных
    QString _learningData; // подгружаемые обучающие данные

public:
    explicit AboutLearningDataDialog(QWidget *parent = nullptr);
    ~AboutLearningDataDialog();

};

#endif // ABOUTLEARNINGDATADIALOG_H
