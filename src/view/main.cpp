#include "../include/mainwindow.h"
#include <QApplication>
#include <stdio.h>

#include "../include/usuarios.h"
#include "../include/product.h"
#include "../include/product_search.h"
#include "../include/avaliacao.h"
#include "../include/transaction_search.h"
#include "../include/transaction.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    //inicializar
    if(usuarios_carregarArquivo() != USUARIOS_SUCESSO)
        exit(1);

    productList lista;
    lista.items = NULL;
    CleanProductList(&lista);
    LoadProductList(&lista);
    w.setProductList(&lista);

    transactionList listaTransaction;
    listaTransaction.items = NULL;
    CleanTransactionList(&listaTransaction);
    LoadTransactionList(&listaTransaction);
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
