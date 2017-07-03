#include "transacao.h"
#include "ui_transacao.h"

#include "transaction_search.h"

Transacao::Transacao(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Transacao)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
}

Transacao::~Transacao()
{
    delete ui;
}

void Transacao::on_pushButton_clicked()
{
    DeleteTransaction(this->id, this->listaTransactions);
    this->close();
}

void Transacao::setId(int id)
{
    this->id = id;
}

void Transacao::setTransactionList(transactionList *list){
    this->listaTransactions = list;
}

void Transacao::applySet()
{
    ui->estado_edit->setText(QString::number(this->listaTransactions->items[this->id].status));
    ui->usuario1_edit->setText(QString::number(this->listaTransactions->items[this->id].user1));
    ui->usuario2_edit->setText(QString::number(this->listaTransactions->items[this->id].user2));
    ui->nome_edit->setText(this->listaTransactions->items[this->id].item.name);
}
