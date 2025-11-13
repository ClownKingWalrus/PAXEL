#include "threadmenuwindow.h"
#include "ui_threadmenuwindow.h"
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
    std::string temp = std::to_string(proc::userID);
    //connect button with lambda
    QPushButton::connect(createThread, &QPushButton::clicked, this, [this, temp]() {
        CreateThreadButtonClicked(temp);
    });

    QScrollArea* scrollBoxMain = new QScrollArea();
    QVBoxLayout* vertLayout = new QVBoxLayout();

    //set the layout to be a verticle scroller
    scrollBoxMain->setLayout(vertLayout);
    ui->verticalLayout->addWidget(createThread);
    //call thread info from sql and stores it into the vector
    std::vector<std::vector<std::string>> threadVect;
    threadVect = Utils::ThreadUpdate(proc::ip, proc::user, proc::password, proc::db, boardID);

    for (int i = 0; i < threadVect.size(); i++) {
        ThreadBannerBox* threadBanner = CreateThreadBanner(threadVect[i][0], threadVect[i][1], threadVect[i][2]);
        QHBoxLayout* temp = new QHBoxLayout();
        temp->addWidget(threadBanner);
        ui->verticalLayout->addLayout(temp);
    }
}

ThreadMenuWindow::~ThreadMenuWindow()
{
    delete ui;
}

ThreadBannerBox* ThreadMenuWindow::CreateThreadBanner(std::string userName, std::string threadName, std::string threadID) {
        //more styling options since qwidget and not just a QHBox
    ThreadBannerBox* bannerWidget = new ThreadBannerBox(QString::fromStdString(userName), QString::fromStdString(threadName), QString::fromStdString(threadID), this);
    return bannerWidget;
}

void ThreadMenuWindow::CreateThreadButtonClicked(std::string uuid)
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
}
