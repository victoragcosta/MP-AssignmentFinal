#include "login.h"
#include "ui_login.h"
#include <string.h>

#include "../include/usuarios.h"
#include "../include/mainwindow.h"
#include "admin.h"

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->main = NULL;
}

Login::~Login()
{
    delete ui;
}

void Login::on_submit_clicked()
{
    char username[50];
    strcpy(username, (char*)qPrintable(ui->username_edit->text()));
    char password[50];
    strcpy(password, (char*)qPrintable(ui->password_edit->text()));

    Admin *admin = new Admin;
    usuarios_condRet erro = usuarios_login(username, password);
    usuarios_tipo_usuario tipo;
    switch (erro) {
    case USUARIOS_SUCESSO:
        this->main->updateLoginStatus();
        this->main->setErrorMessage("");
        usuarios_retornaDados(0,"tipo", (void*)&tipo);
        this->close();
        if(tipo == ADMINISTRADOR){
            admin->setTransactionList(this->main->listaTransactions);
            admin->show();
        }
        break;
    default:
        QString error_message = QString("Erro ao fazer login! Código de Erro: %1").arg(erro);
        ui->error_message->setText(error_message);
        break;
    }
}

void Login::setMainWindow(MainWindow *main)
{
    this->main = main;
}
