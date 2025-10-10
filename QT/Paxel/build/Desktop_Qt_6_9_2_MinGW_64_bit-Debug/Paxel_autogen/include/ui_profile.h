/********************************************************************************
** Form generated from reading UI file 'profile.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROFILE_H
#define UI_PROFILE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Profile
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *ProfPic;
    QPushButton *Followers;
    QPushButton *Following;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *Home;
    QSpacerItem *horizontalSpacer_3;
    QLabel *UserName;
    QSpacerItem *horizontalSpacer;
    QPushButton *Logout;
    QSpacerItem *horizontalSpacer_2;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;

    void setupUi(QMainWindow *Profile)
    {
        if (Profile->objectName().isEmpty())
            Profile->setObjectName("Profile");
        Profile->resize(700, 618);
        centralwidget = new QWidget(Profile);
        centralwidget->setObjectName("centralwidget");
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName("gridLayout_2");
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        ProfPic = new QLabel(centralwidget);
        ProfPic->setObjectName("ProfPic");
        ProfPic->setStyleSheet(QString::fromUtf8("font: 20pt \"Bahnschrift\";"));
        ProfPic->setFrameShape(QFrame::Shape::Box);
        ProfPic->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_3->addWidget(ProfPic);

        Followers = new QPushButton(centralwidget);
        Followers->setObjectName("Followers");
        Followers->setStyleSheet(QString::fromUtf8("font: 20pt \"Bahnschrift\";"));

        horizontalLayout_3->addWidget(Followers);

        Following = new QPushButton(centralwidget);
        Following->setObjectName("Following");
        Following->setStyleSheet(QString::fromUtf8("font: 20pt \"Bahnschrift\";"));

        horizontalLayout_3->addWidget(Following);


        gridLayout_2->addLayout(horizontalLayout_3, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        Home = new QPushButton(centralwidget);
        Home->setObjectName("Home");
        Home->setMinimumSize(QSize(70, 30));
        Home->setStyleSheet(QString::fromUtf8("font: 20pt \"Bahnschrift\";"));

        horizontalLayout->addWidget(Home);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        UserName = new QLabel(centralwidget);
        UserName->setObjectName("UserName");
        UserName->setMinimumSize(QSize(200, 10));
        UserName->setMaximumSize(QSize(1000, 30));
        UserName->setStyleSheet(QString::fromUtf8("font: 20pt \"Bahnschrift\";"));
        UserName->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout->addWidget(UserName);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        Logout = new QPushButton(centralwidget);
        Logout->setObjectName("Logout");
        Logout->setMinimumSize(QSize(70, 30));
        Logout->setStyleSheet(QString::fromUtf8("font: 20pt \"Bahnschrift\";"));

        horizontalLayout->addWidget(Logout);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        gridLayout_2->addLayout(horizontalLayout, 0, 0, 1, 1);

        scrollArea = new QScrollArea(centralwidget);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setMaximumSize(QSize(16777215, 400));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 686, 398));
        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout_2->addWidget(scrollArea, 2, 0, 1, 1);

        Profile->setCentralWidget(centralwidget);

        retranslateUi(Profile);

        QMetaObject::connectSlotsByName(Profile);
    } // setupUi

    void retranslateUi(QMainWindow *Profile)
    {
        Profile->setWindowTitle(QCoreApplication::translate("Profile", "MainWindow", nullptr));
        ProfPic->setText(QCoreApplication::translate("Profile", "ProfPic", nullptr));
        Followers->setText(QCoreApplication::translate("Profile", "Followers", nullptr));
        Following->setText(QCoreApplication::translate("Profile", "Following", nullptr));
        Home->setText(QCoreApplication::translate("Profile", "Back", nullptr));
        UserName->setText(QCoreApplication::translate("Profile", "UserName", nullptr));
        Logout->setText(QCoreApplication::translate("Profile", "Logout", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Profile: public Ui_Profile {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROFILE_H
