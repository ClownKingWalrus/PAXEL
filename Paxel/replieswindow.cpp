#include "replieswindow.h"
#include "ui_replieswindow.h"
#include "../hdr/Utils.h"

#include <QPushButton>
#include <QSizePolicy>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QVBoxLayout>

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
    std::vector<std::pair<std::string, std::string>> threadVect;
    threadVect = Utils::RepliesUpdate("ip", "user", "password", "db", threadID);

    QHBoxLayout* threadBanner = CreateBanner(threadVect[0].first, threadVect[0].second, 100);
    ui->verticalLayout->addLayout(threadBanner);

    for (int i = 1; i < threadVect.size(); i++) {
        QHBoxLayout* repliesBanner = CreateBanner(threadVect[i].first, threadVect[i].second, 60);
        ui->verticalLayout->addLayout(repliesBanner);
    }
}

RepliesWindow::~RepliesWindow()
{
    delete ui;
}

QHBoxLayout* RepliesWindow::CreateBanner(std::string userName, std::string threadCommentName, int height) {
    //create HBox to store the banners content
    QHBoxLayout* bannerBox = new QHBoxLayout();

    //create test buttons
    QPushButton* pButton1 = new QPushButton(QString::fromStdString(userName));
    QPushButton* pButton2 = new QPushButton(QString::fromStdString(threadCommentName));

    pButton1->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    pButton1->setFixedHeight(height);
    pButton1->setFixedWidth(150);
    pButton1->setFlat(true);

    pButton2->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed));
    pButton2->setFixedHeight(height);

    //connect functions saving each unique arg
    QPushButton::connect(pButton1, &QPushButton::clicked, this, [this, userName]() {
        ClickOnProfile(userName);
    });

    //connect functions saving each unique arg
    QPushButton::connect(pButton2, &QPushButton::clicked, this, [this, threadCommentName]() {
        ClickOnBanner(threadCommentName);
    });

    bannerBox->addWidget(pButton1); //should be a small box -users icon or info or somthing
    bannerBox->addWidget(pButton2); //should be long

    return bannerBox;

}

///Replies to thread or comment clicked
void RepliesWindow::ClickOnBanner(std::string threadCommentName) {

}

///Place holder function, implement the profile opening method
///Already connected to button so do not remove this actual function just define it
void RepliesWindow::ClickOnProfile(std::string userID) {

}

///Will go back to threads in board user was previously in
void RepliesWindow::on_backToThreads_clicked() {

}

