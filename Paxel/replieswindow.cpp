#include "replieswindow.h"
#include "ui_replieswindow.h"
#include "../hdr/Utils.h"
#include "../hdr/proc.h"

#include <QPushButton>
#include <QSizePolicy>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QPlainTextEdit>

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
    std::vector<std::vector<std::string>> threadVect;
    threadVect = Utils::RepliesUpdate(proc::ip, proc::user, proc::password, proc::db, threadID);

    RepliesWindow::threadID = threadID;

    QHBoxLayout* threadBanner = CreateBanner(threadVect[0][0], threadVect[0][1], threadVect[0][2], threadVect[0][3], 100);
    ui->verticalLayout->addLayout(threadBanner);

    for (int i = 1; i < threadVect.size(); i++) {
        QHBoxLayout* repliesBanner = CreateBanner(threadVect[i][0], threadVect[i][1], threadVect[i][2], threadVect[i][3], 60);
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
    QPushButton* pbUserName = new QPushButton(QString::fromStdString(userName));
    QPushButton* pbThreadCommentName = new QPushButton(QString::fromStdString(threadCommentName));
    QPushButton* pbThreadCommentID = new QPushButton(QString::fromStdString(threadCommentID));
    QPushButton* pbCommentReply = new QPushButton(QString::fromStdString(commentReply));
    QPushButton* pbReply = new QPushButton("R");

    ///resizing buttons
    pbUserName->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    pbUserName->setFixedHeight(height);
    pbUserName->setFixedWidth(150);
    pbUserName->setFlat(true);

    pbThreadCommentName->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed));
    pbThreadCommentName->setFixedHeight(height);

    pbThreadCommentID->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    pbThreadCommentID->setFixedHeight(height/2);
    pbThreadCommentID->setFixedWidth(125);

    pbCommentReply->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    pbCommentReply->setFixedHeight(height/2);
    pbCommentReply->setFixedWidth(125);

    pbReply->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    pbReply->setFixedWidth(35);
    pbReply->setFixedHeight(35);

    //connect functions saving each unique arg
    QPushButton::connect(pbUserName, &QPushButton::clicked, this, [this, userName]() {
        ClickOnProfile(userName);
    });

    QPushButton::connect(pbThreadCommentName, &QPushButton::clicked, this, [this, threadCommentName]() {
        ClickOnBanner(threadCommentName);
    });

    QPushButton::connect(pbReply, &QPushButton::clicked, this, [this, threadCommentID] ()
                         {
                             ClickOnReply(threadCommentID);
                         });

    bannerBox->addWidget(pbUserName);
    bannerBox->addWidget(pbThreadCommentName, 1);
    bannerBox->addWidget(pbThreadCommentID);
    bannerBox->addWidget(pbCommentReply);
    bannerBox->addWidget(pbReply);
    pbReply->setStyleSheet("background-color: rgb(35, 193, 24);");

    setStyleSheet(R"(
    QWidget {
        font: 14pt "MS Sans Serif";
    }

    QPushButton {
        background-color: rgb(0, 170, 245);
        color: black;
        border: 1px solid rgb(68, 68, 68);
        border-radius: 8px;
        padding: 6px 10px;
    }

    QPushButton:hover {
        background-color: rgb(10, 190, 255);
    }

  QPlainTextEdit {
        background-color: rgb(44, 44, 44);
        color: black;
        border: 1px solid rgb(68, 68, 68);
        border-radius: 6px;
        font: 14pt "MS Sans Serif";
    }

)");

    return bannerBox;
    resize(1000, 800);

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
    QWidget* parentWin = this->parentWidget();
    if (parentWin) {
        parentWin->show();
    }
    this->close();

}

///Sends comment to sql
void RepliesWindow::on_replySend_clicked()
{
    std::string commentName = ui->replyBox->toPlainText().toStdString();

    if (threadID == replyID)
        replyID = "";

    Utils::CreateReply(proc::ip, proc::user, proc::password, proc::db, threadID, commentName, replyID);

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

void RepliesWindow::resizeEvent(QResizeEvent* event) {
    QMainWindow::resizeEvent(event);
    QSize newSize = event->size();

    // Access the width and height
    int newWidth = newSize.width();
    int newHeight = newSize.height();
}
