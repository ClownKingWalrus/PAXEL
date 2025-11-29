#include "homescreen.h"
#include "ui_homescreen.h"
#include "profile.h"
#include "../hdr/Utils.h"
#include "../hdr/proc.h"
#include "threadmenuwindow.h"
#include "messagewindow.h"
#include "YourPaxelBoard.h"
#include "followedboards.h"

#include <QTimer>
#include <QDateTime>
#include <QScrollBar>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPixmap>
#include <QPainter>
#include <qevent.h>
using namespace std;

HomeScreen::HomeScreen(QWidget *parent) :
    QMainWindow(parent)
    , ui(new Ui::HomeScreen)
{
    ui->setupUi(this);

    bannerLayout = new QVBoxLayout(ui->scrollAreaWidgetContents);
    ui->scrollAreaWidgetContents->setLayout(bannerLayout);

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timefunction()));
    timer->start(1000);

    connect(ui->scrollArea->verticalScrollBar(), &QScrollBar::valueChanged,
            this, &HomeScreen::onScroll);

    loadBoards(proc::ip, proc::user, proc::password, proc::db);

    QPixmap pixmapHS1(":/images/Images/Home.png");
    QIcon buttonIcon1(pixmapHS1);
    ui->home_Button->setIcon(buttonIcon1);
    ui->home_Button->setIconSize(QSize(100, 100));

    QPixmap pixmapHS2(":/images/Images/Banner2.png");
    QPixmap scaledPixmapHS2 = pixmapHS2.scaled(300, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->Banner->setPixmap(scaledPixmapHS2);

    QPixmap pixmapHS3(":/images/Images/Followers.png");
    QIcon buttonIcon2(pixmapHS3);
    ui->Followers->setIcon(buttonIcon2);
    ui->Followers->setIconSize(QSize(100, 100));

    QPixmap pixmapHS4(":/images/Images/Paxel banner.png");
    QPixmap scaledPixmapHS4 = pixmapHS4.scaled(350, 500, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QPainter painter(&scaledPixmapHS4);
    painter.setPen(Qt::black);
    painter.setFont(QFont("MS Sans Serif", 16, QFont::Bold));
    painter.drawText(scaledPixmapHS4.rect(), Qt::AlignCenter, "Paxel Boards");
    painter.end();
    ui->boards_Banner->setPixmap(scaledPixmapHS4);

    QPixmap pixmapHS5(":/images/Images/Text Bubble.png");
    QIcon buttonIcon3(pixmapHS5);
    ui->messages_Button->setIcon(buttonIcon3);
    ui->messages_Button->setIconSize(QSize(100, 100));

    QPixmap pixmapHS6(":/images/Images/Question Mark.png");
    QIcon buttonIcon4(pixmapHS6);
    ui->help_Button->setIcon(buttonIcon4);
    ui->help_Button->setIconSize(QSize(80, 80));

    QPixmap pixmapHS7(":/images/Images/Paxel P.png");
    QIcon buttonIcon5(pixmapHS7);
    ui->about_paxel->setIcon(buttonIcon5);
    ui->about_paxel->setIconSize(QSize(80, 80));


    pair<string,int> userCred = Utils::SessionTokenCheck(proc::ip,proc::user, proc::password, proc::ip, Utils::sessionID);
    connect(ui -> BoardsFollowed, &QPushButton::clicked, this, [this, userCred]() {
        BoardsFollowed_clicked(to_string(userCred.second));
    });
    resize(1000, 800);
}

HomeScreen::~HomeScreen()
{
    delete ui;
}

void HomeScreen::on_Profile_clicked()
{
    Profile* ProfileProfile = new Profile();
    hide();
    ProfileProfile->show();
}
void HomeScreen::timefunction() {
    QTime time = QTime::currentTime();
    QString time_text = time.toString("hh : mm ap");
    ui->Clock->setText(time_text);
}

void HomeScreen::loadBoards(const string& host, const string& user, const string& password, const string& dbName) {

    vector<pair<string, string>> boardVect;
    boardVect = Utils::BoardUpdate(host, user, password, dbName);

    for (const auto& board : boardVect ) {
        QHBoxLayout* boardBanner = CreateBoardBanner(board.first, board.second);
        bannerLayout->addLayout(boardBanner);
    }
}

QHBoxLayout* HomeScreen::CreateBoardBanner(const string& boardID, const string& boardName) {
    QHBoxLayout* bannerBox = new QHBoxLayout();

    QPushButton* idButton = new QPushButton(QString::fromStdString(boardID));
    QPushButton* titleButton = new QPushButton(QString::fromStdString(boardName));

    idButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    titleButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    idButton->setMinimumSize(150, 45);
    idButton->setFlat(true);

    titleButton->setMinimumSize(250, 45);
    titleButton->setFlat(true);

    idButton->setStyleSheet(
        "QPushButton { background-color: rgb(35, 242, 24); color: black; font-family: MS Sans Serif; font-weight: bold; }"  // green
        "border-radius: 8px;"        // rounded corners
        );

    titleButton->setStyleSheet(
        "QPushButton { background-color: rgb(8, 136, 245); color: black; font-family: MS Sans Serif; font-weight: bold;}"  // blue
        "border-radius: 8px;"
        );

    bannerBox->addWidget(idButton, 1);
    bannerBox->addWidget(titleButton, 3);

    bannerBox->setContentsMargins(10, 5, 10, 5);
    bannerBox->setSpacing(15);

    QPushButton::connect(titleButton, &QPushButton::clicked, this, [this, boardID]() {
        ClickOnBoardName(boardID);
    });

    return bannerBox;
}

void HomeScreen::ClickOnBoardName (string boardID) {
    ThreadMenuWindow* threadList = new ThreadMenuWindow(this, boardID);
    threadList->show();
    hide();
}

void HomeScreen::onScroll(int value)
{
    QScrollBar* bar = ui->scrollArea->verticalScrollBar();
    if (value >= bar->maximum() - 50) {
        qDebug() << "User scrolled near bottom";
        // You can implement paginated loading if needed
    }
}

void HomeScreen::on_CreateBoardButton_clicked()
{
    CreateBoardWindow* newWin = new CreateBoardWindow(this);
    newWin->show();
    hide();
}

void HomeScreen::BoardsFollowed_clicked(string userID)
{
    FollowedBoards* FB = new FollowedBoards(this, userID);
    hide();
    FB ->show();
}

void HomeScreen::resizeEvent(QResizeEvent* event) {
    QMainWindow::resizeEvent(event);
    QSize newSize = event->size();

    // Access the width and height
    int newWidth = newSize.width();
    int newHeight = newSize.height();
}

void HomeScreen::on_messages_Button_clicked()
{
    MessageWindow* msgWindow = new MessageWindow(this);
    msgWindow->show();
}


void HomeScreen::on_about_paxel_clicked()
{
    ClickOnBoardName("26");
}


void HomeScreen::on_help_Button_clicked()
{
    ClickOnBoardName("8");
}

