#include "threadbannerbox.h"
#include <QPushButton>
#include <QWidget>
#include <QHBoxLayout>
#include "replieswindow.h"
#include "postreply.h"
#include "../hdr/Utils.h"
#include "../hdr/proc.h"
using namespace std;

    ThreadBannerBox::ThreadBannerBox(const QString& userName,
                                       const QString& threadName,
                                       const QString& threadID,
                                       QWidget* parent)
                                       :QWidget(parent) {
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

        profileButton = new QPushButton(userName, this);
        profileButton->setFixedSize(100,100);
        profileButton->setFlat(true);
        profileButton->setObjectName("profileButton");

        threadButton = new QPushButton(threadName, this);
        threadButton->setMinimumHeight(125);
        threadButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        threadButton->setObjectName("threadButton");

        likeButton = new QPushButton("\u25B2",this);
        likeButton->setMinimumSize(25,30);
        likeButton->setMaximumSize(50,60);
        likeButton->setObjectName("likeButton");

        followThreadButton = new QPushButton("F", this);
        followThreadButton->setMinimumSize(25,30);
        followThreadButton->setMaximumSize(50,60);
        followThreadButton->setObjectName("followThreadButton");

        replyToThreadButton = new QPushButton("R", this);
        replyToThreadButton->setMinimumSize(25, 30);
        replyToThreadButton->setMaximumSize(50, 60);
        replyToThreadButton->setObjectName("replyThreadButton");

        QPushButton::connect(profileButton, &QPushButton::clicked, this, [this, userName]() {
            OnClickProfile(userName);
        });

        QPushButton::connect(threadButton, &QPushButton::clicked, this, [this, threadID]() {
            if (!repliesVisible) {
                loadReplies(threadID);
                repliesBox->setVisible(true);
                repliesVisible = true;
            } else {
                repliesBox->setVisible(false);
                repliesVisible = false;
            }
        });

        QPushButton::connect(likeButton, &QPushButton::clicked, this, [this, threadID]() {
            OnClickLike(threadID);
        });

        QPushButton::connect(followThreadButton, &QPushButton::clicked, this, [this, threadID]() {
            OnClickFollowThread(threadID);
        });

        connect(replyToThreadButton, &QPushButton::clicked, this, [this, threadID]() {
            // Reply directly to the thread
            PostReply* popup = new PostReply(this, threadID, threadID);
            popup->exec();
        });

        QVBoxLayout* mainLayout = new QVBoxLayout(this);
        mainLayout->setContentsMargins(0,0,0,0);
        mainLayout->setSpacing(8);

        QHBoxLayout* bannerBox = new QHBoxLayout;
        bannerBox->setContentsMargins(8,8,8,8);
        bannerBox->setSpacing(8);
        bannerBox->addWidget(profileButton);
        bannerBox->addWidget(threadButton, 1); //sets streching to true

        QVBoxLayout* rightButtons = new QVBoxLayout;
        rightButtons->setSpacing(6);
        rightButtons->addWidget(likeButton);
        rightButtons->addWidget(followThreadButton);
        rightButtons->addWidget(replyToThreadButton);
        rightButtons->addStretch();
        bannerBox->addLayout(rightButtons);

        repliesBox = new QWidget(this);
        repliesLayout = new QVBoxLayout(repliesBox);
        repliesLayout->setContentsMargins(8, 8, 8, 8);
        repliesLayout->setSpacing(10);
        repliesBox->setVisible(false);

        mainLayout->addLayout(bannerBox);
        mainLayout->addWidget(repliesBox);

        setObjectName("ThreadBannerBox");
        setAttribute(Qt::WA_StyledBackground, true);
        setAutoFillBackground(true);

        setStyleSheet(R"(
        #ThreadBannerBox {
            background-color: rgb(44, 44, 44);
            border: 4px solid rgb(68, 68, 68);
            border-radius: 8px;
        }
        QPushButton#threadButton {
            background-color: rgb(0, 170, 245);
            color: black;
            border-radius: 1px;
            text-align: left;
            padding-left: 10px;
            font: 15pt "MS Sans Serif";
        }
        QPushButton#threadButton:hover {
            background-color: rgb(10, 190, 255);
        }
        QPushButton#likeButton {
            background-color: rgb(255, 255, 255);
            color: rgb(20, 255, 20);
            font-size: 14px;
            border-radius: 6px;
        }
        QPushButton#likeButton:hover {
            background-color: rgb(102, 102, 102);
        }
        QPushButton#followThreadButton {
            background-color: rgb(255, 255, 255);
            color: rgb(20, 255, 20);
            font-size: 14px;
            border-radius: 6px;
        }
        QPushButton#followThreadButton:hover {
            background-color: rgb(102, 102, 102);
        }
        QPushButton#replyThreadButton {
            background-color: rgb(255, 255, 255);
            color: rgb(20, 255, 20);
            font-size: 14px;
            border-radius: 6px;
        }
        QPushButton#replyThreadButton:hover {
            background-color: rgb(102, 102, 102);
        }
    )");
    }

    ///Place holder function, implement the comment opening method
    ///Already connected to button so do not remove this actual function just define it
    /* void ThreadBannerBox::OnClickBanner(const QString& threadID) {

        RepliesWindow* replyThread = new RepliesWindow(this, threadID.toStdString());
        replyThread->show();
    } */

    void ThreadBannerBox::OnClickLike(const QString& threadID) {
        //change button color call sql update
        std::cout << "Clicked++ \n";
        Utils::ThreadLike(proc::ip, proc::user, proc::password, proc::db, threadID.toStdString());
    }

    void ThreadBannerBox::OnClickFollowThread(const QString& threadID) {
        Utils::ThreadFollow(proc::ip, proc::user, proc::password, proc::db, threadID.toStdString());
    }

    ///Place holder function, implement the profile opening method
    ///Already connected to button so do not remove this actual function just define it
    void ThreadBannerBox::OnClickProfile(const QString& userID) {

    }

    void ThreadBannerBox::loadReplies(const QString& threadID) {
        QLayoutItem* item;
        while ((item = repliesLayout->takeAt(0)) != nullptr) {
            if (item->widget())
                item->widget()->deleteLater();
            delete item;
        }

        vector<vector<string>> replies =
            Utils::RepliesUpdate(proc::ip, proc::user, proc::password, proc::db, threadID.toStdString());

        if (replies.size() <= 1)
            return;

        // (skip [0] = thread)
        for (int i = 1; i < replies.size(); i++)
        {
            string userName = replies[i][0];
            string comment = replies[i][1];
            string id = replies[i][2];
            string replyField = replies[i][3];

            // Allows replies to be wrapped
            QWidget* rowWidget = new QWidget(repliesBox);
            QHBoxLayout* rowLayout = new QHBoxLayout(rowWidget);
            rowLayout->setContentsMargins(8, 4, 4, 8);
            rowLayout->setSizeConstraint(QLayout::SetMinimumSize);
            rowWidget->setMinimumHeight(80);
            rowWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

            QPushButton* pbUserName = new QPushButton(QString::fromStdString(userName));
            QPushButton* pbThreadCommentName = new QPushButton(QString::fromStdString(comment));
            QPushButton* pbThreadCommentID = new QPushButton(QString::fromStdString(id));
            QPushButton* pbCommentReply = new QPushButton(QString::fromStdString(replyField));
            QPushButton* pbReply = new QPushButton("R");

            // Sizing
            pbUserName->setMinimumWidth(140);
            pbUserName->setMinimumHeight(60);
            pbUserName->setFlat(true);

            pbThreadCommentName->setMinimumHeight(60);
            pbThreadCommentName->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

            pbThreadCommentID->setMinimumSize(125, 30);
            pbThreadCommentName->setMinimumHeight(60);

            pbCommentReply->setMinimumSize(125, 30);
            pbThreadCommentName->setMinimumHeight(60);

            pbReply->setMinimumSize(30, 30);
            pbReply->setStyleSheet("background-color: rgb(35, 193, 24);");

            connect(pbReply, &QPushButton::clicked, this, [this, threadID, id]() {
                PostReply* popup = new PostReply(this, threadID, QString::fromStdString(id));
                popup->exec();
            });


            // Add to layout
            rowLayout->addWidget(pbUserName);
            rowLayout->addWidget(pbThreadCommentName, 1);
            rowLayout->addWidget(pbThreadCommentID);
            rowLayout->addWidget(pbCommentReply);
            rowLayout->addWidget(pbReply);

            repliesLayout->addWidget(rowWidget);

        }
        repliesBox->setStyleSheet(R"(
            QPushButton {
                background-color: rgb(0, 170, 235);
                color: black;
                border-radius: 6px;
                padding: 4px;
                font: 12pt "MS Sans Serif";
            }
            QPushButton:hover {
                background-color: rgb(20, 190, 255);
            }
        )");
        repliesLayout->addStretch();
    }
