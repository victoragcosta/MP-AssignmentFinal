/********************************************************************************
** Form generated from reading UI file 'visualizadorproduto.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VISUALIZADORPRODUTO_H
#define UI_VISUALIZADORPRODUTO_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VisualizadorProduto
{
public:
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLabel *result_tag;
    QVBoxLayout *resultados;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *VisualizadorProduto)
    {
        if (VisualizadorProduto->objectName().isEmpty())
            VisualizadorProduto->setObjectName(QString::fromUtf8("VisualizadorProduto"));
        VisualizadorProduto->resize(970, 294);
        widget = new QWidget(VisualizadorProduto);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 0, 971, 291));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        result_tag = new QLabel(widget);
        result_tag->setObjectName(QString::fromUtf8("result_tag"));
        result_tag->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(result_tag);

        resultados = new QVBoxLayout();
        resultados->setObjectName(QString::fromUtf8("resultados"));

        verticalLayout->addLayout(resultados);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(VisualizadorProduto);

        QMetaObject::connectSlotsByName(VisualizadorProduto);
    } // setupUi

    void retranslateUi(QWidget *VisualizadorProduto)
    {
        VisualizadorProduto->setWindowTitle(QApplication::translate("VisualizadorProduto", "Form", 0, QApplication::UnicodeUTF8));
        result_tag->setText(QApplication::translate("VisualizadorProduto", "Transa\303\247\303\265es dispon\303\255veis:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class VisualizadorProduto: public Ui_VisualizadorProduto {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VISUALIZADORPRODUTO_H
