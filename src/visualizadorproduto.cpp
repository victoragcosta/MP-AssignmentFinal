#include "visualizadorproduto.h"
#include "ui_visualizadorproduto.h"

#include <QString>
#include "transacao.h"
#include "transaction_search.h"

VisualizadorProduto::VisualizadorProduto(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VisualizadorProduto)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
}

VisualizadorProduto::~VisualizadorProduto()
{
    delete ui;
}

void VisualizadorProduto::setProduct(ProductWidget *prod)
{
    this->related = prod;
}

void VisualizadorProduto::setTransactionList(transactionList *list){
    this->transactions = list;
}

#include <stdio.h>
void VisualizadorProduto::showTransactions()
{
    int i;
    Transacao *transacao;
    printf("ue\n");
    for(i = 0; i < this->transactions->size; i++){
        printf("transa[%d]: %s\n", i, this->transactions->items[i].item.name);
        transacao = new Transacao(this);
        transacao->setTransactionList(this->transactions);
        transacao->setId(i);
        transacao->applySet();
        ui->resultados->addWidget(transacao);
        transacao->show();
    }
}
