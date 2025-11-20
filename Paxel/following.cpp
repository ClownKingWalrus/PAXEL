#include "following.h"
#include "ui_following.h"
#include "follow.h"
#include "followers.h"
#include "profile.h"
#include "ProfilePicture.h"
#include "../hdr/proc.h"
#include "../hdr/Utils.h"

#include <QScrollBar>
#include <QPushButton>
#include <QObject>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPixmap>
#include <qevent.h>
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
            QLabel* label = new QLabel();
            ui->UserName->setText(QString::fromStdString(u.first));
            label->setAlignment(Qt::AlignCenter);
            label->setMinimumSize(100,50);
            label->setFont(QFont("MS Sans Serif", 20));
        }
    }

    vector<pair<string, string>> followerVect;
    vector<pair<string, string>> followeeVect;
    followerVect = Utils::FollowerProfile(proc::ip, proc::user, proc::password, proc::db, userID);
    followeeVect = Utils::FolloweeProfile(proc::ip, proc::user, proc::password, proc::db, userID);

    vector<pair<string, string>> FolloweeList;
    vector<pair<string, string>> FollowingList;

    for (const auto& p : followerVect) {
        if (p.first == userID) {
            FollowingList.push_back(p);
        }
    }
    for (const auto& b : followeeVect) {
        if (b.first == userID) {
            FolloweeList.push_back(b);
        }
    }
    ui->Following_2->setText(QString::number(FollowingList.size()) + " Following");
    if(FolloweeList.size() != 1) {
        ui->Followers_2->setText(QString::number(FolloweeList.size()) + " Followers");
    }
    else {
        ui->Followers_2->setText(QString::number(FolloweeList.size()) + " Follower");
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
    resize(1000, 800);
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
        if(followerVect[i].first == userID){
            FollowingList.push_back(followeeVect[i]);
        }
    }
    for (const auto& followingprof : FollowingList ) {
        QHBoxLayout* ProfileBanner = CreateProfileBanner(followingprof.first, followingprof.second);
        ProfileLayout->addLayout(ProfileBanner);
    }
}

QHBoxLayout* Following::CreateProfileBanner(const string& userID, const string& username) {
    QHBoxLayout* bannerBox = new QHBoxLayout();
    QPushButton* IDfollowing = new QPushButton(QString::fromStdString(userID));
    QPushButton* Name = new QPushButton(QString::fromStdString(username));

    IDfollowing->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    Name->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    QPixmap pix = ProfilePicture::CreatePixMapFromSql(stoi(userID));
    if (!pix.isNull()) {
        QIcon icon(pix.scaled(64, 64, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        IDfollowing->setIcon(icon);
        IDfollowing->setIconSize(IDfollowing->size());
        IDfollowing->setText("");
        IDfollowing->setStyleSheet(
            "QPushButton {"
            "   color: rgba(0,0,0,0);"               /* hide text */
            "   border: none;"
            "   border-radius: 8px;"
            "   background-color: rgb(35, 242, 24);" /* button background */
            "   font-family: 'MS Sans Serif';"
            "   font-weight: bold;"
            "   text-align: center;"
            "}"
            "QPushButton:hover {"
            "   background-color: rgb(50, 200, 30);"  /* hover color */
            "}"
            );
    } else {
        pix = QPixmap(":/pimages/Profile_Picture/BlankProf.png");
        QIcon icon(pix.scaled(64, 64, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        IDfollowing->setIcon(icon);
        IDfollowing->setIconSize(IDfollowing->size());
        IDfollowing->setText("");
        IDfollowing->setStyleSheet(
            "QPushButton {"
            "   color: rgba(0,0,0,0);"               /* hide text */
            "   border: none;"
            "   border-radius: 8px;"
            "   background-color: rgb(35, 242, 24);" /* button background */
            "   font-family: 'MS Sans Serif';"
            "   font-weight: bold;"
            "   text-align: center;"
            "}"
            "QPushButton:hover {"
            "   background-color: rgb(50, 200, 30);"  /* hover color */
            "}"
            );
    }

    IDfollowing->setMinimumSize(100,100);
    IDfollowing->setFlat(true);
    IDfollowing->setFont(QFont("MS Sans Serif", 20));

    Name->setMinimumSize(100,100);
    Name->setFlat(true);
    Name->setFont(QFont("MS Sans Serif", 20));

    bannerBox->addWidget(IDfollowing, 1);
    bannerBox->addWidget(Name, 3);

    bannerBox->setContentsMargins(10, 5, 10, 5);
    bannerBox->setSpacing(15);

    Name->setStyleSheet(
        "QPushButton { background-color: rgb(8, 136, 245); color: black; font-family: MS Sans Serif;}"  // blue
        "border-radius: 8px;"
        );

    QPushButton::connect(Name, &QPushButton::clicked, this, [this, userID]() {
        onClicked(userID);
    });

    QPushButton::connect(IDfollowing, &QPushButton::clicked, this, [this, userID]() {
        onClicked(userID);
    });

    return bannerBox;
}


void Following::onClicked(string userID) {
    std::pair<std::string,int> userCred = Utils::SessionTokenCheck(proc::ip,proc::user, proc::password, proc::db, Utils::sessionID);
    if (userID != std::to_string(userCred.second)) {
        Follow *FollowProfile = new Follow(this, userID);
        FollowProfile->show();
    }
    else {
        Profile *UserProfile = new Profile(this);
        UserProfile->show();
    }
    this->hide();
}

void Following::Followers_2_clicked(string userID)
{
    Followers *FollowersList = new Followers(this, userID);
    this->hide();
    FollowersList->show();
}

void Following::on_Back_clicked()
{
    this->hide();
    if (parentWidget()) {
        parentWidget()->show();
    }
}

void Following::resizeEvent(QResizeEvent* event) {
    QMainWindow::resizeEvent(event);
    QSize newSize = event->size();

    // Access the width and height
    int newWidth = newSize.width();
    int newHeight = newSize.height();
}
