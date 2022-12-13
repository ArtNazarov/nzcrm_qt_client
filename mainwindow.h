#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlRelationalTableModel>
#include <QSqlDatabase>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    bool _isValid;
    QString msg;
    QString lastError;
    QSqlRelationalTableModel *mdClients;
    QSqlRelationalTableModel *mdManagers;
    QSqlRelationalTableModel *mdTasks;
    QSqlDatabase db;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_btnConnect_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
