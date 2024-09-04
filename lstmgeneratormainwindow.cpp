#include "lstmgeneratormainwindow.h"
#include "ui_lstmgeneratormainwindow.h"

LSTMGeneratorMainWindow::LSTMGeneratorMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LSTMGeneratorMainWindow)
{
    ui->setupUi(this);
}

LSTMGeneratorMainWindow::~LSTMGeneratorMainWindow()
{
    delete ui;
}
