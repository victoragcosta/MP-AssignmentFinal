#include "visualizadorproduto.h"
#include "ui_visualizadorproduto.h"

#include <QString>

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
    ProductWidget *productWidget;
    char usuario[50];
    usuarios_condRet erro;
    printf("tamanho: %d\n", this->transactions->size);
    for(i = 0; i < this->transactions->size; i++){
        printf("id: %d", this->transactions->items[i].user1);
        erro = usuarios_retornaDados(this->transactions->items[i].user1, "usuario", (void*)usuario);
        printf("erro: %d\n", erro);
        printf("name: %s\n", usuario);
        productWidget = new ProductWidget(this);
        productWidget->setName(QString(usuario));
        productWidget->setPreco(this->transactions->items[i].item.price);
        productWidget->setPop(this->transactions->items[i].item.popularity);
        productWidget->applySet();
        ui->resultados->addWidget(productWidget);
        productWidget->show();
        productWidget->setId(i);
    }
}
