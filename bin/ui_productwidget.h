/********************************************************************************
** Form generated from reading UI file 'productwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRODUCTWIDGET_H
#define UI_PRODUCTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

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
            Product->setObjectName(QStringLiteral("Product"));
        Product->setEnabled(true);
        Product->resize(970, 37);
        Product->setMinimumSize(QSize(970, 37));
        layoutWidget = new QWidget(Product);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 0, 971, 36));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        nome_layout = new QVBoxLayout();
        nome_layout->setObjectName(QStringLiteral("nome_layout"));
        nome = new QLabel(layoutWidget);
        nome->setObjectName(QStringLiteral("nome"));

        nome_layout->addWidget(nome);

        nome_exib = new QLabel(layoutWidget);
        nome_exib->setObjectName(QStringLiteral("nome_exib"));

        nome_layout->addWidget(nome_exib);


        horizontalLayout->addLayout(nome_layout);

        preco_layout = new QVBoxLayout();
        preco_layout->setObjectName(QStringLiteral("preco_layout"));
        preco_layout->setSizeConstraint(QLayout::SetDefaultConstraint);
        preco = new QLabel(layoutWidget);
        preco->setObjectName(QStringLiteral("preco"));

        preco_layout->addWidget(preco);

        preco_exib = new QLabel(layoutWidget);
        preco_exib->setObjectName(QStringLiteral("preco_exib"));

        preco_layout->addWidget(preco_exib);


        horizontalLayout->addLayout(preco_layout);

        pop_layout = new QVBoxLayout();
        pop_layout->setObjectName(QStringLiteral("pop_layout"));
        pop = new QLabel(layoutWidget);
        pop->setObjectName(QStringLiteral("pop"));

        pop_layout->addWidget(pop);

        pop_exib = new QLabel(layoutWidget);
        pop_exib->setObjectName(QStringLiteral("pop_exib"));

        pop_layout->addWidget(pop_exib);


        horizontalLayout->addLayout(pop_layout);

        visualizar = new QPushButton(layoutWidget);
        visualizar->setObjectName(QStringLiteral("visualizar"));

        horizontalLayout->addWidget(visualizar);


        retranslateUi(Product);

        QMetaObject::connectSlotsByName(Product);
    } // setupUi

    void retranslateUi(QWidget *Product)
    {
        Product->setWindowTitle(QApplication::translate("Product", "Form", Q_NULLPTR));
        nome->setText(QApplication::translate("Product", "Nome:", Q_NULLPTR));
        nome_exib->setText(QApplication::translate("Product", "Nome", Q_NULLPTR));
        preco->setText(QApplication::translate("Product", "Preco:", Q_NULLPTR));
        preco_exib->setText(QApplication::translate("Product", "Preco", Q_NULLPTR));
        pop->setText(QApplication::translate("Product", "Popularidade:", Q_NULLPTR));
        pop_exib->setText(QApplication::translate("Product", "Popularidade", Q_NULLPTR));
        visualizar->setText(QApplication::translate("Product", "Visualizar", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Product: public Ui_Product {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRODUCTWIDGET_H
