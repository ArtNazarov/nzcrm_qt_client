#include "taskmodel.h"

TaskModel::TaskModel()
{
    fields.id=0;
    fields.dplan="1917-11-11";
    fields.dstart="1917-11-11";
    fields.days="10";
    fields.description="NO DESCRIPTION";
    fields.report="NO REPORT";
    fields.manager_id=0;
    fields.client_id=0;
    fields.task_type="NO TASK TYPE";
    fields.status="NO STATUS";
    fields.price=0;
}

void TaskModel::insert(QSqlDatabase db)
{
    QTextStream out(stdout);
    QString res;
    QSqlQuery* query_max_id = new QSqlQuery(db);
    int id = 1;

    if ( query_max_id->exec("SELECT max(id) FROM tasks LIMIT 1"))
    {
        query_max_id->first();
        id = 1 + query_max_id->value(0).toInt();
    }
    delete query_max_id;

    out << "New id "  << id << Qt::endl;

    fields.id = id;

    // check fields
    if (!validateFields()){
        outFields();
        out << "Something wrong with data " << Qt::endl;
    }
    else
    {
    out << "Validation - ok " << Qt::endl;
    outFields();
    QSqlQuery* query = new QSqlQuery(db);




    query->prepare(
                "INSERT INTO tasks ( "
                "id, dplan,dstart,days,description,report,manager_id,client_id, "
                "task_type, status, price"
                " ) "
                "VALUES ( "
                ":id, :dplan, :dstart, :days, :description, :report, :manager_id, :client_id, "
                ":task_type, :status, :price"
                " ) "

                );

   query->bindValue(":id", fields.id);
   query->bindValue(":dplan", fields.dplan);
   query->bindValue(":dstart", fields.dstart);
   query->bindValue(":days", fields.days);
   query->bindValue(":description", fields.description);
   query->bindValue(":report", fields.report);
   query->bindValue(":manager_id", fields.manager_id);
   query->bindValue(":client_id", fields.client_id);
   query->bindValue(":task_type", fields.task_type);
   query->bindValue(":status", fields.status);
   query->bindValue(":price", fields.price);


    db.transaction();
    out << query->exec();
    db.commit();

    out << query->lastQuery();
    out << db.lastError().text();

    delete query;
    };
}

void TaskModel::modelToRecord(QSqlRecord mr)
{

}

void TaskModel::recordToModel(QSqlRecord mr)
{
    mr.setValue("id", this->fields.id);
    mr.setValue("dplan", fields.dplan);
    mr.setValue("dstart", fields.dstart);
    mr.setValue("days", fields.days);
    mr.setValue("description", fields.description);
    mr.setValue("report", fields.report);
    mr.setValue("manager_id", fields.manager_id);
    mr.setValue("client_id", fields.client_id);
    mr.setValue("task_type", fields.task_type);
    mr.setValue("status", fields.status);
    mr.setValue("price", fields.price);
}

bool TaskModel::validateFields()
{
 bool b = true;
 b &= (fields.dplan!="");
 b &= (fields.dstart!="");
 b &= (fields.days!="");
 b &= (fields.description!="");
 b &= (fields.report!="");
 b &= (fields.task_type!="");
 b &= (fields.status!="");
 return b;
}

void TaskModel::outFields()
{
    QTextStream out(stdout);
    out << "id " << this->fields.id << Qt::endl;
    out << "dplan " << fields.dplan << Qt::endl;
    out << "dstart " << fields.dstart << Qt::endl;
    out << "days " << fields.days << Qt::endl;
    out << "description " << fields.description << Qt::endl;
    out << "report " << fields.report << Qt::endl;
    out << "manager_id " << fields.manager_id << Qt::endl;
    out << "client_id " << fields.client_id << Qt::endl;
    out << "task_type " << fields.task_type << Qt::endl;
    out << "status " << fields.status << Qt::endl;
    out << "price " << fields.price << Qt::endl;
}
