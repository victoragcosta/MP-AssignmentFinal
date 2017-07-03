/********************************************************************************
** Form generated from reading UI file 'registrar.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTRAR_H
#define UI_REGISTRAR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Registrar
{
public:
    QWidget *layoutWidget;
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
            Registrar->setObjectName(QString::fromUtf8("Registrar"));
        Registrar->resize(640, 480);
        layoutWidget = new QWidget(Registrar);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 0, 641, 558));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        error_message = new QLabel(layoutWidget);
        error_message->setObjectName(QString::fromUtf8("error_message"));
        error_message->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(error_message);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        registrar = new QVBoxLayout();
        registrar->setObjectName(QString::fromUtf8("registrar"));
        usuario_layout = new QVBoxLayout();
        usuario_layout->setObjectName(QString::fromUtf8("usuario_layout"));
        usuario = new QLabel(layoutWidget);
        usuario->setObjectName(QString::fromUtf8("usuario"));

        usuario_layout->addWidget(usuario);

        usuario_edit = new QLineEdit(layoutWidget);
        usuario_edit->setObjectName(QString::fromUtf8("usuario_edit"));

        usuario_layout->addWidget(usuario_edit);


        registrar->addLayout(usuario_layout);

        nome_layout = new QVBoxLayout();
        nome_layout->setObjectName(QString::fromUtf8("nome_layout"));
        nome = new QLabel(layoutWidget);
        nome->setObjectName(QString::fromUtf8("nome"));

        nome_layout->addWidget(nome);

        nome_edit = new QLineEdit(layoutWidget);
        nome_edit->setObjectName(QString::fromUtf8("nome_edit"));

        nome_layout->addWidget(nome_edit);


        registrar->addLayout(nome_layout);

        email_layout = new QVBoxLayout();
        email_layout->setObjectName(QString::fromUtf8("email_layout"));
        email = new QLabel(layoutWidget);
        email->setObjectName(QString::fromUtf8("email"));

        email_layout->addWidget(email);

        email_edit = new QLineEdit(layoutWidget);
        email_edit->setObjectName(QString::fromUtf8("email_edit"));

        email_layout->addWidget(email_edit);


        registrar->addLayout(email_layout);

        endereco_layout = new QVBoxLayout();
        endereco_layout->setObjectName(QString::fromUtf8("endereco_layout"));
        endereco = new QLabel(layoutWidget);
        endereco->setObjectName(QString::fromUtf8("endereco"));

        endereco_layout->addWidget(endereco);

        endereco_edit = new QLineEdit(layoutWidget);
        endereco_edit->setObjectName(QString::fromUtf8("endereco_edit"));

        endereco_layout->addWidget(endereco_edit);


        registrar->addLayout(endereco_layout);

        senha_layout = new QVBoxLayout();
        senha_layout->setObjectName(QString::fromUtf8("senha_layout"));
        senha = new QLabel(layoutWidget);
        senha->setObjectName(QString::fromUtf8("senha"));

        senha_layout->addWidget(senha);

        senha_edit = new QLineEdit(layoutWidget);
        senha_edit->setObjectName(QString::fromUtf8("senha_edit"));
        senha_edit->setInputMethodHints(Qt::ImhHiddenText|Qt::ImhNoAutoUppercase|Qt::ImhNoPredictiveText);
        senha_edit->setEchoMode(QLineEdit::Password);

        senha_layout->addWidget(senha_edit);

        senha_confirmacao = new QLabel(layoutWidget);
        senha_confirmacao->setObjectName(QString::fromUtf8("senha_confirmacao"));

        senha_layout->addWidget(senha_confirmacao);

        senha_confirmacao_edit = new QLineEdit(layoutWidget);
        senha_confirmacao_edit->setObjectName(QString::fromUtf8("senha_confirmacao_edit"));
        senha_confirmacao_edit->setInputMethodHints(Qt::ImhHiddenText|Qt::ImhNoAutoUppercase|Qt::ImhNoPredictiveText);
        senha_confirmacao_edit->setEchoMode(QLineEdit::Password);

        senha_layout->addWidget(senha_confirmacao_edit);


        registrar->addLayout(senha_layout);

        formaPagamento_layout = new QVBoxLayout();
        formaPagamento_layout->setObjectName(QString::fromUtf8("formaPagamento_layout"));
        formaPagamento = new QLabel(layoutWidget);
        formaPagamento->setObjectName(QString::fromUtf8("formaPagamento"));

        formaPagamento_layout->addWidget(formaPagamento);

        formaPagamento_combo = new QComboBox(layoutWidget);
        formaPagamento_combo->setObjectName(QString::fromUtf8("formaPagamento_combo"));

        formaPagamento_layout->addWidget(formaPagamento_combo);


        registrar->addLayout(formaPagamento_layout);

        tipo_layout = new QVBoxLayout();
        tipo_layout->setObjectName(QString::fromUtf8("tipo_layout"));
        tipo = new QLabel(layoutWidget);
        tipo->setObjectName(QString::fromUtf8("tipo"));

        tipo_layout->addWidget(tipo);

        tipo_combo = new QComboBox(layoutWidget);
        tipo_combo->setObjectName(QString::fromUtf8("tipo_combo"));

        tipo_layout->addWidget(tipo_combo);


        registrar->addLayout(tipo_layout);

        termos_servico = new QCheckBox(layoutWidget);
        termos_servico->setObjectName(QString::fromUtf8("termos_servico"));

        registrar->addWidget(termos_servico);

        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

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
        Registrar->setWindowTitle(QApplication::translate("Registrar", "Form", 0, QApplication::UnicodeUTF8));
        error_message->setText(QString());
        usuario->setText(QApplication::translate("Registrar", "Usuario:", 0, QApplication::UnicodeUTF8));
        nome->setText(QApplication::translate("Registrar", "Nome:", 0, QApplication::UnicodeUTF8));
        email->setText(QApplication::translate("Registrar", "Email:", 0, QApplication::UnicodeUTF8));
        endereco->setText(QApplication::translate("Registrar", "Endere\303\247o:", 0, QApplication::UnicodeUTF8));
        senha->setText(QApplication::translate("Registrar", "Senha:", 0, QApplication::UnicodeUTF8));
        senha_confirmacao->setText(QApplication::translate("Registrar", "Confirma Senha:", 0, QApplication::UnicodeUTF8));
        formaPagamento->setText(QApplication::translate("Registrar", "Forma de Pagamento:", 0, QApplication::UnicodeUTF8));
        formaPagamento_combo->clear();
        formaPagamento_combo->insertItems(0, QStringList()
         << QApplication::translate("Registrar", "Boleto", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Registrar", "Cart\303\243o de D\303\251bito", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Registrar", "Cart\303\243o de Cr\303\251dito", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Registrar", "Pay Pal", 0, QApplication::UnicodeUTF8)
        );
        tipo->setText(QApplication::translate("Registrar", "Tipo de Usu\303\241rio", 0, QApplication::UnicodeUTF8));
        tipo_combo->clear();
        tipo_combo->insertItems(0, QStringList()
         << QApplication::translate("Registrar", "Consumidor", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Registrar", "Ofertante", 0, QApplication::UnicodeUTF8)
        );
        termos_servico->setText(QApplication::translate("Registrar", "Li e Aceito os Termos de Servi\303\247o", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("Registrar", "Registrar", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Registrar: public Ui_Registrar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTRAR_H
