#include "faddclient.h"
#include "ui_faddclient.h"
#include "clientmodel.h"


fAddClient::fAddClient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::fAddClient)
{


    ui->setupUi(this);
}

fAddClient::~fAddClient()
{
    delete ui;
}

ClientRecord fAddClient::getClient()
{
    ClientRecord r;
    r.name=ui->leName->text();
    r.inn=ui->leInn->text();
    r.kpp=ui->leKpp->text();
    r.uadr=ui->leUadr->text();

        r.fadr = ui->leFadr->text();
        r.rcv = ui->leRcv->text();
        r.phone = ui->lePhone->text();
        r.fax = ui->leFax->text();
        r.director = ui->leDirector->text();
        r.glavbuh = ui->leGlavBuh->text();
        r.email = ui->leEmail->text();
        r.site = ui->leSite->text();
        r.source = ui->leSource->text();
        r.status = ui->leStatus->text();
        QString cg = ui->leClient_Group->text();
        int n = cg.toInt();
        r.client_group=n;
        r.doc_num = ui->leDoc_Num->text();
        r.doc_date = ui->leDoc_Date->text();
        r.rs = ui->leRs->text();
        r.bank = ui->leBank->text();
        r.ks = ui->leKs->text();
        r.bik = ui->leBik->text();

    return r;
}
