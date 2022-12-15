#ifndef TASKMODEL_H
#define TASKMODEL_H

#include <QString>
#include <QSqlQuery>
#include <QTableView>
#include <QSqlTableModel>
#include <QDebug>
#include <QSqlError>
#include <QMessageBox>
#include <QSqlRecord>

struct TaskRecord {
    int id;
    QString dplan;
    QString dstart;
    QString days;
    QString description;
    QString report;
    int manager_id;
    int client_id;
    QString task_type;
    QString status;
    int price;
};

class TaskModel
{
public:
    QSqlQuery query;
    TaskRecord fields;

    TaskModel();

    void insert(QSqlDatabase db);
    void modelToRecord(QSqlRecord mr);
    void recordToModel(QSqlRecord mr);
    bool validateFields();
    void outFields();
};

#endif // TASKMODEL_H
