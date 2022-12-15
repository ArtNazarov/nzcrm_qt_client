#ifndef FADDMANAGER_H
#define FADDMANAGER_H

#include <QDialog>
#include "managermodel.h"

namespace Ui {
class fAddManager;
}

class fAddManager : public QDialog
{
    Q_OBJECT

public:
    explicit fAddManager(QWidget *parent = nullptr);
    ~fAddManager();
    ManagerRecord getModelRecord();

private:
    Ui::fAddManager *ui;
};

#endif // FADDMANAGER_H
