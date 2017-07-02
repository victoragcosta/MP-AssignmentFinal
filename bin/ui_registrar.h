/********************************************************************************
** Form generated from reading UI file 'registrar.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTRAR_H
#define UI_REGISTRAR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Registrar
{
public:
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_2;
    QLabel *error_message;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *registrar;
    QVBoxLayout *usuario_layout;
    QLabel *usuario;
    QLineEdit *usuario_edit;
    QVBoxLayout *nome_layout;
    QLabel *nome;
    QLineEdit *nome_edit;
    QVBoxLayout *email_layout;
    QLabel *email;
    QLineEdit *email_edit;
    QVBoxLayout *endereco_layout;
    QLabel *endereco;
    QLineEdit *endereco_edit;
    QVBoxLayout *senha_layout;
    QLabel *senha;
    QLineEdit *senha_edit;
    QLabel *senha_confirmacao;
    QLineEdit *senha_confirmacao_edit;
    QVBoxLayout *formaPagamento_layout;
    QLabel *formaPagamento;
    QComboBox *formaPagamento_combo;
    QVBoxLayout *tipo_layout;
    QLabel *tipo;
    QComboBox *tipo_combo;
    QCheckBox *termos_servico;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *Registrar)
    {
        if (Registrar->objectName().isEmpty())
            Registrar->setObjectName(QStringLiteral("Registrar"));
        Registrar->resize(640, 480);
        widget = new QWidget(Registrar);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(0, 0, 641, 481));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        error_message = new QLabel(widget);
        error_message->setObjectName(QStringLiteral("error_message"));
        error_message->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(error_message);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        registrar = new QVBoxLayout();
        registrar->setObjectName(QStringLiteral("registrar"));
        usuario_layout = new QVBoxLayout();
        usuario_layout->setObjectName(QStringLiteral("usuario_layout"));
        usuario = new QLabel(widget);
        usuario->setObjectName(QStringLiteral("usuario"));

        usuario_layout->addWidget(usuario);

        usuario_edit = new QLineEdit(widget);
        usuario_edit->setObjectName(QStringLiteral("usuario_edit"));

        usuario_layout->addWidget(usuario_edit);


        registrar->addLayout(usuario_layout);

        nome_layout = new QVBoxLayout();
        nome_layout->setObjectName(QStringLiteral("nome_layout"));
        nome = new QLabel(widget);
        nome->setObjectName(QStringLiteral("nome"));

        nome_layout->addWidget(nome);

        nome_edit = new QLineEdit(widget);
        nome_edit->setObjectName(QStringLiteral("nome_edit"));

        nome_layout->addWidget(nome_edit);


        registrar->addLayout(nome_layout);

        email_layout = new QVBoxLayout();
        email_layout->setObjectName(QStringLiteral("email_layout"));
        email = new QLabel(widget);
        email->setObjectName(QStringLiteral("email"));

        email_layout->addWidget(email);

        email_edit = new QLineEdit(widget);
        email_edit->setObjectName(QStringLiteral("email_edit"));

        email_layout->addWidget(email_edit);


        registrar->addLayout(email_layout);

        endereco_layout = new QVBoxLayout();
        endereco_layout->setObjectName(QStringLiteral("endereco_layout"));
        endereco = new QLabel(widget);
        endereco->setObjectName(QStringLiteral("endereco"));

        endereco_layout->addWidget(endereco);

        endereco_edit = new QLineEdit(widget);
        endereco_edit->setObjectName(QStringLiteral("endereco_edit"));

        endereco_layout->addWidget(endereco_edit);


        registrar->addLayout(endereco_layout);

        senha_layout = new QVBoxLayout();
        senha_layout->setObjectName(QStringLiteral("senha_layout"));
        senha = new QLabel(widget);
        senha->setObjectName(QStringLiteral("senha"));

        senha_layout->addWidget(senha);

        senha_edit = new QLineEdit(widget);
        senha_edit->setObjectName(QStringLiteral("senha_edit"));
        senha_edit->setInputMethodHints(Qt::ImhHiddenText|Qt::ImhNoAutoUppercase|Qt::ImhNoPredictiveText|Qt::ImhSensitiveData);
        senha_edit->setEchoMode(QLineEdit::Password);

        senha_layout->addWidget(senha_edit);

        senha_confirmacao = new QLabel(widget);
        senha_confirmacao->setObjectName(QStringLiteral("senha_confirmacao"));

        senha_layout->addWidget(senha_confirmacao);

        senha_confirmacao_edit = new QLineEdit(widget);
        senha_confirmacao_edit->setObjectName(QStringLiteral("senha_confirmacao_edit"));
        senha_confirmacao_edit->setInputMethodHints(Qt::ImhHiddenText|Qt::ImhNoAutoUppercase|Qt::ImhNoPredictiveText|Qt::ImhSensitiveData);
        senha_confirmacao_edit->setEchoMode(QLineEdit::Password);

        senha_layout->addWidget(senha_confirmacao_edit);


        registrar->addLayout(senha_layout);

        formaPagamento_layout = new QVBoxLayout();
        formaPagamento_layout->setObjectName(QStringLiteral("formaPagamento_layout"));
        formaPagamento = new QLabel(widget);
        formaPagamento->setObjectName(QStringLiteral("formaPagamento"));

        formaPagamento_layout->addWidget(formaPagamento);

        formaPagamento_combo = new QComboBox(widget);
        formaPagamento_combo->setObjectName(QStringLiteral("formaPagamento_combo"));

        formaPagamento_layout->addWidget(formaPagamento_combo);


        registrar->addLayout(formaPagamento_layout);

        tipo_layout = new QVBoxLayout();
        tipo_layout->setObjectName(QStringLiteral("tipo_layout"));
        tipo = new QLabel(widget);
        tipo->setObjectName(QStringLiteral("tipo"));

        tipo_layout->addWidget(tipo);

        tipo_combo = new QComboBox(widget);
        tipo_combo->setObjectName(QStringLiteral("tipo_combo"));

        tipo_layout->addWidget(tipo_combo);


        registrar->addLayout(tipo_layout);

        termos_servico = new QCheckBox(widget);
        termos_servico->setObjectName(QStringLiteral("termos_servico"));

        registrar->addWidget(termos_servico);

        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        registrar->addWidget(pushButton);


        horizontalLayout->addLayout(registrar);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(Registrar);

        QMetaObject::connectSlotsByName(Registrar);
    } // setupUi

    void retranslateUi(QWidget *Registrar)
    {
        Registrar->setWindowTitle(QApplication::translate("Registrar", "Form", Q_NULLPTR));
        error_message->setText(QString());
        usuario->setText(QApplication::translate("Registrar", "Usuario:", Q_NULLPTR));
        nome->setText(QApplication::translate("Registrar", "Nome:", Q_NULLPTR));
        email->setText(QApplication::translate("Registrar", "Email:", Q_NULLPTR));
        endereco->setText(QApplication::translate("Registrar", "Endere\303\247o:", Q_NULLPTR));
        senha->setText(QApplication::translate("Registrar", "Senha:", Q_NULLPTR));
        senha_confirmacao->setText(QApplication::translate("Registrar", "Confirma Senha:", Q_NULLPTR));
        formaPagamento->setText(QApplication::translate("Registrar", "Forma de Pagamento:", Q_NULLPTR));
        formaPagamento_combo->clear();
        formaPagamento_combo->insertItems(0, QStringList()
         << QApplication::translate("Registrar", "Boleto", Q_NULLPTR)
         << QApplication::translate("Registrar", "Cart\303\243o de D\303\251bito", Q_NULLPTR)
         << QApplication::translate("Registrar", "Cart\303\243o de Cr\303\251dito", Q_NULLPTR)
         << QApplication::translate("Registrar", "Pay Pal", Q_NULLPTR)
        );
        tipo->setText(QApplication::translate("Registrar", "Tipo de Usu\303\241rio", Q_NULLPTR));
        tipo_combo->clear();
        tipo_combo->insertItems(0, QStringList()
         << QApplication::translate("Registrar", "Consumidor", Q_NULLPTR)
         << QApplication::translate("Registrar", "Ofertante", Q_NULLPTR)
        );
        termos_servico->setText(QApplication::translate("Registrar", "Li e Aceito os Termos de Servi\303\247o", Q_NULLPTR));
        pushButton->setText(QApplication::translate("Registrar", "Registrar", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Registrar: public Ui_Registrar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTRAR_H
