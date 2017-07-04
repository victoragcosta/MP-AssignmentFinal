#ifndef ADMIN_H
#define ADMIN_H

#include <QWidget>
#include "transaction_search.h"
#include "product_search.h"

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
    void setProductList(productList *list);
    void setId(int id);

private slots:
    void on_listar_transacoes_clicked();

    void on_cria_transacoes_clicked();

private:
    Ui::Admin *ui;
    transactionList *listaTransactions;
    productList *listaProdutos;
    int id;
};

#endif // ADMIN_H
