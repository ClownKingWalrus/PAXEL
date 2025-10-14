#include "threadmenuwindow.h"
#include "ui_threadmenuwindow.h"
#include "../hdr/Utils.h"
#include "replieswindow.h"

#include <QPushButton>
#include <QSizePolicy>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QVBoxLayout>

ThreadMenuWindow::ThreadMenuWindow(QWidget *parent, std::string boardID)
    : QMainWindow(parent)
    , ui(new Ui::ThreadMenuWindow)
{
    ui->setupUi(this);

    QScrollArea* scrollBoxMain = new QScrollArea();
    QVBoxLayout* vertLayout = new QVBoxLayout();

    //set the layout to be a verticle scroller
    scrollBoxMain->setLayout(vertLayout);

    //call thread info from sql and stores it into the vector
    std::vector<std::vector<std::string>> threadVect;
    threadVect = Utils::ThreadUpdate("localhost::3306", "root", "Ddomo2001@", "paxel", boardID);

    for (int i = 0; i < threadVect.size(); i++) {
        QHBoxLayout* threadBanner = CreateThreadBanner(threadVect[i][0], threadVect[i][1], threadVect[i][2]);
        ui->verticalLayout->addLayout(threadBanner);
    }
}

ThreadMenuWindow::~ThreadMenuWindow()
{
    delete ui;
}

QHBoxLayout* ThreadMenuWindow::CreateThreadBanner(std::string userName, std::string threadName, std::string threadID) {
    //create HBox to store the banners content
    QHBoxLayout* bannerBox = new QHBoxLayout();

    //create test buttons
    QPushButton* pButton1 = new QPushButton(QString::fromStdString(userName));
    QPushButton* pButton2 = new QPushButton(QString::fromStdString(threadName));

    pButton1->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    pButton1->setFixedHeight(150);
    pButton1->setFixedWidth(150);
    pButton1->setFlat(true);

    pButton2->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed));
    pButton2->setFixedHeight(150);

    //connect functions saving each unique arg
    QPushButton::connect(pButton1, &QPushButton::clicked, this, [this, userName]() {
        ClickOnProfile(userName);
    });

    //connect functions saving each unique arg
    QPushButton::connect(pButton2, &QPushButton::clicked, this, [this, threadID]() {
        ClickOnBanner(threadID);
    });

    bannerBox->addWidget(pButton1); //should be a small box -users icon or info or somthing
    bannerBox->addWidget(pButton2); //should be long

    return bannerBox;

}

///Place holder function, implement the comment opening method
///Already connected to button so do not remove this actual function just define it
void ThreadMenuWindow::ClickOnBanner(std::string threadID) {

    RepliesWindow* replyThread = new RepliesWindow(this, threadID);
    replyThread->show();
}

///Place holder function, implement the profile opening method
///Already connected to button so do not remove this actual function just define it
void ThreadMenuWindow::ClickOnProfile(std::string userID) {

}
