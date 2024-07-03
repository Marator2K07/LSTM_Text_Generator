#include "mainwindow.h"
#include "ui_form.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
