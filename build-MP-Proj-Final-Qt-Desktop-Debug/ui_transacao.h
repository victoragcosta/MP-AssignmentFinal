/********************************************************************************
** Form generated from reading UI file 'transacao.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRANSACAO_H
#define UI_TRANSACAO_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Transacao
{
public:
    QWidget *widget;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_4;
    QLabel *usuario1;
    QLabel *usuario1_edit;
    QVBoxLayout *verticalLayout_3;
    QLabel *usuario2;
    QLabel *usuario2_edit;
    QVBoxLayout *verticalLayout_2;
    QLabel *nome;
    QLabel *nome_edit;
    QVBoxLayout *verticalLayout;
    QLabel *estado;
    QLabel *estado_edit;
    QPushButton *pushButton;

    void setupUi(QWidget *Transacao)
    {
        if (Transacao->objectName().isEmpty())
            Transacao->setObjectName(QString::fromUtf8("Transacao"));
        Transacao->resize(400, 78);
        Transacao->setMinimumSize(QSize(400, 78));
        widget = new QWidget(Transacao);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 0, 401, 79));
        verticalLayout_5 = new QVBoxLayout(widget);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        usuario1 = new QLabel(widget);
        usuario1->setObjectName(QString::fromUtf8("usuario1"));

        verticalLayout_4->addWidget(usuario1);

        usuario1_edit = new QLabel(widget);
        usuario1_edit->setObjectName(QString::fromUtf8("usuario1_edit"));

        verticalLayout_4->addWidget(usuario1_edit);


        horizontalLayout->addLayout(verticalLayout_4);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        usuario2 = new QLabel(widget);
        usuario2->setObjectName(QString::fromUtf8("usuario2"));

        verticalLayout_3->addWidget(usuario2);

        usuario2_edit = new QLabel(widget);
        usuario2_edit->setObjectName(QString::fromUtf8("usuario2_edit"));

        verticalLayout_3->addWidget(usuario2_edit);


        horizontalLayout->addLayout(verticalLayout_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        nome = new QLabel(widget);
        nome->setObjectName(QString::fromUtf8("nome"));

        verticalLayout_2->addWidget(nome);

        nome_edit = new QLabel(widget);
        nome_edit->setObjectName(QString::fromUtf8("nome_edit"));

        verticalLayout_2->addWidget(nome_edit);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        estado = new QLabel(widget);
        estado->setObjectName(QString::fromUtf8("estado"));

        verticalLayout->addWidget(estado);

        estado_edit = new QLabel(widget);
        estado_edit->setObjectName(QString::fromUtf8("estado_edit"));

        verticalLayout->addWidget(estado_edit);


        horizontalLayout->addLayout(verticalLayout);


        verticalLayout_5->addLayout(horizontalLayout);

        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout_5->addWidget(pushButton);


        retranslateUi(Transacao);

        QMetaObject::connectSlotsByName(Transacao);
    } // setupUi

    void retranslateUi(QWidget *Transacao)
    {
        Transacao->setWindowTitle(QApplication::translate("Transacao", "Form", 0, QApplication::UnicodeUTF8));
        usuario1->setText(QApplication::translate("Transacao", "Usuario 1:", 0, QApplication::UnicodeUTF8));
        usuario1_edit->setText(QApplication::translate("Transacao", "editU1", 0, QApplication::UnicodeUTF8));
        usuario2->setText(QApplication::translate("Transacao", "Usuario 2:", 0, QApplication::UnicodeUTF8));
        usuario2_edit->setText(QApplication::translate("Transacao", "editU2", 0, QApplication::UnicodeUTF8));
        nome->setText(QApplication::translate("Transacao", "Nome:", 0, QApplication::UnicodeUTF8));
        nome_edit->setText(QApplication::translate("Transacao", "editNome", 0, QApplication::UnicodeUTF8));
        estado->setText(QApplication::translate("Transacao", "Estado", 0, QApplication::UnicodeUTF8));
        estado_edit->setText(QApplication::translate("Transacao", "editEstado", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("Transacao", "Deletar", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Transacao: public Ui_Transacao {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRANSACAO_H
