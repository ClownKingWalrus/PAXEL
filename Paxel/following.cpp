#include "following.h"
#include "ui_following.h"
#include "follow.h"
#include "followers.h"
#include "profile.h"
#include "../hdr/proc.h"
#include "../hdr/Utils.h"

#include <QScrollBar>
#include <QPushButton>
#include <QObject>
#include <QHBoxLayout>
#include <QVBoxLayout>
using namespace std;

Following::Following(QWidget *parent, string userID)
    : QMainWindow(parent)
    , ui(new Ui::Following)
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
    ui->Following_2->setMinimumSize(100,50);
    ui->Back->setMinimumSize(15,10);

    ProfileLayout = new QVBoxLayout(ui->scrollAreaWidgetContents);
    ui->scrollAreaWidgetContents->setLayout(ProfileLayout);

    loadProfiles(proc::ip, proc::user, proc::password, proc::db, userID);
    connect(ui->Followers_2, &QPushButton::clicked, this, [this, userID]() {
        Followers_2_clicked(userID);
    });
    connect(ui->Back, &QPushButton::clicked, this, [this, userID]() {
        Back_clicked(userID);
    });
}

Following::~Following()
{
    delete ui;
}

void Following::loadProfiles(const string& host, const string& user, const string& password, const string& dbName, string userID){

    vector<pair<string, string>> followeeVect;
    vector<pair<string, string>> followerVect;
    followeeVect = Utils::FolloweeProfile(proc::ip, proc::user, proc::password, proc::db, userID);
    followerVect = Utils::FollowerProfile(proc::ip, proc::user, proc::password, proc::db, userID);

    vector<pair<string,string>> FollowingList;
    for (int i = 0; i < followeeVect.size(); i++) {
        if(followerVect[i].second == userID){
            FollowingList.push_back(followeeVect[i]);
        }
    }
    for (const auto& followingprof : FollowingList ) {
        QHBoxLayout* ProfileBanner = CreateProfileBanner(followingprof.second, followingprof.first);
        ProfileLayout->addLayout(ProfileBanner);
    }
}

QHBoxLayout* Following::CreateProfileBanner(const string& userID, const string& username) {
    QHBoxLayout* bannerBox = new QHBoxLayout();
    QPushButton* IDfollowing = new QPushButton(QString::fromStdString(userID));
    QPushButton* Name = new QPushButton(QString::fromStdString(username));

    IDfollowing->setMinimumSize(100,100);
    IDfollowing->setFlat(true);

    Name->setMinimumSize(100,100);
    Name->setFlat(true);

    bannerBox->addWidget(IDfollowing, 1);
    bannerBox->addWidget(Name, 3);

    bannerBox->setContentsMargins(10, 5, 10, 5);
    bannerBox->setSpacing(15);

    QPushButton::connect(Name, &QPushButton::clicked, this, [this, userID]() {
        onClicked(userID);
    });
    return bannerBox;
}


void Following::onClicked(string userID) {
    std::pair<std::string,int> userCred = Utils::SessionTokenCheck(proc::ip,proc::user, proc::password, proc::ip, Utils::sessionID);
    if (userID != std::to_string(userCred.second)) {
        Follow *FollowProfile = new Follow(this, userID);
        FollowProfile->show();
    }
    else {
        Profile *UserProfile = new Profile;
        UserProfile->show();
    }
    hide();
}

void Following::Followers_2_clicked(string userID)
{
    Followers *FollowersList = new Followers(this, userID);
    hide();
    FollowersList->show();
}

void Following::Back_clicked(string userID)
{
    std::pair<std::string,int> userCred = Utils::SessionTokenCheck(proc::ip,proc::user, proc::password, proc::ip, Utils::sessionID);
    if (userID == std::to_string(userCred.second)) {
        Profile *UserProfile = new Profile(this, userID);
        UserProfile->show();
    }
    else {
        Follow *OtherProfile = new Follow(this, userID);
        OtherProfile->show();
    }
    hide();
}
