/********************************************************************************
** Form generated from reading UI file 'GUI_kursach.ui'
**
** Created by: Qt User Interface Compiler version 5.12.10
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUI_KURSACH_H
#define UI_GUI_KURSACH_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GUI_kursachClass
{
public:
    QWidget *centralWidget;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *NickLine;
    QPushButton *ButtonNick;
    QTextEdit *textEdit;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *MessageLine;
    QPushButton *ButtonMessage;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *GUI_kursachClass)
    {
        if (GUI_kursachClass->objectName().isEmpty())
            GUI_kursachClass->setObjectName(QString::fromUtf8("GUI_kursachClass"));
        GUI_kursachClass->resize(641, 400);
        centralWidget = new QWidget(GUI_kursachClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(60, 30, 491, 256));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        NickLine = new QLineEdit(widget);
        NickLine->setObjectName(QString::fromUtf8("NickLine"));

        horizontalLayout->addWidget(NickLine);

        ButtonNick = new QPushButton(widget);
        ButtonNick->setObjectName(QString::fromUtf8("ButtonNick"));

        horizontalLayout->addWidget(ButtonNick);


        verticalLayout->addLayout(horizontalLayout);

        textEdit = new QTextEdit(widget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));

        verticalLayout->addWidget(textEdit);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        MessageLine = new QLineEdit(widget);
        MessageLine->setObjectName(QString::fromUtf8("MessageLine"));

        horizontalLayout_2->addWidget(MessageLine);

        ButtonMessage = new QPushButton(widget);
        ButtonMessage->setObjectName(QString::fromUtf8("ButtonMessage"));

        horizontalLayout_2->addWidget(ButtonMessage);


        verticalLayout->addLayout(horizontalLayout_2);

        GUI_kursachClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(GUI_kursachClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 641, 21));
        GUI_kursachClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(GUI_kursachClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        GUI_kursachClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(GUI_kursachClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        GUI_kursachClass->setStatusBar(statusBar);

        retranslateUi(GUI_kursachClass);
        QObject::connect(ButtonMessage, SIGNAL(clicked()), GUI_kursachClass, SLOT(SendMessage()));
        QObject::connect(ButtonNick, SIGNAL(clicked()), GUI_kursachClass, SLOT(SendNickname()));

        QMetaObject::connectSlotsByName(GUI_kursachClass);
    } // setupUi

    void retranslateUi(QMainWindow *GUI_kursachClass)
    {
        GUI_kursachClass->setWindowTitle(QApplication::translate("GUI_kursachClass", "GUI_kursach", nullptr));
        label->setText(QApplication::translate("GUI_kursachClass", "nickname", nullptr));
        ButtonNick->setText(QApplication::translate("GUI_kursachClass", "\320\236\321\202\320\277\321\200\320\260\320\262\320\270\321\202\321\214", nullptr));
        label_2->setText(QApplication::translate("GUI_kursachClass", "\320\241\320\276\320\276\320\261\321\211\320\265\320\275\320\270\320\265", nullptr));
        ButtonMessage->setText(QApplication::translate("GUI_kursachClass", "\320\236\321\202\320\277\321\200\320\260\320\262\320\270\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GUI_kursachClass: public Ui_GUI_kursachClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI_KURSACH_H
