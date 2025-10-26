#include "following.h"
#include "ui_following.h"
#include "follow.h"
#include "followers.h"
#include "profile.h"
#include <QScrollBar>
#include <QPushButton>
#include <QObject>

Following::Following(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Following)
{
    ui->setupUi(this);
    extern int followingcount;
    connect(ui->scrollArea->verticalScrollBar(), &QScrollBar::valueChanged, this, &Following::onScroll);
    loadProfiles(followingcount);
}

Following::~Following()
{
    delete ui;
}

void Following::on_Back_clicked()
{
    Follow *FollowFollow = new Follow;
    QString UserList = ui->UserList->text();
    hide();
    FollowFollow->show();
}

void Following::loadProfiles(int count) {
    for (int i = 0; i < count; ++i) {
        ProfileCount++;
        QPushButton *btn = new QPushButton(QString("Profile %1").arg(ProfileCount), this);
        btn->setMinimumSize(500, 80);
        btn->setMaximumSize(500, 100);
        ui->verticalLayout->addWidget(btn);
        QObject::connect(btn, &QPushButton::clicked, this, &Following::onClicked);
    }
}

void Following::onScroll(int value) {
    QScrollBar *bar = ui->scrollArea->verticalScrollBar();
}

void Following::onClicked() {
    Follow *FollowFollow = new Follow;
    hide();
    FollowFollow->show();
}

void Following::on_Followers_2_clicked()
{
    Followers *FollowersFollowers = new Followers;
    hide();
    FollowersFollowers->show();
}

