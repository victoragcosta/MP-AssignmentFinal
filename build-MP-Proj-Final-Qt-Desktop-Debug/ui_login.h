/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

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
            login->setObjectName(QString::fromUtf8("login"));
        login->resize(639, 272);
        widget = new QWidget(login);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 0, 641, 271));
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setSizeConstraint(QLayout::SetMinimumSize);
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        error_message = new QLabel(widget);
        error_message->setObjectName(QString::fromUtf8("error_message"));
        error_message->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(error_message);

        username_label = new QLabel(widget);
        username_label->setObjectName(QString::fromUtf8("username_label"));

        verticalLayout->addWidget(username_label);

        username_edit = new QLineEdit(widget);
        username_edit->setObjectName(QString::fromUtf8("username_edit"));
        username_edit->setMinimumSize(QSize(451, 0));

        verticalLayout->addWidget(username_edit);

        password_label = new QLabel(widget);
        password_label->setObjectName(QString::fromUtf8("password_label"));

        verticalLayout->addWidget(password_label);

        password_edit = new QLineEdit(widget);
        password_edit->setObjectName(QString::fromUtf8("password_edit"));
        password_edit->setEnabled(true);
        password_edit->setMinimumSize(QSize(133, 0));
        password_edit->setAcceptDrops(true);
        password_edit->setInputMethodHints(Qt::ImhHiddenText|Qt::ImhNoAutoUppercase|Qt::ImhNoPredictiveText);
        password_edit->setFrame(true);
        password_edit->setEchoMode(QLineEdit::Password);

        verticalLayout->addWidget(password_edit);

        submit = new QPushButton(widget);
        submit->setObjectName(QString::fromUtf8("submit"));

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
        login->setWindowTitle(QApplication::translate("login", "Form", 0, QApplication::UnicodeUTF8));
        error_message->setText(QString());
        username_label->setText(QApplication::translate("login", "Username:", 0, QApplication::UnicodeUTF8));
        password_label->setText(QApplication::translate("login", "Password:", 0, QApplication::UnicodeUTF8));
        submit->setText(QApplication::translate("login", "Login", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class login: public Ui_login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
