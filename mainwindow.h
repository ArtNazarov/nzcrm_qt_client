#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qtableview.h"
#include <QMainWindow>
#include <QSqlTableModel>
#include <QSqlDatabase>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct PairedMV {
    QSqlTableModel* md;
    QTableView* tv;
};

enum TableList{
    CLIENTS, MANAGERS, TASKS
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    bool _isValid;
    QString msg;
    QString lastError;
    QSqlTableModel *mdClients;
    QSqlTableModel *mdManagers;
    QSqlTableModel *mdTasks;
    QSqlDatabase db;

    void doConnection(QString host, int port, QString database_name, QString username, QString password);
    void initialView( TableList choice);
    void removeRowFrom(TableList choice);
    void showMessage(QString msg);
    PairedMV getByEnum(TableList t);

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_btnConnect_clicked();

    void on_btnDeleteManager_clicked();

    void on_btnDeleteFromClients_clicked();

    void on_btnRemoveFromTasks_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
