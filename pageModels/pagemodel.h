#ifndef PAGEMODEL_H
#define PAGEMODEL_H

#include <QWidget>

namespace Ui {
class PageModel;
}

class PageModel : public QWidget
{
    Q_OBJECT

private:
    Ui::PageModel *ui;

public:
    explicit PageModel(QWidget *parent = nullptr);
    ~PageModel();

};

#endif // PAGEMODEL_H
