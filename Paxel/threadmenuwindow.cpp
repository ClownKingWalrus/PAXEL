#include "threadmenuwindow.h"
#include "ui_threadmenuwindow.h"
#include "homescreen.h"
#include "../hdr/Utils.h"
#include "threadbannerbox.h"
#include "../hdr/proc.h"
#include "createboardorthread.h"

#include <QPushButton>
#include <QSizePolicy>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QWidget>
#include <QMessageBox>
#include <qevent.h>

ThreadMenuWindow::ThreadMenuWindow(QWidget *parent, std::string boardID)
    : QMainWindow(parent)
    , ui(new Ui::ThreadMenuWindow)
{
    ui->setupUi(this);
    boardIDT = boardID;
    createThread = new QPushButton("+Create Thread+");
    createThread->setFont(QFont("MS Sans Serif", 32, QFont::Bold));
    createThread->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    createThread->setMinimumSize(QSize(20, 100));
    //connect button with lambda

    followBoards = new QPushButton("+ Follow Board");
    followBoards->setFont(QFont("MS Sans Serif", 16));
    followBoards->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    followBoards->setMinimumSize(QSize(20, 30));

    reloadButton = new QPushButton("Reload");
    reloadButton->setFont(QFont("MS Sans Serif", 16));
    reloadButton->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    reloadButton->setMinimumSize(QSize(20, 30));

    ui->BackHome->setFont(QFont("MS Sans Serif", 20));
    ui->BackHome->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    ui->BackHome->setMinimumSize(QSize(20, 30));

    QPushButton::connect(createThread, &QPushButton::clicked, this, [this]() {
        CreateThreadButtonClicked();
    });
    QPushButton::connect(followBoards, &QPushButton::clicked, this, [this, boardID]() {
        BoardsFollowClicked(boardID);
    });

    QScrollArea* scrollBoxMain = new QScrollArea();
    QVBoxLayout* vertLayout = new QVBoxLayout();

    //set the layout to be a verticle scroller
    scrollBoxMain->setLayout(vertLayout);
    ui->verticalLayout->addWidget(createThread);
    ui->verticalLayout->addWidget(followBoards);
    ui->verticalLayout->addWidget(reloadButton);
    //call thread info from sql and stores it into the vector
    std::vector<std::vector<std::string>> threadVect;
    threadVect = Utils::ThreadUpdate(proc::ip, proc::user, proc::password, proc::db, boardID);

    for (int i = 0; i < threadVect.size(); i++) {
        ThreadBannerBox* threadBanner = CreateThreadBanner(threadVect[i][0], threadVect[i][1], threadVect[i][2]); //user ID in front
        QHBoxLayout* temp = new QHBoxLayout();
        temp->addWidget(threadBanner);
        ui->verticalLayout->addLayout(temp);
    }

    std:: vector<std::pair<std::string, std::string>> boardfollowVect;
    boardfollowVect = Utils::BoardFollowList(proc::ip, proc::user, proc::password, proc::db, boardID);
    std::pair<std::string,int> userCred = Utils::SessionTokenCheck(proc::ip,proc::user, proc::password, proc::db, Utils::sessionID);
    for (int i = 0; i < boardfollowVect.size(); i++){
        if (boardfollowVect[i].first == boardID) {
            followBoards -> setText("- Unfollow Board");
            followBoards -> setStyleSheet("background-color: rgb(48, 143, 145);");
        }
    }
    resize(1000, 800);
}

ThreadMenuWindow::~ThreadMenuWindow()
{
    delete ui;
}

ThreadBannerBox* ThreadMenuWindow::CreateThreadBanner(std::string userName, std::string threadName, std::string threadID) { //userName is actually userID
        //more styling options since qwidget and not just a QHBox
    ThreadBannerBox* bannerWidget = new ThreadBannerBox(QString::fromStdString(userName), QString::fromStdString(threadName), QString::fromStdString(threadID), this);
    return bannerWidget;
}

void ThreadMenuWindow::CreateThreadButtonClicked()
{
    if (boardIDT == "") {
        QMessageBox* box = new QMessageBox();
        box->setText("Not sure what Board your on -bug report to devs");
        box->show();
        return;
    }
    std::cout << "Can we work\n";
    CreateBoardOrThread* createThreadWindow = new CreateBoardOrThread();
    createThreadWindow->isThread = true;
    createThreadWindow->boardID = boardIDT;
    createThreadWindow->ChangeToThreadWindow();
    createThreadWindow->show();
    hide();
}

void ThreadMenuWindow::BoardsFollowClicked(std::string boardID) {
    Utils::BoardFollow(proc::ip, proc::user, proc::password, proc::db, boardID);
    QString currentText = followBoards->text();
    if (currentText == "+ Follow Board") {
        followBoards -> setText("- Unfollow Board");
        followBoards -> setStyleSheet("background-color: rgb(48, 143, 145);");
    }
    else if (currentText == "- Unfollow Board") {
        followBoards -> setText("+ Follow Board");
        followBoards -> setStyleSheet("background-color: rgb(75, 222, 255);");
    }
}

void ThreadMenuWindow::on_BackHome_clicked()
{
    // HomeScreen *BackHome = new HomeScreen();
    // hide();
    // BackHome->show();
    // this->close();
    if (!Utils::sessionID.empty()) {
        std::cout << "+++Login Succeded+++\n";
        HomeScreen* Homescreen = new HomeScreen();
        Homescreen->show();
        this->close();
    } else {
        return;
    }
}

void ThreadMenuWindow::resizeEvent(QResizeEvent* event) {
    QMainWindow::resizeEvent(event);
    QSize newSize = event->size();

    // Access the width and height
    int newWidth = newSize.width();
    int newHeight = newSize.height();
}

