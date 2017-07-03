#ifndef ADMIN_H
#define ADMIN_H

#include <QWidget>
#include "transaction_search.h"

namespace Ui {
class Admin;
}

class Admin : public QWidget
{
    Q_OBJECT

public:
    explicit Admin(QWidget *parent = 0);
    ~Admin();
    void setTransactionList(transactionList *list);

private slots:
    void on_listar_transacoes_clicked();

private:
    Ui::Admin *ui;
    transactionList *listaTransactions;
};

#endif // ADMIN_H
