#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSqlQuery>
#include <QTableView>
#include <QSqlRelationalTableModel>
#include <QDebug>
#include <QSqlError>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{

    if (db.isOpen()) { db.close(); }

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
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setPort(3306);
    db.setUserName("test");
    db.setPassword("test_pass");
    db.setDatabaseName("laranotes");

    bool ok = db.open();
    if (!ok){

          _isValid = db.isValid();
          msg = "database not opened";
          lastError = db.lastError().text();
       }
    if (ok) {

      mdClients = new QSqlRelationalTableModel(this->parent(), db);
      mdClients->setTable("clients");
      mdClients->setEditStrategy(QSqlRelationalTableModel::OnFieldChange);
      mdClients->select();


      mdManagers = new QSqlRelationalTableModel(this->parent(), db);
      mdManagers->setTable("managers");
      mdManagers->setEditStrategy(QSqlRelationalTableModel::OnFieldChange);
      mdManagers->select();


      mdTasks = new QSqlRelationalTableModel(this->parent(), db);
      mdTasks->setTable("tasks");
      mdTasks->setEditStrategy(QSqlRelationalTableModel::OnFieldChange);
      mdTasks->select();


      ui->tvManagers->setModel(mdManagers);
      ui->tvManagers->show();

      ui->tvClients->setModel(mdClients);
      ui->tvClients->show();

      ui->tvTasks->setModel(mdTasks);
      ui->tvTasks->show();


   } else { qDebug() << "Error"; };
}

