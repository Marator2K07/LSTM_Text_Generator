#include <QApplication>
#include <QListView>
#include <QStringListModel>

#include "lstmgeneratormainwindow.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LSTMGeneratorMainWindow mainWindow;
    mainWindow.show();

    return a.exec();
}
