#include "profile.h"
#include "ui_profile.h"
#include "mainwindow.h"
#include <QMessageBox>
#include "homescreen.h"
#include "interestselect.h"
#include "createboardorthread.h"
Profile::Profile(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::Profile)
{
    ui->setupUi(this);
}

Profile::~Profile()
{
    delete ui;
}

void Profile::on_Logout_clicked()
{
    MainWindow* MainWindowMainWindow = new MainWindow;
    QMessageBox::StandardButton reply;

    reply = QMessageBox::question(this,"Logout","Do You Want to Logout",QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        hide();
        MainWindowMainWindow->show();
    }
}


void Profile::on_Home_clicked()
{
    HomeScreen* HomescreenHomescreen = new HomeScreen;
    hide();
    HomescreenHomescreen->show();
}


void Profile::on_AddInterestsProfile_clicked()
{
    interestselect* InterestScreen = new interestselect;
    InterestScreen->show();
}

