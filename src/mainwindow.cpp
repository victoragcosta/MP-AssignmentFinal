#include "ui_mainwindow.h"
#include "../include/mainwindow.h"

#include "login.h"
#include "registrar.h"

#include "../include/usuarios.h"
#include "../include/product.h"
#include "../include/product_search.h"

//extern usuarios_login(char *, char *);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
    especificacao.minimum_price = min_preco;
    especificacao.maximum_price = max_preco;
    especificacao.type = tipo;
    especificacao.minimum_popularity = min_popularidade;
    especificacao.maximum_popularity = max_popularidade;

    productList resultado;
    //SearchProduct(busca, <preencher>, &especificacao, &resultado);
}
