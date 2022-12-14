#include "clientmodel.h"
#include <QTextStream>


ClientModel::ClientModel()
{
    fields.id=0;
    fields.name="NO NAME";
    fields.inn="NO INN";
    fields.kpp="NO KPP";
    fields.uadr="NO UADR";
    fields.fadr="NO FADR";
    fields.rcv="NO RCV";
    fields.phone="NO PHONE";
    fields.fax="NO FAX";
    fields.director="NO DIRECTOR";
    fields.glavbuh="NO GLAVBUH";
    fields.email="NO EMAIL";
    fields.site="NO SITE";
    fields.source="NO SOURCE";
    fields.status="NO STATUS";
    fields.client_group=0;
    fields.doc_num="NO DOC_NUM";
    fields.doc_date="1917-01-01";
    fields.rs="NO RS";
    fields.bank="NO BANK";
    fields.ks="NO KS";
    fields.bik="NO BIK";
}

void ClientModel::insert(QSqlDatabase db)
{
    QTextStream out(stdout);
    QString res;
    QSqlQuery* query_max_id = new QSqlQuery(db);
    int id = 1;

    if ( query_max_id->exec("SELECT max(id) FROM clients LIMIT 1"))
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
    outFields();
    QSqlQuery* query = new QSqlQuery(db);

    query->prepare(
                "INSERT INTO clients ( "
                "id, name, inn, kpp, uadr, fadr, rcv, phone, fax, "
                "director, glavbuh, email, site, source, status, client_group, doc_num, doc_date, rs, bank, ks, bik "
                " ) "
                "VALUES ( "
                ":id, :name, :inn, :kpp, :uadr, :fadr, :rcv, :phone, :fax, "
                ":director, :glavbuh, :email, :site, :source, :status, :client_group, :doc_num, :doc_date, :rs, :bank, :ks, :bik "
                " ) "

                );

    query->bindValue(":id", fields.id);
    query->bindValue(":name", fields.name);
    query->bindValue(":inn", fields.inn);
    query->bindValue(":kpp", fields.kpp);
    query->bindValue(":uadr", fields.uadr);
    query->bindValue(":fadr", fields.fadr);
    query->bindValue(":rcv", fields.rcv);
    query->bindValue(":phone",fields.phone);
    query->bindValue(":fax", fields.fax);
    query->bindValue(":director", fields.director);
    query->bindValue(":glavbuh", fields.glavbuh);
    query->bindValue(":email", fields.email);
    query->bindValue(":site", fields.site);
    query->bindValue(":source",fields.source);
    query->bindValue(":status",fields.status);
    query->bindValue(":client_group",fields.client_group);
    query->bindValue(":doc_num",fields.doc_num);
    query->bindValue(":doc_date",fields.doc_date);
    query->bindValue(":rs",fields.rs);
    query->bindValue(":bank",fields.bank);
    query->bindValue(":ks",fields.ks);
    query->bindValue(":bik",fields.bik);

    db.transaction();
    out << query->exec();
    db.commit();

    out << query->lastQuery();
    out << db.lastError().text();

    delete query;
    };
}

void ClientModel::modelToRecord(QSqlRecord mr)
{
 // TODO mr
}

void ClientModel::recordToModel(QSqlRecord mr)
{
    mr.setValue("id", this->fields.id);
    mr.setValue("name", this->fields.name);
    mr.setValue("inn", this->fields.inn);
    mr.setValue("kpp", this->fields.kpp);
    mr.setValue("uadr", this->fields.uadr);
    mr.setValue("fadr", this->fields.fadr);
    mr.setValue("rcv", this->fields.rcv);
    mr.setValue("phone",this->fields.phone);
    mr.setValue("fax", this->fields.fax);
    mr.setValue("director", this->fields.director);
    mr.setValue("glavbuh", this->fields.glavbuh);
    mr.setValue("email", this->fields.email);
    mr.setValue("site", this->fields.site);
    mr.setValue("source",this->fields.source);
    mr.setValue("status",this->fields.status);
    mr.setValue("client_group",this->fields.client_group);
    mr.setValue("doc_num",this->fields.doc_num);
    mr.setValue("doc_date",this->fields.doc_date);
    mr.setValue("rs",this->fields.rs);
    mr.setValue("bank",this->fields.bank);
    mr.setValue("ks",this->fields.ks);
    mr.setValue("bik",this->fields.bik);

}

bool ClientModel::validateFields()
{
    bool b = true;

    b &= (this->fields.name!="");
    b &= (this->fields.inn!="");
    b &= (this->fields.kpp!="");
    b &= (this->fields.uadr!="");
    b &= (this->fields.fadr!="");
    b &= (this->fields.rcv!="");
    b &= (this->fields.phone!="");
    b &= (this->fields.fax!="");
    b &= (this->fields.director!="");
    b &= (this->fields.glavbuh!="");
    b &= (this->fields.email!="");
    b &= (this->fields.site!="");
    b &= (this->fields.source!="");
    b &= (this->fields.status!="");

    b &= (this->fields.doc_num!="");
    b &= (this->fields.doc_date!="");
    b &= (this->fields.rs!="");
    b &= (this->fields.bank!="");
    b &= (this->fields.ks!="");
    b &= (this->fields.bik!="");

    return b;
}

void ClientModel::outFields()
{
    QTextStream out(stdout);
     out << "id" << fields.id << Qt::endl;
     out << "name" << fields.name << Qt::endl;
     out << "inn" << fields.inn << Qt::endl;
    out << "kpp" << fields.kpp << Qt::endl;
    out << "uadr" <<  fields.uadr<< Qt::endl;
    out << "fadr" <<  fields.fadr<< Qt::endl;
    out << "rcv" <<  fields.rcv<< Qt::endl;
    out << "phone" << fields.phone<< Qt::endl;
    out << "fax" <<  fields.fax<< Qt::endl;
    out << "director" <<  fields.director<< Qt::endl;
    out << "glavbuh" <<  fields.glavbuh<< Qt::endl;
    out << "email" <<  fields.email<< Qt::endl;
    out << "site" <<  fields.site<< Qt::endl;
    out << "source" << fields.source<< Qt::endl;
    out << "status" << fields.status<< Qt::endl;
    out << "client_group"<< fields.client_group<< Qt::endl;
    out << "doc_num" << fields.doc_num<< Qt::endl;
    out << "doc_date" << fields.doc_date<< Qt::endl;
    out << "rs" << fields.rs<< Qt::endl;
    out << "bank" << fields.bank<< Qt::endl;
    out << "ks" << fields.ks<< Qt::endl;
    out << "bik" << fields.bik<< Qt::endl;
}
