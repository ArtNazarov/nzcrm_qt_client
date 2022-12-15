#ifndef FADDTASK_H
#define FADDTASK_H

#include <QDialog>
#include "taskmodel.h"

namespace Ui {
class fAddTask;
}

class fAddTask : public QDialog
{
    Q_OBJECT

public:
    explicit fAddTask(QWidget *parent = nullptr);
    ~fAddTask();

    TaskRecord getTask();



private:
    Ui::fAddTask *ui;
};

#endif // FADDTASK_H
