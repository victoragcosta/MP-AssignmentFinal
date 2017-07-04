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
    usuarios_condRet erro;
    if((erro = usuarios_carregarArquivo()) != USUARIOS_SUCESSO){
        cout << erro << endl;
        exit(1);
    }

    cout << "teste" << endl;

    productList lista;
    lista.items = NULL;
    CleanProductList(&lista);
    LoadProductList(&lista);
    w.setProductList(&lista);

    cout << "teste" << endl;

    transactionList listaTransaction;
    listaTransaction.items = NULL;
    CleanTransactionList(&listaTransaction);
    LoadTransactionList(&listaTransaction);
    cout << "teste" << endl;
    w.setTransactionList(&listaTransaction);


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
