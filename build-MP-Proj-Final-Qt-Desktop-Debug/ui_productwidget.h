/********************************************************************************
** Form generated from reading UI file 'productwidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRODUCTWIDGET_H
#define UI_PRODUCTWIDGET_H

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

class Ui_Product
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *nome_layout;
    QLabel *nome;
    QLabel *nome_exib;
    QVBoxLayout *preco_layout;
    QLabel *preco;
    QLabel *preco_exib;
    QVBoxLayout *pop_layout;
    QLabel *pop;
    QLabel *pop_exib;
    QPushButton *visualizar;

    void setupUi(QWidget *Product)
    {
        if (Product->objectName().isEmpty())
            Product->setObjectName(QString::fromUtf8("Product"));
        Product->setEnabled(true);
        Product->resize(970, 37);
        Product->setMinimumSize(QSize(970, 37));
        layoutWidget = new QWidget(Product);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 0, 971, 36));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        nome_layout = new QVBoxLayout();
        nome_layout->setObjectName(QString::fromUtf8("nome_layout"));
        nome = new QLabel(layoutWidget);
        nome->setObjectName(QString::fromUtf8("nome"));

        nome_layout->addWidget(nome);

        nome_exib = new QLabel(layoutWidget);
        nome_exib->setObjectName(QString::fromUtf8("nome_exib"));

        nome_layout->addWidget(nome_exib);


        horizontalLayout->addLayout(nome_layout);

        preco_layout = new QVBoxLayout();
        preco_layout->setObjectName(QString::fromUtf8("preco_layout"));
        preco_layout->setSizeConstraint(QLayout::SetDefaultConstraint);
        preco = new QLabel(layoutWidget);
        preco->setObjectName(QString::fromUtf8("preco"));

        preco_layout->addWidget(preco);

        preco_exib = new QLabel(layoutWidget);
        preco_exib->setObjectName(QString::fromUtf8("preco_exib"));

        preco_layout->addWidget(preco_exib);


        horizontalLayout->addLayout(preco_layout);

        pop_layout = new QVBoxLayout();
        pop_layout->setObjectName(QString::fromUtf8("pop_layout"));
        pop = new QLabel(layoutWidget);
        pop->setObjectName(QString::fromUtf8("pop"));

        pop_layout->addWidget(pop);

        pop_exib = new QLabel(layoutWidget);
        pop_exib->setObjectName(QString::fromUtf8("pop_exib"));

        pop_layout->addWidget(pop_exib);


        horizontalLayout->addLayout(pop_layout);

        visualizar = new QPushButton(layoutWidget);
        visualizar->setObjectName(QString::fromUtf8("visualizar"));

        horizontalLayout->addWidget(visualizar);


        retranslateUi(Product);

        QMetaObject::connectSlotsByName(Product);
    } // setupUi

    void retranslateUi(QWidget *Product)
    {
        Product->setWindowTitle(QApplication::translate("Product", "Form", 0, QApplication::UnicodeUTF8));
        nome->setText(QApplication::translate("Product", "Nome:", 0, QApplication::UnicodeUTF8));
        nome_exib->setText(QApplication::translate("Product", "Nome", 0, QApplication::UnicodeUTF8));
        preco->setText(QApplication::translate("Product", "Preco:", 0, QApplication::UnicodeUTF8));
        preco_exib->setText(QApplication::translate("Product", "Preco", 0, QApplication::UnicodeUTF8));
        pop->setText(QApplication::translate("Product", "Popularidade:", 0, QApplication::UnicodeUTF8));
        pop_exib->setText(QApplication::translate("Product", "Popularidade", 0, QApplication::UnicodeUTF8));
        visualizar->setText(QApplication::translate("Product", "Visualizar", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Product: public Ui_Product {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRODUCTWIDGET_H
