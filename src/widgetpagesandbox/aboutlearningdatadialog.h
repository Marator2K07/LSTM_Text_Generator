#ifndef ABOUTLEARNINGDATADIALOG_H
#define ABOUTLEARNINGDATADIALOG_H

#include <QMessageBox>
#include <QTextStream>
#include <QDialog>
#include <QFile>

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

public slots:
    ///
    /// \brief preloadData предзагрузка
    /// необходимых данных при возможности
    void preloadData();
    ///
    /// \brief updateLearningDataPath обновление пути обучающих данных
    /// \param path новый путь для обновления
    void updateLearningDataPath(const QString &path);

};

#endif // ABOUTLEARNINGDATADIALOG_H
