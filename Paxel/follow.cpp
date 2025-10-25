#include "follow.h"
#include "ui_follow.h"
#include "followers.h"
#include "following.h"
#include "profile.h"
#include <QPushButton>
#include <QMessageBox>
#include <QString>

Follow::Follow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Follow)
{
    ui->setupUi(this);
}
int followercount = 0;
int followingcount = 0;

Follow::~Follow()
{
    delete ui;
}

void Follow::on_FollowButton_clicked()
{
    QString currentText = ui->FollowButton->text();
    QString FlwCount = ui->Followers->text();
    if(currentText == "+ Follow")
    {
        ui->FollowButton->setText("- Unfollow");
        followercount++;
    }
    else if (currentText == "- Unfollow")
    {
        QMessageBox::StandardButton reply = QMessageBox::question(this,"Unfollow","Do You Want to Unfollow?",QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            ui->FollowButton->setText("+ Follow");
            followercount--;
        }
    }
    if(followercount == 1){
        ui->Followers->setText(QString::number(followercount) + " Follower");
    }
    else {
        ui->Followers->setText(QString::number(followercount) + " Followers");
    }
}

void Follow::on_Followers_clicked()
{
    Followers *FriendsFriends = new Followers;
    hide();
    FriendsFriends -> show();
}

void Follow::on_Following_clicked()
{
    Following *FollowingFollowing = new Following;
    hide();
    FollowingFollowing -> show();
}

void Follow::on_Back_clicked()
{}
