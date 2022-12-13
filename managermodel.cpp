#include "managermodel.h"
#include <QTextStream>


ManagerModel::ManagerModel()
{
  fields.manager_group = 999;
  fields.id = 100;
  fields.wday = "1917-01-01";
  fields.birthday = "1917-01-01";
  fields.adr = "NO ADDRESS";
  fields.phone = "NO PHONE";
  fields.email = "NO EMAIL";
  fields.inn = "NO INN";
  fields.name = "NO NAME";
  fields.pass = "NO PASS";
  fields.percent = "0";
}

void ManagerModel::insert(QSqlDatabase db)
{
    QTextStream out(stdout);
    QString res;
    QSqlQuery* query_max_id = new QSqlQuery(db);
    int id = 1;

    if ( query_max_id->exec("SELECT max(id) FROM managers LIMIT 1"))
    {
        query_max_id->first();
        id = 1 + query_max_id->value(0).toInt();
    }
    delete query_max_id;

    out << "New id "  << id << Qt::endl;

    fields.id = id;

    // check fields
    if (!validateFields()){
        out << "Something wrong with data " << Qt::endl;
    }
    else
    {
    out << "Validation - ok " << Qt::endl;

    QSqlQuery* query = new QSqlQuery(db);

    query->prepare(
                  "INSERT INTO managers ( "
                  "adr, birthday, email, id, inn,"
                  "manager_group, name, pass, "
                  "percent, phone, wday  ) "
                  "VALUES ( "
                  ":adr, :birthday, :email, :id, :inn,"
                  ":manager_group, :name, :pass, "
                  ":percent, :phone, :wday )");

    query->bindValue(":adr", fields.adr);
    query->bindValue(":id", fields.id);
    query->bindValue(":birthday", fields.birthday);

    query->bindValue(":email", fields.email);
    query->bindValue(":inn", fields.inn);
    query->bindValue(":manager_group", fields.manager_group);

    query->bindValue(":name", fields.name);
    query->bindValue(":pass", fields.pass);
    query->bindValue(":percent", fields.percent);

    query->bindValue(":phone", fields.phone);
    query->bindValue(":wday", fields.wday);


    out << query->exec();
    delete query;
    };
}

void ManagerModel::modelToRecord(QSqlRecord mr)
{

mr.setValue("adr", this->fields.adr);
mr.setValue("birthday", fields.birthday);
mr.setValue("email", fields.email);
mr.setValue("id", fields.id);
mr.setValue("inn", fields.inn);
mr.setValue("manager_group", fields.manager_group);
mr.setValue("name", fields.name);
mr.setValue("pass", fields.pass);
mr.setValue("percent", fields.percent);
mr.setValue("phone", fields.phone);
mr.setValue("wday", fields.wday);
}

void ManagerModel::recordToModel(QSqlRecord mr)
{
    // TODO
}

bool ManagerModel::validateFields()
{
  bool b;

  b = (fields.adr != "");
  b &= (fields.birthday != "");
  b &= (fields.email != "");
  b &= (fields.inn != "");
  b &= (fields.birthday != "");
  b &= (fields.name != "");
  b &= (fields.pass != "");
  b &= (fields.percent != "");
  b &= (fields.phone != "");

  return b;

}
