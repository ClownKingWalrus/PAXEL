#include "followers.h"
#include "ui_followers.h"
#include "follow.h"
#include "following.h"
#include "profile.h"
#include <QScrollBar>
#include <QPushButton>
#include <QObject>

Followers::Followers(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Followers)
{
    ui->setupUi(this);
    extern int followercount;
    extern int followingcount;
    connect(ui->scrollArea->verticalScrollBar(), &QScrollBar::valueChanged, this, &Followers::onScroll);
    loadProfiles(followercount);
}

Followers::~Followers()
{
    delete ui;
}

void Followers::on_Back_clicked()
{
    Follow *FollowFollow = new Follow;
    QString UserList = ui->UserList->text();
}

void Followers::loadProfiles(int count) {
    for (int i = 0; i < count; ++i) {
        ProfileCount++;
        QPushButton *btn = new QPushButton(QString("Profile %1").arg(ProfileCount), this);
        btn->setMinimumSize(500, 80);
        btn->setMaximumSize(500, 100);
        ui->verticalLayout->addWidget(btn);
        QObject::connect(btn, &QPushButton::clicked, this, &Followers::onClicked);
    }
}

void Followers::onScroll(int value) {
    QScrollBar *bar = ui->scrollArea->verticalScrollBar();
}

void Followers::onClicked() {
    Follow *FollowFollow = new Follow;
    hide();
    FollowFollow -> show();
}

void Followers::on_Following_clicked()
{
    Following *FollowingFollowing = new Following;
    hide();
    FollowingFollowing->show();
}

