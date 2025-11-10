#include "threadbannerbox.h"
#include <QPushButton>
#include <QWidget>
#include <QHBoxLayout>
#include "replieswindow.h"
#include "../hdr/Utils.h"
#include "../hdr/proc.h"

    ThreadBannerBox::ThreadBannerBox(const QString& userName,
                                       const QString& threadName,
                                       const QString& threadID,
                                       QWidget* parent)
                                       :QWidget(parent) {
        setMinimumHeight(150);
        setMaximumHeight(200);

        profileButton = new QPushButton(userName, this);
        profileButton->setFixedSize(100,100);
        profileButton->setFlat(true);
        profileButton->setObjectName("profileButton");

        threadButton = new QPushButton(threadName, this);
        threadButton->setMinimumHeight(150);
        threadButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        threadButton->setObjectName("threadButton");

        likeButton = new QPushButton("\u25B2", threadButton);
        likeButton->setMinimumSize(25,30);
        likeButton->setMaximumSize(50,60);
        likeButton->setObjectName("likeButton");

        QPushButton::connect(profileButton, &QPushButton::clicked, this, [this, userName]() {
            OnClickProfile(userName);
        });

        //connect functions saving each unique arg
        QPushButton::connect(threadButton, &QPushButton::clicked, this, [this, threadID]() {
            OnClickBanner(threadID);
        });

        QPushButton::connect(likeButton, &QPushButton::clicked, this, [this, threadID]() {
            OnClickLike(threadID, Utils::GetUserID());
        });

        QHBoxLayout* bannerBox = new QHBoxLayout(this);
        bannerBox->setContentsMargins(8,8,8,8);
        bannerBox->setSpacing(8);
        bannerBox->addWidget(profileButton);
        bannerBox->addWidget(threadButton, 1); //sets streching to true

        setObjectName("ThreadBannerBox");
        setAttribute(Qt::WA_StyledBackground, true);
        setAutoFillBackground(true);

        setStyleSheet(R"(
        #ThreadBannerBox {
            background-color: rgb(44, 44, 44);
            border: 1px solid rgb(68, 68, 68);
            border-radius: 8px;
            border-bottom: 8px solid rgb(44, 44, 44);
        }
        QPushButton#threadButton {
            background-color: rgb(0, 170, 245);
            color: rgb(255, 255, 255);
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
    )");
    }

    ///Place holder function, implement the comment opening method
    ///Already connected to button so do not remove this actual function just define it
    void ThreadBannerBox::OnClickBanner(const QString& threadID) {

        RepliesWindow* replyThread = new RepliesWindow(this, threadID.toStdString());
        replyThread->show();
    }

    void ThreadBannerBox::OnClickLike(const QString& threadID, const std::string& userID) {
        //change button color call sql update
        std::cout << "Clicked++ \n";
        Utils::ThreadLike(proc::ip, proc::user, proc::password, proc::db, threadID.toStdString(), userID);
    }

    ///Place holder function, implement the profile opening method
    ///Already connected to button so do not remove this actual function just define it
    void ThreadBannerBox::OnClickProfile(const QString& userID) {

    }

    void ThreadBannerBox::resizeEvent(QResizeEvent* event)
    {
        QWidget::resizeEvent(event);
        int margin = 8;
        likeButton->move(threadButton->width() - likeButton->width() - margin, //width
                         threadButton->height() - likeButton->height() - margin); //height
        likeButton->raise(); //put above the thread button
    }

