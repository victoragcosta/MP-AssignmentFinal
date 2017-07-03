#ifndef TRANSACAO_H
#define TRANSACAO_H

#include <QWidget>
#include "transaction_search.h"

namespace Ui {
class Transacao;
}

class Transacao : public QWidget
{
    Q_OBJECT

public:
    explicit Transacao(QWidget *parent = 0);
    ~Transacao();
    void setId(int id);
    void setTransactionList(transactionList *list);
    void applySet();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Transacao *ui;
    int id;
    transactionList *listaTransactions;
};

#endif // TRANSACAO_H
