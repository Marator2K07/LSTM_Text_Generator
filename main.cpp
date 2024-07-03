#include <QApplication>

#include "pageModels/pagemodel.h"
#include "adagrad.h"
#include "sgd.h"
#include "lstmlayer.h"
#include "lstmmodel.h"
#include "softmaxcrossentropyloss.h"
#include "consistenttrainer.h"
#include "charasvectorembedding.h"
#include "charasvectorembedding.cpp"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    PageModel window;
    window.show();

    return a.exec();
}
