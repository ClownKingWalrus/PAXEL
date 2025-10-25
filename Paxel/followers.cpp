#include "followers.h"
#include "ui_followers.h"
#include "follow.h"
#include "following.h"
#include "profile.h"
#include "../hdr/proc.h"
#include "../hdr/Utils.h"

#include <QScrollBar>
#include <QPushButton>
#include <QObject>
#include <QHBoxLayout>
#include <QVBoxLayout>
using namespace std;

Followers::Followers(QWidget *parent, string userID)
    : QMainWindow(parent)
    , ui(new Ui::Followers)
{
    ui->setupUi(this);

    vector<pair<string, string>> userVect;
    userVect = Utils::UserID(proc::ip, proc::user, proc::password, proc::db);
    for (const auto& u : userVect) {
        if (u.second == userID) {
            ui->UserName->setText(QString::fromStdString(u.first));
        }
    }

    ui->Followers_2->setMinimumSize(100,50);
    ui->Following->setMinimumSize(100,50);
    ui->Back->setMinimumSize(15,10);

    ProfileLayout = new QVBoxLayout(ui->scrollAreaWidgetContents);
    ui->scrollAreaWidgetContents->setLayout(ProfileLayout);

    loadProfiles(proc::ip, proc::user, proc::password, proc::db, userID);
    connect(ui->Following, &QPushButton::clicked, this, [this, userID]() {
        Following_clicked(userID);
    });
    connect(ui->Back, &QPushButton::clicked, this, [this, userID]() {
        Back_clicked(userID);
    });
}

Followers::~Followers()
{
    delete ui;
}

void Followers::loadProfiles(const string& host, const string& user, const string& password, const string& dbName, string userID) {

    vector<pair<string, string>> followeeVect;
    vector<pair<string, string>> followerVect;
    followeeVect = Utils::FolloweeProfile(proc::ip, proc::user, proc::password, proc::db, userID);
    followerVect = Utils::FollowerProfile(proc::ip, proc::user, proc::password, proc::db, userID);

    vector<pair<string,string>> FollowerList;
    for (int i = 0; i < followerVect.size(); i++) {
        if(followeeVect[i].second == userID){
            FollowerList.push_back(followerVect[i]);
        }
    }
    for (const auto& followerprof : FollowerList) {
        QHBoxLayout* ProfileBanner = CreateProfileBanner(followerprof.second, followerprof.first);
        ProfileLayout->addLayout(ProfileBanner);
    }
}

QHBoxLayout* Followers::CreateProfileBanner(const string& userID, const string& username) {
    QHBoxLayout* bannerBox = new QHBoxLayout();
    QPushButton* IDfollower = new QPushButton(QString::fromStdString(userID));
    QPushButton* Name = new QPushButton(QString::fromStdString(username));

    IDfollower->setMinimumSize(100,100);
    IDfollower->setFlat(true);

    Name->setMinimumSize(100,100);
    Name->setFlat(true);

    bannerBox->addWidget(IDfollower, 1);
    bannerBox->addWidget(Name, 3);

    bannerBox->setContentsMargins(10, 5, 10, 5);
    bannerBox->setSpacing(15);
    QPushButton::connect(Name, &QPushButton::clicked, this, [this, userID]() {
        onClicked(userID);
    });
    return bannerBox;
}

void Followers::onClicked(string userID) {
    if (userID != Utils::GetUserID()) {
        Follow *FollowerProfile = new Follow(this, userID);
        FollowerProfile->show();
    }
    else {
        Profile *UserProfile = new Profile;
        UserProfile->show();
        }
    hide();
}

void Followers::Following_clicked(string userID)
{
    Following *FollowingList = new Following(this, userID);
    hide();
    FollowingList->show();
}


void Followers::Back_clicked(string userID)
{
    if (userID == Utils::GetUserID()) {
    Profile *UserProfile = new Profile(this, userID);
    UserProfile->show();
    }
    else {
        Follow *OtherProfile = new Follow(this, userID);
        OtherProfile->show();
    }
    hide();
}

