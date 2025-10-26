#include "profile.h"
#include "ui_profile.h"
#include "mainwindow.h"
#include "homescreen.h"
#include "followers.h"
#include "follow.h"
#include <QString>
#include <QMessageBox>
Profile::Profile(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Profile)
{
    ui->setupUi(this);
    extern int followercount;
    QString FollowingTxt = ui->Following->text();

    ui->Following->setText(QString::number(followercount) + " Following");
}

Profile::~Profile()
{
    delete ui;
}

void Profile::on_Logout_clicked()
{
    MainWindow *MainWindowMainWindow = new MainWindow;
    QMessageBox::StandardButton reply;

    reply = QMessageBox::question(this,"Logout","Do You Want to Logout",QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        hide();
        MainWindowMainWindow->show();
    }
}

void Profile::on_Back_clicked()
{
    HomeScreen *HomescreenHomescreen = new HomeScreen;
    hide();
    HomescreenHomescreen->show();
}

void Profile::on_Followers_clicked()
{
    Followers *FriendsFriends = new Followers;
    hide();
    FriendsFriends -> show();
}

void Profile::on_Following_clicked()
{
    Followers *FriendsFriends = new Followers;
    hide();
    FriendsFriends -> show();
}
