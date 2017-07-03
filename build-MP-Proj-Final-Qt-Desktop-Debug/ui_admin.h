/********************************************************************************
** Form generated from reading UI file 'admin.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADMIN_H
#define UI_ADMIN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Admin
{
public:
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *listar_transacoes;
    QPushButton *cria_transacoes;
    QVBoxLayout *transacoes;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *Admin)
    {
        if (Admin->objectName().isEmpty())
            Admin->setObjectName(QString::fromUtf8("Admin"));
        Admin->resize(400, 408);
        widget = new QWidget(Admin);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(-1, 0, 401, 411));
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        listar_transacoes = new QPushButton(widget);
        listar_transacoes->setObjectName(QString::fromUtf8("listar_transacoes"));

        horizontalLayout->addWidget(listar_transacoes);

        cria_transacoes = new QPushButton(widget);
        cria_transacoes->setObjectName(QString::fromUtf8("cria_transacoes"));

        horizontalLayout->addWidget(cria_transacoes);


        verticalLayout_2->addLayout(horizontalLayout);

        transacoes = new QVBoxLayout();
        transacoes->setObjectName(QString::fromUtf8("transacoes"));

        verticalLayout_2->addLayout(transacoes);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        retranslateUi(Admin);

        QMetaObject::connectSlotsByName(Admin);
    } // setupUi

    void retranslateUi(QWidget *Admin)
    {
        Admin->setWindowTitle(QApplication::translate("Admin", "Form", 0, QApplication::UnicodeUTF8));
        listar_transacoes->setText(QApplication::translate("Admin", "Listar Transa\303\247\303\265es", 0, QApplication::UnicodeUTF8));
        cria_transacoes->setText(QApplication::translate("Admin", "Criar Transa\303\247\303\243o", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Admin: public Ui_Admin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADMIN_H
