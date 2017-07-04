#include "admin.h"
#include "ui_admin.h"

#include "transacao.h"
#include "transaction.h"
#include "transaction_search.h"

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
        transacao = new Transacao(this);
        transacao->setTransactionList(this->listaTransactions);
        transacao->setId(i);
        transacao->applySet();
        ui->transacoes->addWidget(transacao);
        transacao->show();
    }
}

void Admin::on_cria_transacoes_clicked()
{
    //CreateTransaction(ui->u1->value(), ui->u1->value(), );
}
