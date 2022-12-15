#include "faddtask.h"
#include "ui_faddtask.h"
#include "taskmodel.h"

fAddTask::fAddTask(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::fAddTask)
{
    ui->setupUi(this);
}

fAddTask::~fAddTask()
{
    delete ui;
}

TaskRecord fAddTask::getTask()
{
    TaskRecord r;
    r.task_type = ui->leTaskType->text();
    r.client_id = ui->leClient_id->text().toInt();
    r.days = ui->leDays->text();
    r.description = ui->leDescription->text();
    r.dplan = ui->leDplan->text();
    r.dstart = ui->leDstart->text();
    r.manager_id = ui->leManager_id->text().toInt();
    r.price = ui->leSum->text().toInt();
    r.report = ui->teReport->toPlainText();
    r.status = ui->leStatus->text();

     return r;
}
