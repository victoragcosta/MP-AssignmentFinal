#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../include/product_search.h"
#include "productwidget.h"
#include "../include/transaction_search.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void updateLoginStatus();
    void setErrorMessage(QString message);
    void setProductList(productList *list);
    void setTransactionList(transactionList *list);
    void addResult(ProductWidget *novo);
    ProductWidget *getResult();
    void cleanResults();
    transactionList *listaTransactions;

private slots:

    void on_login_clicked();

    void on_registrar_clicked();

    void on_logout_clicked();

    void on_busca_edit_returnPressed();

private:
    Ui::MainWindow *ui;
    productList *listaProdutos;
    ProductWidget *results;
};

#endif // MAINWINDOW_H
