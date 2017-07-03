#include "admin.h"
#include "ui_admin.h"

#include "transacao.h"

Admin::Admin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Admin)
{
    ui->setupUi(this);
}

Admin::~Admin()
{
    delete ui;
}

void Admin::setTransactionList(transactionList *list){
    this->listaTransactions = list;
}

#include <stdio.h>
void Admin::on_listar_transacoes_clicked()
{
    int i;
    Transacao *transacao;
    printf("ue\n");
    for(i = 0; i < this->listaTransactions->size; i++){
        printf("transa[%d]: %s\n", i, this->listaTransactions->items[i].item.name);
        transacao = new Transacao(this);
        transacao->setTransactionList(this->listaTransactions);
        transacao->setId(i);
        transacao->applySet();
        ui->transacoes->addWidget(transacao);
        transacao->show();
    }
}
