#ifndef MANAGERMODEL_H
#define MANAGERMODEL_H

#include <QSqlQuery>
#include <QTableView>
#include <QSqlTableModel>
#include <QDebug>
#include <QSqlError>
#include <QMessageBox>
#include <QSqlRecord>


struct ManagerRecord {
    QString adr;
    QString birthday;
    QString email;
    int id;
    QString inn;
    int manager_group;
    QString name;
    QString pass;
    QString percent;
    QString phone;
    QString wday;
};


class ManagerModel
{
public:

    QSqlQuery query;
    ManagerRecord fields;

    ManagerModel();

    void insert(QSqlDatabase db);
    void modelToRecord(QSqlRecord mr);
    void recordToModel(QSqlRecord mr);
    bool validateFields();
};

#endif // MANAGERMODEL_H
