#ifndef FADDCLIENT_H
#define FADDCLIENT_H

#include <QDialog>
#include "clientmodel.h"

namespace Ui {
class fAddClient;
}

class fAddClient : public QDialog
{
    Q_OBJECT

public:
    explicit fAddClient(QWidget *parent = nullptr);
    ~fAddClient();

    ClientRecord getClient();

private:
    Ui::fAddClient *ui;
};

#endif // FADDCLIENT_H
