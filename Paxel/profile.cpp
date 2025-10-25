#include "profile.h"
#include "ui_profile.h"
#include "mainwindow.h"
#include "homescreen.h"
#include "interestselect.h"
#include "createboardorthread.h"
#include "followers.h"
#include "following.h"
#include "../hdr/proc.h"
#include "../hdr/Utils.h"

#include <QString>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
Profile::Profile(QWidget *parent, string userID)
    : QMainWindow(parent)
    , ui(new Ui::Profile)
{
    ui->setupUi(this);

    vector<pair<string, string>> userVect;
    userVect = Utils::UserID(proc::ip, proc::user, proc::password, proc::db);
    for (const auto& u : userVect) {
        if (u.second == Utils::GetUserID()) {
            ui->UserName->setText(QString::fromStdString(u.first));
        }
    }

    vector<pair<string, string>> followerVect;
    vector<pair<string, string>> followeeVect;
    followerVect = Utils::FollowerProfile(proc::ip, proc::user, proc::password, proc::db, userID);
    followeeVect = Utils::FolloweeProfile(proc::ip, proc::user, proc::password, proc::db, userID);

    vector<pair<string, string>> FolloweeList;
    vector<pair<string, string>> FollowingList;

    for (const auto& p : followerVect) {
        if (p.second == Utils::GetUserID()) {
            FollowingList.push_back(p);
        }
    }
    for (const auto& p : followeeVect) {
        if (p.second == Utils::GetUserID()) {
            FolloweeList.push_back(p);
        }
    }

    ui->Following->setText(QString::number(FollowingList.size()) + " Following");
    if(FolloweeList.size() != 1) {
        ui->Followers->setText(QString::number(FolloweeList.size()) + " Followers");
    }
    else {
        ui->Followers->setText(QString::number(FolloweeList.size()) + " Follower");
    }

    connect(ui->Following, &QPushButton::clicked, this, [this, userID]() {
        Following_clicked(Utils::GetUserID());
    });
    connect(ui->Followers, &QPushButton::clicked, this, [this, userID]() {
        Followers_clicked(Utils::GetUserID());
    });
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

void Profile::Back_clicked()
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

void Profile::Followers_clicked(string userID)
{
    Followers *FollowersList = new Followers(this, userID);
    hide();
    FollowersList -> show();
}

void Profile::Following_clicked(string userID)
{
    Following *FollowingList = new Following(this, userID);
    hide();
    FollowingList -> show();
}
