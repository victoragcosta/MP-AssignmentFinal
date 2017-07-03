#include "ui_mainwindow.h"
#include "../include/mainwindow.h"

#include "login.h"
#include "registrar.h"
#include "productwidget.h"

#include "../include/usuarios.h"
#include "../include/product.h"
#include "../include/product_search.h"
#include "../include/error_level.h"
#include "../include/transaction.h"
#include "../include/transaction_search.h"

#include <stdio.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->results = NULL;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_login_clicked()
{
    Login *login_screen = new Login();
    login_screen->setMainWindow(this);
    login_screen->show();
}

void MainWindow::on_registrar_clicked()
{
    Registrar *registrar_screen = new Registrar();
    registrar_screen->show();
}

void MainWindow::on_logout_clicked()
{
    usuarios_condRet error_level = usuarios_logout();
    switch (error_level) {
    case USUARIOS_SUCESSO:
        ui->error_message->setText("Deslogado com Sucesso!");
        break;
    default:
        QString error_message = QString("Erro ao deslogar. Código de Erro %1").arg(error_level);
        ui->error_message->setText(error_message);
        break;
    }
    this->updateLoginStatus();
}

void MainWindow::setErrorMessage(QString message)
{
    ui->error_message->setText(message);
}

void MainWindow::updateLoginStatus()
{
    char usuario[50];
    usuarios_condRet erro = usuarios_retornaDados(0, "usuario", (void*)usuario);

    QString username_qstring;
    switch (erro) {
    case USUARIOS_SUCESSO:
        username_qstring = QString(usuario);
        ui->username->setText(username_qstring);
        ui->busca_edit->setEnabled(true);
        break;
    default:
        ui->username->setText("Faça Login!");
        ui->busca_edit->setEnabled(false);
        break;
    }

}

void MainWindow::on_busca_edit_returnPressed()
{
    //Captura Query
    char busca[75];
    strcpy(busca, (char*)qPrintable(ui->busca_edit->text()));

    double min_preco = ui->min_preco_spin->value();
    double max_preco = ui->max_preco_spin->value();
    int tipo = ui->tipo_combo->currentIndex();
    int min_popularidade = ui->popuaridade_min_spin->value();
    int max_popularidade = ui->popuaridade_max_spin->value();

    productSpecification especificacao;
    errorLevel erro;
    erro = CreateSpecification((productType)tipo, min_preco, max_preco, min_popularidade, max_popularidade, &especificacao);
    if(erro != Success){
        exit(erro);
    }

    productList resultado;
    resultado.items = NULL;
    erro = SearchProduct(busca, this->listaProdutos, &especificacao, &resultado);

    int i;
    ProductWidget *productWidget;
    if(erro == Success){
        this->setErrorMessage("Busca feita com sucesso!");
        this->cleanResults();
        for(i = 0; i < resultado.size; i++){
            productWidget = new ProductWidget(this);
            productWidget->setName(resultado.items[i].name);
            productWidget->setPreco(resultado.items[i].price);
            productWidget->setPop(resultado.items[i].popularity);
            productWidget->applySet();
            ui->resultados->addWidget(productWidget);
            productWidget->show();
            productWidget->setId(i);
            this->addResult(productWidget);
        }
    } else {
        this->setErrorMessage("Sem itens com esse nome!");
        this->cleanResults();
        for(i = 0; i < this->listaProdutos->size; i++){
            productWidget = new ProductWidget(this);
            productWidget->setName(this->listaProdutos->items[i].name);
            productWidget->setPreco(this->listaProdutos->items[i].price);
            productWidget->setPop(this->listaProdutos->items[i].popularity);
            productWidget->applySet();
            ui->resultados->addWidget(productWidget);
            productWidget->show();
            productWidget->setId(i);
            this->addResult(productWidget);
        }
    }
}

void MainWindow::setProductList(productList *list){
    this->listaProdutos = list;
}

void MainWindow::setTransactionList(transactionList *list){
    this->listaTransactions = list;
}

void MainWindow::addResult(ProductWidget *novo)
{
    novo->setNext(this->results);
    this->results = novo;
}

ProductWidget *MainWindow::getResult()
{
    if(this->results == NULL)
        return NULL;
    ProductWidget *retorno = this->results;
    this->results = this->results->getNext();
    return retorno;
}

void MainWindow::cleanResults()
{
    ProductWidget *toDelete;
    while((toDelete = this->getResult()) != NULL){
        toDelete->close();
        delete toDelete;
    }
}
