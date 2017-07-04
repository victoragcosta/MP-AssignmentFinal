#include "productwidget.h"
#include "ui_productwidget.h"
#include "visualizadorproduto.h"

#include "admin.h"

ProductWidget::ProductWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Product)
{
    ui->setupUi(this);
}

ProductWidget::~ProductWidget()
{
    delete ui;
    this->setAttribute(Qt::WA_DeleteOnClose);
}

void ProductWidget::setName(QString name)
{
    this->name = name;
}

void ProductWidget::setPreco(double preco)
{
    this->preco = preco;
}

void ProductWidget::setPop(int pop)
{
    this->pop = pop;
}

void ProductWidget::applySet()
{
    ui->nome_exib->setText(this->name);
    ui->pop_exib->setText(QString("%1").arg(this->pop));
    ui->preco_exib->setText(QString("%1").arg(this->preco));
}

ProductWidget *ProductWidget::getNext()
{
    return this->next;
}

void ProductWidget::setNext(ProductWidget *product)
{
    this->next = product;
}

void ProductWidget::setId(int id)
{
    this->id = id;
}

int ProductWidget::getId()
{
    return this->id;
}

void ProductWidget::on_visualizar_clicked()
{
    usuarios_tipo_usuario tipo;
    usuarios_retornaDados(0,"tipo", (void*)&tipo);
    if(tipo == ADMINISTRADOR){
        Admin *admin = new Admin;
        admin->setId(this->id);
        admin->setProductList(this->products);
        admin->setTransactionList(this->transactions);
        admin->show();
    } else {
        VisualizadorProduto *visu = new VisualizadorProduto;
        visu->setProduct(this);
        visu->setTransactionList(this->transactions);
        visu->show();
        visu->showTransactions();
    }
}


QString ProductWidget::getName()
{
    return this->name;
}

double ProductWidget::getPreco()
{
    return this->preco;
}


int ProductWidget::getPop()
{
    return this->pop;
}

void ProductWidget::setTransactionList(transactionList *list){
    this->transactions = list;
}

void ProductWidget::setProductsList(productList *list)
{
    this->products = list;
}
