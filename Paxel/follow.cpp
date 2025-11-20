#include "follow.h"
#include "ui_follow.h"
#include "followers.h"
#include "following.h"
#include "ProfilePicture.h"
#include "../hdr/proc.h"
#include "../hdr/Utils.h"

#include <QPushButton>
#include <QMessageBox>
#include <QString>
#include <QPixmap>
#include <QPainter>
#include <qevent.h>
using namespace std;

Follow::Follow(QWidget *parent, string userID)
    : QMainWindow(parent)
    , ui(new Ui::Follow)
{
    ui->setupUi(this);

    QPixmap pix = ProfilePicture::CreatePixMapFromSql(stoi(userID));
    if (!pix.isNull()) {
        this->ui->ProfPic->setPixmap(pix.scaled(300, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    } else {
        pix = QPixmap(":/pimages/Profile_Picture/BlankProf.png");
        this->ui->ProfPic->setPixmap(pix.scaled(300, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }

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
    ui->FollowButton->setStyleSheet(
        "QPushButton {"
        "   color: rgba(0,0,0);"
        "   border: none;"
        "   border-radius: 8px;"
        "   background-color: rgb(0, 170, 245);"
        "   font-family: 'MS Sans Serif';"
        "   font-weight: bold;"
        "   text-align: center;"
        "}"
        "QPushButton:hover {"
        "   background-color: rgb(10, 180, 255);"
        "}"
        );
    ui->blockButton->setStyleSheet(
        "QPushButton {"
        "   color: rgba(255, 255, 255);"
        "   border: none;"
        "   border-radius: 8px;"
        "   background-color: rgb(139, 0, 0);"
        "   font-family: 'MS Sans Serif';"
        "   font-weight: bold;"
        "   text-align: center;"
        "}"
        "QPushButton:hover {"
        "   background-color: rgb(178, 34, 34);"
        "}"
        );

    ui->FollowButton->setFont(QFont("MS Sans Serif", 16, QFont::Bold));
    ui->FollowButton->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    ui->FollowButton->setMinimumSize(QSize(20, 30));
    ui->FollowButton->setStyleSheet(
        "QPushButton {"
        "   color: rgba(0,0,0);"
        "   border: none;"
        "   border-radius: 8px;"
        "   background-color: rgb(0, 170, 245);"
        "   font-family: 'MS Sans Serif';"
        "   font-weight: bold;"
        "   text-align: center;"
        "}"
        "QPushButton:hover {"
        "   background-color: rgb(10, 180, 255);"
        "}"
        );

    ui->FollowButton->setFont(QFont("MS Sans Serif", 16, QFont::Bold));
    ui->FollowButton->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    ui->FollowButton->setMinimumSize(QSize(20, 30));

    vector<pair<string, string>> followerVect;
    vector<pair<string, string>> followeeVect;
    followerVect = Utils::FollowerProfile(proc::ip, proc::user, proc::password, proc::db, userID);
    followeeVect = Utils::FolloweeProfile(proc::ip, proc::user, proc::password, proc::db, userID);

    vector<pair<string, string>> FolloweeList;
    vector<pair<string, string>> FollowingList;

    std::pair<std::string,int> userCred = Utils::SessionTokenCheck(proc::ip,proc::user, proc::password, proc::db, Utils::sessionID);

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


    for (int i = 0; i < followerVect.size(); i++){
        if ((followerVect[i].first == (to_string(userCred.second))) && (followeeVect[i].first == userID)) {
            ui->FollowButton->setText("- Unfollow");
            ui->FollowButton -> setStyleSheet("background-color: rgb(48, 143, 145);");
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
    connect(ui->blockButton, &QPushButton::clicked, this, [this, userID]() {
        BlockButton_clicked(userID);
    });
    resize(1000, 800);
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
            ui->FollowButton->setStyleSheet(
                "QPushButton {"
                "   color: rgba(0,0,0);"
                "   border: none;"
                "   border-radius: 8px;"
                "   background-color: rgb(0, 170, 245);"
                "   font-family: 'MS Sans Serif';"
                "   font-weight: bold;"
                "   text-align: center;"
                "}"
                "QPushButton:hover {"
                "   background-color: rgb(10, 180, 255);"
                "}"
                );
        }
    }
}

void Follow::BlockButton_clicked(string userID)
{
    QString currentText = ui->blockButton->text();

    if(currentText == "+ Block")
    {
        Utils::BlockUser(proc::ip, proc::user, proc::password, proc::db, userID);
        ui->blockButton -> setText("- Unblock");
        ui->FollowButton->setText("Cannot Follow");
        ui->blockButton->setStyleSheet(
            "QPushButton {"
            "   color: rgba(0,0,0);"
            "   border: none;"
            "   border-radius: 8px;"
            "   background-color: rgb(176, 176, 176);"
            "   font-family: 'MS Sans Serif';"
            "   font-weight: bold;"
            "   text-align: center;"
            "}"
            );
        ui->FollowButton->setStyleSheet(
            "QPushButton {"
            "   color: rgba(0,0,0);"
            "   border: none;"
            "   border-radius: 8px;"
            "   background-color: rgb(176, 176, 176);"
            "   font-family: 'MS Sans Serif';"
            "   font-weight: bold;"
            "   text-align: center;"
            "}"
            );
    }
    else if (currentText == "- Unblock")
    {
        Utils::BlockUser(proc::ip, proc::user, proc::password, proc::db, userID);
        ui->blockButton->setText("+ Block");
        ui->FollowButton-> setText("+ Follow");
        ui->blockButton->setStyleSheet(
            "QPushButton {"
            "   color: rgba(255, 255, 255);"
            "   border: none;"
            "   border-radius: 8px;"
            "   background-color: rgb(139, 0, 0);"
            "   font-family: 'MS Sans Serif';"
            "   font-weight: bold;"
            "   text-align: center;"
            "}"
            "QPushButton:hover {"
            "   background-color: rgb(178, 34, 34);"
            "}"
            );
        ui->FollowButton->setStyleSheet(
            "QPushButton {"
            "   color: rgba(0,0,0);"
            "   border: none;"
            "   border-radius: 8px;"
            "   background-color: rgb(0, 170, 245);"
            "   font-family: 'MS Sans Serif';"
            "   font-weight: bold;"
            "   text-align: center;"
            "}"
            "QPushButton:hover {"
            "   background-color: rgb(10, 180, 255);"
            "}"
            );
    }

    vector<pair<string, string>> followerVect;
    vector<pair<string, string>> followeeVect;
    followerVect = Utils::FollowerProfile(proc::ip, proc::user, proc::password, proc::db, userID);
    followeeVect = Utils::FolloweeProfile(proc::ip, proc::user, proc::password, proc::db, userID);
    std::pair<std::string,int> userCred = Utils::SessionTokenCheck(proc::ip,proc::user, proc::password, proc::db, Utils::sessionID);
    for (int i = 0; i < followerVect.size(); i++){
        if ((followerVect[i].first == (to_string(userCred.second))) && (followeeVect[i].first == userID)) {
            Utils::UserFollow(proc::ip, proc::user, proc::password, proc::db, userID);
        }
    }
}

void Follow::Followers_clicked(string userID)
{
    Followers *FollowerList = new Followers(this, userID);
    this->hide();
    FollowerList->show();
}

void Follow::Following_clicked(string userID)
{
    Following *FollowingList = new Following(this, userID);
    this->hide();
    FollowingList->show();
}

void Follow::resizeEvent(QResizeEvent* event) {
    QMainWindow::resizeEvent(event);
    QSize newSize = event->size();

    // Access the width and height
    int newWidth = newSize.width();
    int newHeight = newSize.height();
}

void Follow::on_Back_clicked()
{
    this->hide();
    if(parentWidget()) {
        parentWidget()->show();
    }
}
