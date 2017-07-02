#include "registrar.h"
#include "ui_registrar.h"
#include "../include/usuarios.h"

Registrar::Registrar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Registrar)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
}

Registrar::~Registrar()
{
    delete ui;
}

void Registrar::on_pushButton_clicked()
{
    char usuario[50];
    strcpy(usuario, (char*)qPrintable(ui->usuario_edit->text()));
    char nome[50];
    strcpy(nome, (char*)qPrintable(ui->nome_edit->text()));
    char email[50];
    strcpy(email, (char*)qPrintable(ui->email_edit->text()));
    char endereco[50];
    strcpy(endereco, (char*)qPrintable(ui->endereco_edit->text()));
    char senha[50];
    strcpy(senha, (char*)qPrintable(ui->senha_edit->text()));
    char senha_confirmacao[50];
    strcpy(senha_confirmacao, (char*)qPrintable(ui->senha_confirmacao_edit->text()));
    int formaPagamento = ui->formaPagamento_combo->currentIndex();
    int tipo = ui->tipo_combo->currentIndex();
    bool termos_servico = ui->termos_servico->checkState();

    usuarios_condRet nivel_erro;
    if(!termos_servico){
        ui->error_message->setText("É preciso aceitar os termos de uso antes de prosseguir.");
    } else {
        ui->error_message->setText("");
        nivel_erro = usuarios_cadastro(8,
                          "usuario",usuario,
                          "nome",nome,
                          "email",email,
                          "endereco",endereco,
                          "senha",senha,
                          "senha_confirmacao", senha_confirmacao,
                          "formaPagamento", formaPagamento,
                          "tipo", tipo);
        switch (nivel_erro) {
        case USUARIOS_SUCESSO:
            this->close();
            break;
        case USUARIOS_FALHA_EMAIL_INVALIDO:
            ui->error_message->setText("Email Inválido, tente novamente.");
        default:
            QString error_message = QString("Ocorreu algum erro no registro. Código de Erro: %1").arg(nivel_erro);
            ui->error_message->setText(error_message);
            break;
        }
    }
}
