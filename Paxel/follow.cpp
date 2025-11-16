#include "follow.h"
#include "ui_follow.h"
#include "followers.h"
#include "following.h"
#include "../hdr/proc.h"
#include "../hdr/Utils.h"

#include <QPushButton>
#include <QMessageBox>
#include <QString>
using namespace std;

Follow::Follow(QWidget *parent, string userID)
    : QMainWindow(parent)
    , ui(new Ui::Follow)
{
    ui->setupUi(this);

    vector<pair<string, string>> userVect;
    userVect = Utils::UserID(proc::ip, proc::user, proc::password, proc::db);
    for (const auto& u : userVect) {
        if (u.second == userID) {
            ui->UserName->setText(QString::fromStdString(u.first));
        }
    }

    vector<pair<string, string>> followerVect;
    vector<pair<string, string>> followeeVect;
    followerVect = Utils::FollowerProfile(proc::ip, proc::user, proc::password, proc::db, userID);
    followeeVect = Utils::FolloweeProfile(proc::ip, proc::user, proc::password, proc::db, userID);

    vector<pair<string, string>> FolloweeList;
    vector<pair<string, string>> FollowingList;

    std::pair<std::string,int> userCred = Utils::SessionTokenCheck(proc::ip,proc::user, proc::password, proc::ip, Utils::sessionID);

    for (const auto& p : followerVect) {
        if (p.second == userID) {
            FollowingList.push_back(p);
        }
    }
    for (const auto& b : followeeVect) {
        if (b.second == userID) {
            FolloweeList.push_back(b);
        }
    }
    for (const auto& f : FolloweeList) {
        if (f.second != std::to_string(userCred.second)) {
            ui->FollowButton->setText("- Unfollow");
        }
        else {
            ui->FollowButton->setText("+ Follow");
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
        Following_clicked(userID);
    });
    connect(ui->Followers, &QPushButton::clicked, this, [this, userID]() {
        Followers_clicked(userID);
    });
    connect(ui->FollowButton, &QPushButton::clicked, this, [this, userID, userCred]() {
        FollowButton_clicked(userID, std::to_string(userCred.second));
    });

}
Follow::~Follow()
{
    delete ui;
}

void Follow::FollowButton_clicked(string userID, string userID2)
{
    QString currentText = ui->FollowButton->text();
    if(currentText == "+ Follow")
    {
        Utils::UserFollow(proc::ip, proc::user, proc::password, proc::db, userID);
        ui->FollowButton->setText("- Unfollow");
    }
    else if (currentText == "- Unfollow")
    {
        QMessageBox::StandardButton reply = QMessageBox::question(this,"Unfollow","Do You Want to Unfollow?", QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            Utils::UserFollow(proc::ip, proc::user, proc::password, proc::db, userID);
            ui->FollowButton->setText("+ Follow");
        }
    }
}

void Follow::Followers_clicked(string userID)
{
    Followers *FollowerList = new Followers(this, userID);
    hide();
    FollowerList -> show();
}

void Follow::Following_clicked(string userID)
{
    Following *FollowingList = new Following(this, userID);
    hide();
    FollowingList -> show();
}
