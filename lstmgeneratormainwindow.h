#ifndef LSTMGENERATORMAINWINDOW_H
#define LSTMGENERATORMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class LSTMGeneratorMainWindow;
}

///
/// \brief The LSTMGeneratorMainWindow class
/// основа визуального интерфейса приложения LSTM генератора
class LSTMGeneratorMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LSTMGeneratorMainWindow(QWidget *parent = nullptr);
    ~LSTMGeneratorMainWindow();

private:
    Ui::LSTMGeneratorMainWindow *ui;
};

#endif // LSTMGENERATORMAINWINDOW_H
