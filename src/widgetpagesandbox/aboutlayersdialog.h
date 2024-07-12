#ifndef ABOUTLAYERSDIALOG_H
#define ABOUTLAYERSDIALOG_H

#include <QDialog>

namespace Ui {
class AboutLayersDialog;
}

///
/// \brief The AboutLayersDialog class
/// вспомогательный виджет с основной
/// информацией о слоях нейронной сети
class AboutLayersDialog : public QDialog
{
    Q_OBJECT

private:
    Ui::AboutLayersDialog *ui;

public:
    explicit AboutLayersDialog(QWidget *parent = nullptr);
    ~AboutLayersDialog();

};

#endif // ABOUTLAYERSDIALOG_H
