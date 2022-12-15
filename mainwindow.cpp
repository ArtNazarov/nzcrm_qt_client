#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSqlQuery>
#include <QTableView>
#include <QSqlTableModel>
#include <QDebug>
#include <QSqlError>
#include <QMessageBox>
#include <QSqlRecord>
#include "managermodel.h"
#include "clientmodel.h"
#include "faddmanager.h"
#include "faddclient.h"

void MainWindow::doConnection(QString host, int port, QString database_name, QString username, QString password)
{




    if (""==host) return;
    if (""==database_name) return;
    if (""==username) return;
    if (""==password) return;

    db = QSqlDatabase::addDatabase("QMYSQL");


    db.setHostName(host);
    db.setPort(port);
    db.setUserName(username);
    db.setPassword(password);
    db.setDatabaseName(database_name);

    bool ok = db.open();
    if (!ok){
        msg = "database not opened";
        lastError = db.lastError().text();
        showMessage(lastError);
        }
    if (ok) {


       initialView(  TableList::MANAGERS );
       initialView( TableList::CLIENTS );
       initialView( TableList::TASKS );



   } else {
        msg = "error in button connect";
        lastError = db.lastError().text();
        showMessage(lastError);

    };
    this->uiElementsWatch();
}

void MainWindow::initialView(TableList choice)
{
     QString tableName;
     QSqlTableModel* md = new QSqlTableModel(this->parent(), db);
     QTableView* tv;
    switch (choice){

    case TableList::MANAGERS : {
        tableName = "managers";
        this->mdManagers = md;
        tv = this->ui->tvManagers;
        break;
    }
    case TableList::CLIENTS : {
        tableName = "clients";
        this->mdClients = md;
        tv = this->ui->tvClients;
        break;
    }
    case TableList::TASKS : {
        tableName = "tasks";
        this->mdTasks = md;
        tv = this->ui->tvTasks;
        break;
    };

    };

    md->setTable(tableName);
    md->setEditStrategy(QSqlTableModel::OnFieldChange);
    md->select();
    tv->setModel(md);
    tv->show();


}

void MainWindow::removeRowFrom(TableList choice)
{


    if (!db.isOpen())
    {
        showMessage("Database must be open");
        return;
    };



    PairedMV MV = this->getByEnum(choice);



    if ((MV.md==0)||(MV.tv==0)) {
        showMessage("Error in removeRowFrom 103");
        return;
    }

    if (!MV.tv->selectionModel()->hasSelection()){
        showMessage("Not selected any row");
        return;
    }

    QModelIndexList selection = MV.tv->selectionModel()->selectedRows();


    for(int i=0; i< selection.count(); i++)
    {
        QModelIndex index = selection.at(i);
        showMessage ( QString::number ( index.row() ) );
        //showMessage(MV.md->tableName());
        MV.md->removeRow( index.row()  );
     }

    MV.tv->clearSelection();
    MV.md->submit();
    MV.md->select();



}

void MainWindow::showMessage(QString msg)
{
    QMessageBox* msgBox = new QMessageBox();
    msgBox->setWindowTitle("Info");
    msgBox->setText(msg);
    msgBox->setIcon(QMessageBox::Information);
    msgBox->exec();
    delete msgBox;
}

PairedMV MainWindow::getByEnum(TableList t)
{
    PairedMV Result;
    switch (t){

    case TableList::MANAGERS : {
        Result.md = this->mdManagers;
        Result.tv = this->ui->tvManagers;
        break;
    }
    case TableList::CLIENTS : {
        Result.md = this->mdClients;
        Result.tv = this->ui->tvClients;
        break;
    }
    case TableList::TASKS : {
        Result.md = this->mdTasks;
        Result.tv = this->ui->tvTasks;
        break;
    };

    };
    return Result;
}

void MainWindow::uiElementsWatch()
{
      ui->btnConnect->setEnabled(!db.isOpen());
      ui->btnDisconnect->setEnabled(db.isOpen());

      ui->tvManagers->setEnabled( db.isOpen() );
      ui->tvClients->setEnabled( db.isOpen() );
      ui->tvTasks->setEnabled( db.isOpen() );

      ui->btnRemoveFromTasks->setEnabled(db.isOpen());
      ui->btnDeleteFromClients->setEnabled( db.isOpen());
      ui->btnDeleteManager->setEnabled(db.isOpen());
      ui->btnAddManager->setEnabled(db.isOpen());
      ui->btnAddClient->setEnabled(db.isOpen());


      QString text;

      text = (!db.isOpen()) ?  "disconnected" : "connected";

      ui->lbStatus->setText(text);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{


    ui->setupUi(this);
    this->uiElementsWatch();
  }

MainWindow::~MainWindow()
{

        if (db.isOpen()) { db.close(); };


    delete mdClients;
    delete mdManagers;
    delete mdTasks;

    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
}


void MainWindow::on_btnConnect_clicked()
{
   int port = ui->lePortNum->text().toInt();
   doConnection(

    ui->leHost->text(),
    port,
    ui->leDatabase->text(),
    ui->leUsername->text(),
    ui->lePassword->text()

               );
 if (db.isOpen()){
     ui->lbStatus->setText("connected");
 }
}


void MainWindow::on_btnDeleteManager_clicked()
{

    removeRowFrom(TableList::MANAGERS);


}


void MainWindow::on_btnDeleteFromClients_clicked()
{
   //showMessage("remove from clients");
    removeRowFrom(TableList::CLIENTS);

}


void MainWindow::on_btnRemoveFromTasks_clicked()
{
   //  showMessage("remove from tasks");
     removeRowFrom(TableList::TASKS);
}


void MainWindow::on_btnDisconnect_clicked()
{
    if (db.isOpen()){
        db.close();
        this->uiElementsWatch();
    }
}


void MainWindow::on_btnAddManager_clicked()
{
    fAddManager *dialog = new fAddManager();
    dialog->show();
    if ( dialog->exec() == QDialog::Accepted ){
        PairedMV MV = getByEnum(TableList::MANAGERS);
        ManagerModel* mm = new ManagerModel();
        mm->fields = dialog->getModelRecord();
        mm->insert(db);
        delete mm;
        MV.md->select();
    }
    else
    {
        showMessage("not added because canceled");
    };




}


void MainWindow::on_btnAddClient_clicked()
{
    fAddClient *dialog = new fAddClient();
    dialog->show();
    if ( dialog->exec() == QDialog::Accepted ){
        PairedMV MV = getByEnum(TableList::CLIENTS);
        ClientModel* cm = new ClientModel();
        cm->fields = dialog->getClient();
        cm->insert(db);
        delete cm;
        MV.md->select();
    }
    else
    {
        showMessage("not added because canceled");
    };

}

