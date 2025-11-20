#include "followedboards.h"
#include "ui_followedboards.h"
#include "homescreen.h"
#include "profilepicture.h"
#include "threadmenuwindow.h"
#include "profile.h"
#include "follow.h"
#include "../hdr/proc.h"
#include "../hdr/Utils.h"

#include <QScrollBar>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <qevent.h>
using namespace std;
FollowedBoards::FollowedBoards(QWidget *parent, string boardID)
    : QMainWindow(parent)
    , ui(new Ui::FollowedBoards)
{
    ui->setupUi(this);

    QPixmap pixmap1(":/images/Images/clouds.png");
    QPixmap scaledPixmap1 = pixmap1.scaled(300, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->Clouds->setPixmap(scaledPixmap1);

    QPixmap pixmap2(":/images/Images/Clouds reverse.png");
    QPixmap scaledPixmap2 = pixmap2.scaled(300, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->RevClouds->setPixmap(scaledPixmap2);


    bannerLayout = new QVBoxLayout(ui->scrollAreaWidgetContents);
    ui->scrollAreaWidgetContents->setLayout(bannerLayout);
    loadBoards(proc::ip, proc::user, proc::password, proc::db, boardID);
    resize(1000, 800);
}

FollowedBoards::~FollowedBoards()
{
    delete ui;
}

void FollowedBoards::loadBoards(const string& host, const string& user, const string& password, const string& dbName, string boardID) {

    vector<pair<string, string>> boardfollowVect;
    boardfollowVect = Utils::BoardFollowList(proc::ip, proc::user, proc::password, proc::db, boardID);
    std::pair<std::string,int> userCred = Utils::SessionTokenCheck(proc::ip,proc::user, proc::password, proc::db, Utils::sessionID);

    for (const auto& FB : boardfollowVect) {
        QHBoxLayout* boardBanner = CreateBoardBanner(FB.first, FB.second);
        bannerLayout->addLayout(boardBanner);
    }
}

QHBoxLayout* FollowedBoards::CreateBoardBanner(const string& boardID, const string& boardName) {
    QHBoxLayout* bannerBox = new QHBoxLayout();

    QPushButton* idButton = new QPushButton(QString::fromStdString(boardID));
    QPushButton* titleButton = new QPushButton(QString::fromStdString(boardName));

    //yoink the userID from board
    std::string userTemp = boardID; //not sure if touching the memory is dangroud this is a failsafe
    int userID = Utils::GetUserIDFromBoardID(proc::ip, proc::user, proc::password, proc::db, std::stoi(userTemp));
    //load the pixmap if it exist
    QPixmap pix = ProfilePicture::CreatePixMapFromSql(userID);
    if (!pix.isNull()) {
        QIcon icon(pix.scaled(64, 64, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        idButton->setIcon(icon);
        idButton->setIconSize(idButton->size());
        idButton->setText("");
        idButton->setStyleSheet(
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
        idButton->setIcon(icon);
        idButton->setIconSize(idButton->size());
        idButton->setText("");
        idButton->setStyleSheet(
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


    idButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    titleButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    idButton->setMinimumSize(150, 45);
    idButton->setFlat(true);

    titleButton->setMinimumSize(250, 45);
    titleButton->setFlat(true);

    titleButton->setStyleSheet(
        "QPushButton { background-color: rgb(8, 136, 245); color: black; font-family: MS Sans Serif; font-weight: bold;}"  // blue
        "border-radius: 8px;"
        );

    bannerBox->addWidget(idButton, 1);
    bannerBox->addWidget(titleButton, 3);

    bannerBox->setContentsMargins(10, 5, 10, 5);
    bannerBox->setSpacing(15);

    QPushButton::connect(titleButton, &QPushButton::clicked, this, [this, boardID]() {
        onClicked(boardID);
    });
    QPushButton::connect(idButton, &QPushButton::clicked, this, [this, userID]() {
        ClickID(to_string(userID));
    });
    connect(ui->Back, &QPushButton::clicked, this, &FollowedBoards::on_Back_clicked);

    return bannerBox;
}

void FollowedBoards::onClicked(string boardID) {
    ThreadMenuWindow *BoardFollow = new ThreadMenuWindow(this, boardID);
    BoardFollow->show();
    this->hide();
}

void FollowedBoards::ClickID(string userID) {
    std::pair<std::string,int> userCred = Utils::SessionTokenCheck(proc::ip,proc::user, proc::password, proc::db, Utils::sessionID);
    if (userID == std::to_string(userCred.second)) {
        Profile *userProf = new Profile(this);
        userProf->show();
    }
    else {
        Follow *otherProf = new Follow(this, userID);
        otherProf->show();
    }
    this->hide();
}

void FollowedBoards::on_Back_clicked()
{
    this->hide();
    if (parentWidget()) {
        parentWidget()->show();
    }
}

void FollowedBoards::resizeEvent(QResizeEvent* event) {
    QMainWindow::resizeEvent(event);
    QSize newSize = event->size();

    // Access the width and height
    int newWidth = newSize.width();
    int newHeight = newSize.height();
}