/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_login
{
public:
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout;
    QLabel *error_message;
    QLabel *username_label;
    QLineEdit *username_edit;
    QLabel *password_label;
    QLineEdit *password_edit;
    QPushButton *submit;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *login)
    {
        if (login->objectName().isEmpty())
            login->setObjectName(QStringLiteral("login"));
        login->resize(639, 272);
        widget = new QWidget(login);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(0, 0, 641, 271));
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setSizeConstraint(QLayout::SetMinimumSize);
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        error_message = new QLabel(widget);
        error_message->setObjectName(QStringLiteral("error_message"));
        error_message->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(error_message);

        username_label = new QLabel(widget);
        username_label->setObjectName(QStringLiteral("username_label"));

        verticalLayout->addWidget(username_label);

        username_edit = new QLineEdit(widget);
        username_edit->setObjectName(QStringLiteral("username_edit"));
        username_edit->setMinimumSize(QSize(451, 0));

        verticalLayout->addWidget(username_edit);

        password_label = new QLabel(widget);
        password_label->setObjectName(QStringLiteral("password_label"));

        verticalLayout->addWidget(password_label);

        password_edit = new QLineEdit(widget);
        password_edit->setObjectName(QStringLiteral("password_edit"));
        password_edit->setEnabled(true);
        password_edit->setMinimumSize(QSize(133, 0));
        password_edit->setAcceptDrops(true);
        password_edit->setInputMethodHints(Qt::ImhHiddenText|Qt::ImhNoAutoUppercase|Qt::ImhNoPredictiveText|Qt::ImhSensitiveData);
        password_edit->setFrame(true);
        password_edit->setEchoMode(QLineEdit::Password);

        verticalLayout->addWidget(password_edit);

        submit = new QPushButton(widget);
        submit->setObjectName(QStringLiteral("submit"));

        verticalLayout->addWidget(submit);


        horizontalLayout->addLayout(verticalLayout);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);


        retranslateUi(login);

        QMetaObject::connectSlotsByName(login);
    } // setupUi

    void retranslateUi(QWidget *login)
    {
        login->setWindowTitle(QApplication::translate("login", "Form", Q_NULLPTR));
        error_message->setText(QString());
        username_label->setText(QApplication::translate("login", "Username:", Q_NULLPTR));
        password_label->setText(QApplication::translate("login", "Password:", Q_NULLPTR));
        submit->setText(QApplication::translate("login", "Login", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class login: public Ui_login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
