#include "../include/mainwindow.h"
#include <QApplication>
#include <stdio.h>
#include <iostream>

#include "../include/usuarios.h"
#include "../include/product.h"
#include "../include/product_search.h"
#include "../include/avaliacao.h"
#include "../include/transaction_search.h"
#include "../include/transaction.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    //inicializar
    if(usuarios_carregarArquivo() != USUARIOS_SUCESSO)
        exit(1);

    cout << "eita" << endl;

    productList lista;
    lista.items = NULL;
    CleanProductList(&lista);
    LoadProductList(&lista);
    w.setProductList(&lista);

    cout << "eita" << endl;

    transactionList listaTransaction;
    cout << "eita" << endl;
    listaTransaction.items = NULL;
    cout << "eita" << endl;
    CleanTransactionList(&listaTransaction);
    cout << "eita" << endl;
    LoadTransactionList(&listaTransaction);
    cout << "eita" << endl;
    w.setTransactionList(&listaTransaction);

    cout << "eita" << endl;

    w.show();
    int retorno = a.exec();

    //clean up
    usuarios_limpar();
    SaveProductList(&lista);
    CleanProductList(&lista);
    SaveTransactionList(&listaTransaction);
    CleanTransactionList(&listaTransaction);

    return retorno;
}
