/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *widget;
    QVBoxLayout *verticalLayout_3;
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
    QLabel *tipo_combo;
    QComboBox *tipo;
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
    QListWidget *resultados_busca;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1000, 600);
        QIcon icon;
        icon.addFile(QStringLiteral("img_carrinho.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(10, 0, 981, 571));
        verticalLayout_3 = new QVBoxLayout(widget);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        topbar = new QHBoxLayout();
        topbar->setSpacing(6);
        topbar->setObjectName(QStringLiteral("topbar"));
        busca_layout = new QVBoxLayout();
        busca_layout->setSpacing(6);
        busca_layout->setObjectName(QStringLiteral("busca_layout"));
        busca = new QLabel(widget);
        busca->setObjectName(QStringLiteral("busca"));

        busca_layout->addWidget(busca);

        busca_edit = new QLineEdit(widget);
        busca_edit->setObjectName(QStringLiteral("busca_edit"));
        busca_edit->setEnabled(false);

        busca_layout->addWidget(busca_edit);

        advanced = new QHBoxLayout();
        advanced->setSpacing(6);
        advanced->setObjectName(QStringLiteral("advanced"));
        min_preco_layout = new QVBoxLayout();
        min_preco_layout->setSpacing(6);
        min_preco_layout->setObjectName(QStringLiteral("min_preco_layout"));
        min_preco = new QLabel(widget);
        min_preco->setObjectName(QStringLiteral("min_preco"));

        min_preco_layout->addWidget(min_preco);

        min_preco_spin = new QDoubleSpinBox(widget);
        min_preco_spin->setObjectName(QStringLiteral("min_preco_spin"));
        min_preco_spin->setMaximum(1e+6);

        min_preco_layout->addWidget(min_preco_spin);


        advanced->addLayout(min_preco_layout);

        max_preco_layout = new QVBoxLayout();
        max_preco_layout->setSpacing(6);
        max_preco_layout->setObjectName(QStringLiteral("max_preco_layout"));
        max_preco = new QLabel(widget);
        max_preco->setObjectName(QStringLiteral("max_preco"));

        max_preco_layout->addWidget(max_preco);

        max_preco_spin = new QDoubleSpinBox(widget);
        max_preco_spin->setObjectName(QStringLiteral("max_preco_spin"));
        max_preco_spin->setMaximum(1e+6);
        max_preco_spin->setValue(1e+6);

        max_preco_layout->addWidget(max_preco_spin);


        advanced->addLayout(max_preco_layout);

        tipo_layout = new QVBoxLayout();
        tipo_layout->setSpacing(6);
        tipo_layout->setObjectName(QStringLiteral("tipo_layout"));
        tipo_combo = new QLabel(widget);
        tipo_combo->setObjectName(QStringLiteral("tipo_combo"));

        tipo_layout->addWidget(tipo_combo);

        tipo = new QComboBox(widget);
        tipo->setObjectName(QStringLiteral("tipo"));

        tipo_layout->addWidget(tipo);


        advanced->addLayout(tipo_layout);

        popularidade_min_layout = new QVBoxLayout();
        popularidade_min_layout->setSpacing(6);
        popularidade_min_layout->setObjectName(QStringLiteral("popularidade_min_layout"));
        popularidade_min = new QLabel(widget);
        popularidade_min->setObjectName(QStringLiteral("popularidade_min"));

        popularidade_min_layout->addWidget(popularidade_min);

        popuaridade_min_spin = new QSpinBox(widget);
        popuaridade_min_spin->setObjectName(QStringLiteral("popuaridade_min_spin"));
        popuaridade_min_spin->setMaximum(100);

        popularidade_min_layout->addWidget(popuaridade_min_spin);


        advanced->addLayout(popularidade_min_layout);

        popularidade_max_layout = new QVBoxLayout();
        popularidade_max_layout->setSpacing(6);
        popularidade_max_layout->setObjectName(QStringLiteral("popularidade_max_layout"));
        popularidade_max = new QLabel(widget);
        popularidade_max->setObjectName(QStringLiteral("popularidade_max"));

        popularidade_max_layout->addWidget(popularidade_max);

        popuaridade_max_spin = new QSpinBox(widget);
        popuaridade_max_spin->setObjectName(QStringLiteral("popuaridade_max_spin"));
        popuaridade_max_spin->setMaximum(100);
        popuaridade_max_spin->setValue(100);

        popularidade_max_layout->addWidget(popuaridade_max_spin);


        advanced->addLayout(popularidade_max_layout);


        busca_layout->addLayout(advanced);


        topbar->addLayout(busca_layout);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        username = new QLabel(widget);
        username->setObjectName(QStringLiteral("username"));
        username->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(username);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        login = new QPushButton(widget);
        login->setObjectName(QStringLiteral("login"));

        horizontalLayout->addWidget(login);

        registrar = new QPushButton(widget);
        registrar->setObjectName(QStringLiteral("registrar"));

        horizontalLayout->addWidget(registrar);

        logout = new QPushButton(widget);
        logout->setObjectName(QStringLiteral("logout"));

        horizontalLayout->addWidget(logout);


        verticalLayout->addLayout(horizontalLayout);

        error_message = new QLabel(widget);
        error_message->setObjectName(QStringLiteral("error_message"));
        error_message->setSizeIncrement(QSize(0, 0));
        error_message->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(error_message);


        topbar->addLayout(verticalLayout);


        verticalLayout_3->addLayout(topbar);

        resultados_busca = new QListWidget(widget);
        resultados_busca->setObjectName(QStringLiteral("resultados_busca"));

        verticalLayout_3->addWidget(resultados_busca);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1000, 21));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Hub", Q_NULLPTR));
        busca->setText(QApplication::translate("MainWindow", "Busca:", Q_NULLPTR));
        min_preco->setText(QApplication::translate("MainWindow", "Pre\303\247o Min.:", Q_NULLPTR));
        max_preco->setText(QApplication::translate("MainWindow", "Pre\303\247o Max.:", Q_NULLPTR));
        tipo_combo->setText(QApplication::translate("MainWindow", "Tipo de Produto", Q_NULLPTR));
        tipo->clear();
        tipo->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Aluguel", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Venda", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Servi\303\247o", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Todos", Q_NULLPTR)
        );
        popularidade_min->setText(QApplication::translate("MainWindow", "Popularidade Min.:", Q_NULLPTR));
        popularidade_max->setText(QApplication::translate("MainWindow", "Popularidade Max.:", Q_NULLPTR));
        username->setText(QApplication::translate("MainWindow", "Fa\303\247a Login", Q_NULLPTR));
        login->setText(QApplication::translate("MainWindow", "Login", Q_NULLPTR));
        registrar->setText(QApplication::translate("MainWindow", "Registrar", Q_NULLPTR));
        logout->setText(QApplication::translate("MainWindow", "Logout", Q_NULLPTR));
        error_message->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
