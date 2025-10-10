/********************************************************************************
** Form generated from reading UI file 'homescreen.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HOMESCREEN_H
#define UI_HOMESCREEN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HomeScreen
{
public:
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *Add;
    QSpacerItem *horizontalSpacer_2;
    QLabel *Clock;
    QSpacerItem *horizontalSpacer;
    QPushButton *Profile;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents_3;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QPushButton *pushButton;

    void setupUi(QWidget *HomeScreen)
    {
        if (HomeScreen->objectName().isEmpty())
            HomeScreen->setObjectName("HomeScreen");
        HomeScreen->resize(683, 657);
        gridLayout_3 = new QGridLayout(HomeScreen);
        gridLayout_3->setObjectName("gridLayout_3");
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        Add = new QPushButton(HomeScreen);
        Add->setObjectName("Add");
        Add->setMinimumSize(QSize(80, 60));
        Add->setStyleSheet(QString::fromUtf8("font: 20pt \"Bahnschrift\";"));

        horizontalLayout_3->addWidget(Add);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        Clock = new QLabel(HomeScreen);
        Clock->setObjectName("Clock");
        Clock->setMinimumSize(QSize(200, 0));
        Clock->setMaximumSize(QSize(300, 16777215));
        Clock->setStyleSheet(QString::fromUtf8("font: 20pt \"Bahnschrift\";"));
        Clock->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_3->addWidget(Clock);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        Profile = new QPushButton(HomeScreen);
        Profile->setObjectName("Profile");
        Profile->setMinimumSize(QSize(80, 60));
        Profile->setStyleSheet(QString::fromUtf8("font: 20pt \"Bahnschrift\";"));

        horizontalLayout_3->addWidget(Profile);


        gridLayout_3->addLayout(horizontalLayout_3, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label_2 = new QLabel(HomeScreen);
        label_2->setObjectName("label_2");
        label_2->setMinimumSize(QSize(60, 0));

        horizontalLayout->addWidget(label_2);

        scrollArea = new QScrollArea(HomeScreen);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents_3 = new QWidget();
        scrollAreaWidgetContents_3->setObjectName("scrollAreaWidgetContents_3");
        scrollAreaWidgetContents_3->setGeometry(QRect(0, 0, 527, 575));
        scrollArea->setWidget(scrollAreaWidgetContents_3);

        horizontalLayout->addWidget(scrollArea);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(HomeScreen);
        label->setObjectName("label");
        label->setMinimumSize(QSize(0, 200));
        label->setMaximumSize(QSize(300, 16777215));

        verticalLayout->addWidget(label);

        pushButton = new QPushButton(HomeScreen);
        pushButton->setObjectName("pushButton");
        pushButton->setMaximumSize(QSize(16777215, 50));
        pushButton->setStyleSheet(QString::fromUtf8("font: 20pt \"Bahnschrift\";"));

        verticalLayout->addWidget(pushButton);


        horizontalLayout->addLayout(verticalLayout);


        gridLayout_3->addLayout(horizontalLayout, 1, 0, 1, 1);


        retranslateUi(HomeScreen);

        QMetaObject::connectSlotsByName(HomeScreen);
    } // setupUi

    void retranslateUi(QWidget *HomeScreen)
    {
        HomeScreen->setWindowTitle(QCoreApplication::translate("HomeScreen", "Form", nullptr));
        Add->setText(QCoreApplication::translate("HomeScreen", "Add", nullptr));
        Clock->setText(QCoreApplication::translate("HomeScreen", "00:00 a.m.", nullptr));
        Profile->setText(QCoreApplication::translate("HomeScreen", "Profile", nullptr));
        label_2->setText(QCoreApplication::translate("HomeScreen", "TextLabel", nullptr));
        label->setText(QCoreApplication::translate("HomeScreen", "TextLabel", nullptr));
        pushButton->setText(QCoreApplication::translate("HomeScreen", "Boards", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HomeScreen: public Ui_HomeScreen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HOMESCREEN_H
