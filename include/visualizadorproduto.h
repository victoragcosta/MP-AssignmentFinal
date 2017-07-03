#ifndef VISUALIZADORPRODUTO_H
#define VISUALIZADORPRODUTO_H

#include <QWidget>
#include "productwidget.h"
#include "transaction_search.h"

namespace Ui {
class VisualizadorProduto;
}

class VisualizadorProduto : public QWidget
{
    Q_OBJECT

public:
    explicit VisualizadorProduto(QWidget *parent = 0);
    ~VisualizadorProduto();
    void setProduct(ProductWidget *prod);
    void setTransactionList(transactionList *list);
    void showTransactions();

private slots:

private:
    Ui::VisualizadorProduto *ui;
    ProductWidget *related;
    transactionList *transactions;
};

#endif // VISUALIZADORPRODUTO_H
