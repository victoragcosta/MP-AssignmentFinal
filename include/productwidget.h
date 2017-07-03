#ifndef PRODUCT_H
#define PRODUCT_H

#include <QWidget>
#include "transaction_search.h"

namespace Ui {
class Product;
}

class ProductWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ProductWidget(QWidget *parent = 0);
    ~ProductWidget();
    void setName(QString name);
    void setPreco(double preco);
    void setPop(int pop);
    void applySet();
    ProductWidget *getNext();
    void setNext(ProductWidget *product);
    void setId(int id);
    int getId();
    void setTransactionList(transactionList *list);

    QString getName();
    double getPreco();
    int getPop();

private slots:
    void on_visualizar_clicked();

private:
    Ui::Product *ui;
    QString name;
    double preco;
    int pop;
    ProductWidget *next;
    int id;
    transactionList *transactions;
};

#endif // PRODUCT_H
