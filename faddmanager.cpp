#include "faddmanager.h"
#include "ui_faddmanager.h"
#include "managermodel.h"

fAddManager::fAddManager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::fAddManager)
{
    ui->setupUi(this);
}

fAddManager::~fAddManager()
{
    delete ui;
}

ManagerRecord fAddManager::getModelRecord()
{
    ManagerRecord r;


    r.adr = ui->leAddress->text();
    r.birthday = ui->leBirthday->text();
    r.email = ui->leEmail->text();
    r.inn = ui->leInn->text();
    r.pass = ui->lePassport->text();
    r.percent = ui->lePercent->text();
    r.phone = ui->lePhone->text();
    r.wday = ui->leDateEmp->text();
    r.name = ui->leName->text();

    return r;
}
