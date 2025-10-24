#include "threadmenuwindow.h"
#include "ui_threadmenuwindow.h"
#include "../hdr/Utils.h"
#include "threadbannerbox.h"
#include "../hdr/proc.h"

#include <QPushButton>
#include <QSizePolicy>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QWidget>

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
