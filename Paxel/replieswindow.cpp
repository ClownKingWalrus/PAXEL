#include "replieswindow.h"
#include "ui_replieswindow.h"
#include "../hdr/Utils.h"

#include <QPushButton>
#include <QSizePolicy>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QPlainTextEdit>

///change these for testing
const std::string sqlIp = "localhost::3306";
const std::string sqlUser = "root";
const std::string sqlPassword = "password";
const std::string sqlDatabase = "paxel";

RepliesWindow::RepliesWindow(QWidget *parent, std::string threadID)
    : QMainWindow(parent)
    , ui(new Ui::RepliesWindow)
{
    ui->setupUi(this);

    QScrollArea* scrollBoxMain = new QScrollArea();
    QVBoxLayout* vertLayout = new QVBoxLayout();

    //set the layout to be a verticle scroller
    scrollBoxMain->setLayout(vertLayout);

    //call thread info from sql and stores it into the vector
    std::vector<std::tuple<std::string, std::string, std::string, std::string>> threadVect;
    threadVect = Utils::RepliesUpdate(sqlIp, sqlUser, sqlPassword, sqlDatabase, threadID);

    RepliesWindow::threadID = threadID;

    QHBoxLayout* threadBanner = CreateBanner(std::get<0>(threadVect[0]), std::get<1>(threadVect[0]), std::get<2>(threadVect[0]), std::get<3>(threadVect[0]), 100);
    ui->verticalLayout->addLayout(threadBanner);

    for (int i = 1; i < threadVect.size(); i++) {
        QHBoxLayout* repliesBanner = CreateBanner(std::get<0>(threadVect[i]), std::get<1>(threadVect[i]), std::get<2>(threadVect[i]), std::get<3>(threadVect[i]), 60);
        ui->verticalLayout->addLayout(repliesBanner);
    }

    ui->replyBox->setVisible(false);
    ui->replySend->setVisible(false);
    ui->replyCancel->setVisible(false);
}

RepliesWindow::~RepliesWindow()
{
    delete ui;
}

QHBoxLayout* RepliesWindow::CreateBanner(std::string userName, std::string threadCommentName, std::string threadCommentID, std::string commentReply, int height) {
    ///create HBox to store the banners content
    QHBoxLayout* bannerBox = new QHBoxLayout();

    ///creating buttons
    QPushButton* bUserName = new QPushButton(QString::fromStdString(userName));
    QPushButton* bThreadCommentName = new QPushButton(QString::fromStdString(threadCommentName));
    QPushButton* bThreadCommentID = new QPushButton(QString::fromStdString(threadCommentID));
    QPushButton* bCommentReply = new QPushButton(QString::fromStdString(commentReply));
    QPushButton* bReply = new QPushButton("R");

    ///resizing buttons
    bUserName->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    bUserName->setFixedHeight(height);
    bUserName->setFixedWidth(150);
    bUserName->setFlat(true);

    bThreadCommentName->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed));
    bThreadCommentName->setFixedHeight(height);

    bThreadCommentID->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    bThreadCommentID->setFixedHeight(height/2);
    bThreadCommentID->setFixedWidth(125);

    bCommentReply->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    bCommentReply->setFixedHeight(height/2);
    bCommentReply->setFixedWidth(125);

    bReply->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    bReply->setFixedWidth(20);
    bReply->setFixedHeight(20);

    //connect functions saving each unique arg
    QPushButton::connect(bUserName, &QPushButton::clicked, this, [this, userName]() {
        ClickOnProfile(userName);
    });

    QPushButton::connect(bThreadCommentName, &QPushButton::clicked, this, [this, threadCommentName]() {
        ClickOnBanner(threadCommentName);
    });

    QPushButton::connect(bReply, &QPushButton::clicked, this, [this, threadCommentID] ()
    {
        ClickOnReply(threadCommentID);
    });

    bannerBox->addWidget(bUserName);
    bannerBox->addWidget(bThreadCommentName, 1);
    bannerBox->addWidget(bThreadCommentID);
    bannerBox->addWidget(bCommentReply);
    bannerBox->addWidget(bReply);

    return bannerBox;

}

void RepliesWindow::ClickOnBanner(std::string threadCommentName) {

}

void RepliesWindow::ClickOnProfile(std::string userID) {

}

///Clicking on reply button tied to thread or comment
void RepliesWindow::ClickOnReply(std::string threadCommentID)
{
    replyID = threadCommentID;

    ui->replyBox->setVisible(true);
    ui->replySend->setVisible(true);
    ui->replyCancel->setVisible(true);
}

///Will go back to threads in board user was previously in
void RepliesWindow::on_backToThreads_clicked() {

}

///Sends comment to sql
void RepliesWindow::on_replySend_clicked()
{
    std::string commentName = ui->replyBox->toPlainText().toStdString();

    if (threadID == replyID)
        replyID = "";

    Utils::CreateReply(sqlIp, sqlUser, sqlPassword, sqlDatabase, threadID, commentName, replyID);

    endReply();
}

void RepliesWindow::on_replyCancel_clicked()
{
    endReply();
}

void RepliesWindow::endReply(void)
{
    replyID = "";
    ui->replyBox->setVisible(false);
    ui->replyBox->setPlainText("");
    ui->replySend->setVisible(false);
    ui->replyCancel->setVisible(false);
}
