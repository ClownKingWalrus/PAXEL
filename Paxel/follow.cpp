#include "follow.h"
#include "ui_follow.h"
#include "followers.h"
#include "following.h"
#include "../hdr/proc.h"
#include "../hdr/Utils.h"

#include <QPushButton>
#include <QMessageBox>
#include <QString>
#include <qevent.h>
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

    ui->FollowButton->setFont(QFont("MS Sans Serif", 16, QFont::Bold));
    ui->FollowButton->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    ui->FollowButton->setMinimumSize(QSize(20, 30));

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

    for (int i = 0; i < followerVect.size(); i++){
        if ((followerVect[i].second == (std::to_string(userCred.second)) && (followeeVect[i].second == userID))) {
            ui->FollowButton->setText("- Unfollow");
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
    connect(ui->FollowButton, &QPushButton::clicked, this, [this, userID]() {
        FollowButton_clicked(userID);
    });
    resize(1000, 800);

}
Follow::~Follow()
{
    delete ui;
}

void Follow::FollowButton_clicked(string userID)
{
    QString currentText = ui->FollowButton->text();
    if(currentText == "+ Follow")
    {
        Utils::UserFollow(proc::ip, proc::user, proc::password, proc::db, userID);
        ui -> FollowButton -> setText("- Unfollow");
        ui -> FollowButton -> setStyleSheet("background-color: rgb(48, 143, 145);");
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

void Follow::resizeEvent(QResizeEvent* event) {
    QMainWindow::resizeEvent(event);
    QSize newSize = event->size();

    // Access the width and height
    int newWidth = newSize.width();
    int newHeight = newSize.height();
}
