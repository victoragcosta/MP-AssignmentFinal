/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QStatusBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *widget;
    QVBoxLayout *tudo;
    QHBoxLayout *topbar;
    QVBoxLayout *busca_layout;
    QLabel *busca;
    QLineEdit *busca_edit;
    QHBoxLayout *advanced;
    QVBoxLayout *min_preco_layout;
    QLabel *min_preco;
    QDoubleSpinBox *min_preco_spin;
    QVBoxLayout *max_preco_layout;
    QLabel *max_preco;
    QDoubleSpinBox *max_preco_spin;
    QVBoxLayout *tipo_layout;
    QLabel *tipo;
    QComboBox *tipo_combo;
    QVBoxLayout *popularidade_min_layout;
    QLabel *popularidade_min;
    QSpinBox *popuaridade_min_spin;
    QVBoxLayout *popularidade_max_layout;
    QLabel *popularidade_max;
    QSpinBox *popuaridade_max_spin;
    QVBoxLayout *verticalLayout;
    QLabel *username;
    QHBoxLayout *horizontalLayout;
    QPushButton *login;
    QPushButton *registrar;
    QPushButton *logout;
    QLabel *error_message;
    QVBoxLayout *resultados;
    QSpacerItem *verticalSpacer;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1000, 477);
        QIcon icon;
        icon.addFile(QString::fromUtf8("img_carrinho.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(11, 1, 981, 441));
        tudo = new QVBoxLayout(widget);
        tudo->setSpacing(6);
        tudo->setContentsMargins(11, 11, 11, 11);
        tudo->setObjectName(QString::fromUtf8("tudo"));
        tudo->setContentsMargins(0, 0, 0, 0);
        topbar = new QHBoxLayout();
        topbar->setSpacing(6);
        topbar->setObjectName(QString::fromUtf8("topbar"));
        busca_layout = new QVBoxLayout();
        busca_layout->setSpacing(6);
        busca_layout->setObjectName(QString::fromUtf8("busca_layout"));
        busca = new QLabel(widget);
        busca->setObjectName(QString::fromUtf8("busca"));

        busca_layout->addWidget(busca);

        busca_edit = new QLineEdit(widget);
        busca_edit->setObjectName(QString::fromUtf8("busca_edit"));
        busca_edit->setEnabled(false);

        busca_layout->addWidget(busca_edit);

        advanced = new QHBoxLayout();
        advanced->setSpacing(6);
        advanced->setObjectName(QString::fromUtf8("advanced"));
        min_preco_layout = new QVBoxLayout();
        min_preco_layout->setSpacing(6);
        min_preco_layout->setObjectName(QString::fromUtf8("min_preco_layout"));
        min_preco = new QLabel(widget);
        min_preco->setObjectName(QString::fromUtf8("min_preco"));

        min_preco_layout->addWidget(min_preco);

        min_preco_spin = new QDoubleSpinBox(widget);
        min_preco_spin->setObjectName(QString::fromUtf8("min_preco_spin"));
        min_preco_spin->setMaximum(1e+06);

        min_preco_layout->addWidget(min_preco_spin);


        advanced->addLayout(min_preco_layout);

        max_preco_layout = new QVBoxLayout();
        max_preco_layout->setSpacing(6);
        max_preco_layout->setObjectName(QString::fromUtf8("max_preco_layout"));
        max_preco = new QLabel(widget);
        max_preco->setObjectName(QString::fromUtf8("max_preco"));

        max_preco_layout->addWidget(max_preco);

        max_preco_spin = new QDoubleSpinBox(widget);
        max_preco_spin->setObjectName(QString::fromUtf8("max_preco_spin"));
        max_preco_spin->setMaximum(1e+06);
        max_preco_spin->setValue(1e+06);

        max_preco_layout->addWidget(max_preco_spin);


        advanced->addLayout(max_preco_layout);

        tipo_layout = new QVBoxLayout();
        tipo_layout->setSpacing(6);
        tipo_layout->setObjectName(QString::fromUtf8("tipo_layout"));
        tipo = new QLabel(widget);
        tipo->setObjectName(QString::fromUtf8("tipo"));

        tipo_layout->addWidget(tipo);

        tipo_combo = new QComboBox(widget);
        tipo_combo->setObjectName(QString::fromUtf8("tipo_combo"));

        tipo_layout->addWidget(tipo_combo);


        advanced->addLayout(tipo_layout);

        popularidade_min_layout = new QVBoxLayout();
        popularidade_min_layout->setSpacing(6);
        popularidade_min_layout->setObjectName(QString::fromUtf8("popularidade_min_layout"));
        popularidade_min = new QLabel(widget);
        popularidade_min->setObjectName(QString::fromUtf8("popularidade_min"));

        popularidade_min_layout->addWidget(popularidade_min);

        popuaridade_min_spin = new QSpinBox(widget);
        popuaridade_min_spin->setObjectName(QString::fromUtf8("popuaridade_min_spin"));
        popuaridade_min_spin->setMaximum(100);

        popularidade_min_layout->addWidget(popuaridade_min_spin);


        advanced->addLayout(popularidade_min_layout);

        popularidade_max_layout = new QVBoxLayout();
        popularidade_max_layout->setSpacing(6);
        popularidade_max_layout->setObjectName(QString::fromUtf8("popularidade_max_layout"));
        popularidade_max = new QLabel(widget);
        popularidade_max->setObjectName(QString::fromUtf8("popularidade_max"));

        popularidade_max_layout->addWidget(popularidade_max);

        popuaridade_max_spin = new QSpinBox(widget);
        popuaridade_max_spin->setObjectName(QString::fromUtf8("popuaridade_max_spin"));
        popuaridade_max_spin->setMaximum(100);
        popuaridade_max_spin->setValue(100);

        popularidade_max_layout->addWidget(popuaridade_max_spin);


        advanced->addLayout(popularidade_max_layout);


        busca_layout->addLayout(advanced);


        topbar->addLayout(busca_layout);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        username = new QLabel(widget);
        username->setObjectName(QString::fromUtf8("username"));
        username->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(username);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        login = new QPushButton(widget);
        login->setObjectName(QString::fromUtf8("login"));

        horizontalLayout->addWidget(login);

        registrar = new QPushButton(widget);
        registrar->setObjectName(QString::fromUtf8("registrar"));

        horizontalLayout->addWidget(registrar);

        logout = new QPushButton(widget);
        logout->setObjectName(QString::fromUtf8("logout"));

        horizontalLayout->addWidget(logout);


        verticalLayout->addLayout(horizontalLayout);

        error_message = new QLabel(widget);
        error_message->setObjectName(QString::fromUtf8("error_message"));
        error_message->setSizeIncrement(QSize(0, 0));
        error_message->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(error_message);


        topbar->addLayout(verticalLayout);


        tudo->addLayout(topbar);

        resultados = new QVBoxLayout();
        resultados->setSpacing(6);
        resultados->setObjectName(QString::fromUtf8("resultados"));

        tudo->addLayout(resultados);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        tudo->addItem(verticalSpacer);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1000, 21));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tipo_combo->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Hub", 0, QApplication::UnicodeUTF8));
        busca->setText(QApplication::translate("MainWindow", "Busca:", 0, QApplication::UnicodeUTF8));
        min_preco->setText(QApplication::translate("MainWindow", "Pre\303\247o Min.:", 0, QApplication::UnicodeUTF8));
        max_preco->setText(QApplication::translate("MainWindow", "Pre\303\247o Max.:", 0, QApplication::UnicodeUTF8));
        tipo->setText(QApplication::translate("MainWindow", "Tipo de Produto", 0, QApplication::UnicodeUTF8));
        tipo_combo->clear();
        tipo_combo->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Aluguel", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Venda", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Servi\303\247o", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Todos", 0, QApplication::UnicodeUTF8)
        );
        popularidade_min->setText(QApplication::translate("MainWindow", "Popularidade Min.:", 0, QApplication::UnicodeUTF8));
        popularidade_max->setText(QApplication::translate("MainWindow", "Popularidade Max.:", 0, QApplication::UnicodeUTF8));
        username->setText(QApplication::translate("MainWindow", "Fa\303\247a Login", 0, QApplication::UnicodeUTF8));
        login->setText(QApplication::translate("MainWindow", "Login", 0, QApplication::UnicodeUTF8));
        registrar->setText(QApplication::translate("MainWindow", "Registrar", 0, QApplication::UnicodeUTF8));
        logout->setText(QApplication::translate("MainWindow", "Logout", 0, QApplication::UnicodeUTF8));
        error_message->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
