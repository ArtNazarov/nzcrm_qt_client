#ifndef CLIENTMODEL_H
#define CLIENTMODEL_H

#include <QSqlQuery>
#include <QTableView>
#include <QSqlTableModel>
#include <QDebug>
#include <QSqlError>
#include <QMessageBox>
#include <QSqlRecord>

struct ClientRecord {
    int id;
    QString name;
    QString inn;
    QString kpp;
    QString uadr;
    QString fadr;
    QString rcv;
    QString phone;
    QString fax;
    QString director;
    QString glavbuh;
    QString email;
    QString site;
    QString source;
    QString status;
    int client_group;
    QString doc_num;
    QString doc_date;
    QString rs;
    QString bank;
    QString ks;
    QString bik;
};


class ClientModel
{
public:
    QSqlQuery query;
    ClientRecord fields;
    ClientModel();

    void insert(QSqlDatabase db);
    void modelToRecord(QSqlRecord mr);
    void recordToModel(QSqlRecord mr);
    bool validateFields();
    void outFields();
};

#endif // CLIENTMODEL_H
