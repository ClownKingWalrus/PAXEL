#include "profile.h"
#include "ui_profile.h"
#include "followers.h"
#include "follow.h"
#include <QMessageBox>
#include <QString>

Profile::Profile(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Profile)
{
    ui->setupUi(this);
    extern int followingcount;
    extern int followercount;
    QString FollowerTxt = ui->Followers->text();
    QString FollowingTxt = ui->Following->text();

    ui->Following->setText(QString::number(followercount) + " Following");
}

Profile::~Profile()
{
    delete ui;
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
