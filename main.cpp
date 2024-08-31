#include <QApplication>
#include <QListView>
#include <QStringListModel>

#include "pageModels/pagemodel.h"
#include "modeltraininggroupbox.h"
#include "newmodelgroupbox.h"
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

    PageModel pageModel;
    pageModel.show();

    NewModelGroupBox newModelSand;
    newModelSand.show();

    ModelTrainingGroupBox modelTraining;
    modelTraining.show();

    return a.exec();
}
