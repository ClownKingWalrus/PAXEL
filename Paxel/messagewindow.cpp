#include "messagewindow.h"
#include "ui_messagewindow.h"
#include "../hdr/Utils.h"
#include "../hdr/proc.h"
#include <QMessageBox>

MessageWindow::MessageWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MessageWindow)
{
    ui->setupUi(this);
    QScrollArea* scrollBoxMain = new QScrollArea();
    QVBoxLayout* vertLayout = new QVBoxLayout();

    //set the layout to be a verticle scroller
    scrollBoxMain->setLayout(vertLayout);

    ReloadInbox();

    std::list<std::string> FollowingVect;
    FollowingVect = Utils::FollowingList(proc::ip, proc::user, proc::password, proc::db);

    int originalSize = FollowingVect.size();

    for (int i = 0; i < originalSize; i++) {
        QHBoxLayout* messageBanner = CreateInboxBanner(FollowingVect.front());
        ui->verticalLayout_3->addLayout(messageBanner);
        FollowingVect.pop_front();
    }

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
}

MessageWindow::~MessageWindow()
{
    delete ui;
}

class QHBoxLayout* MessageWindow::CreateInboxBanner(std::string user)
{
    ///create HBox to store the banners content
    QHBoxLayout* bannerBox = new QHBoxLayout();

    ///creating buttons
    QPushButton* pbUser = new QPushButton(QString::fromStdString(user));

    ///resizing buttons
    pbUser->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    pbUser->setFixedHeight(60);
    pbUser->setFixedWidth(250);
    pbUser->setFlat(true);

    QPushButton::connect(pbUser, &QPushButton::clicked, this, [this, user]() {
        ClickOnUserDM(user);
    });

    bannerBox->addWidget(pbUser);
    return bannerBox;
}

class QHBoxLayout* MessageWindow::CreateDMBanner(std::string user, std::string msg, std::string dateTime)
{
    ///create HBox to store the banners content
    QHBoxLayout* bannerBox = new QHBoxLayout();

    ///creating buttons
    QPushButton* pbUser = new QPushButton(QString::fromStdString(user));
    QPushButton* pbMsg = new QPushButton(QString::fromStdString(msg));
    QPushButton* pbDateTime = new QPushButton(QString::fromStdString(dateTime));

    ///resizing buttons
    pbUser->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    pbUser->setFixedHeight(100);
    pbUser->setFixedWidth(150);
    pbUser->setFlat(true);

    pbMsg->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed));
    pbMsg->setFixedHeight(100);
    pbMsg->setFlat(true);

    pbDateTime->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    pbDateTime->setFixedHeight(100);
    pbDateTime->setFixedWidth(225);
    pbDateTime->setFlat(true);

    bannerBox->addWidget(pbUser);
    bannerBox->addWidget(pbMsg);
    bannerBox->addWidget(pbDateTime);

    return bannerBox;
}

void MessageWindow::ClickOnUserDM(std::string user)
{
    std::vector<std::vector<std::string>> DMVect;
    DMVect = Utils::DMHistory(proc::ip, proc::user, proc::password, proc::db, Utils::UserLookup(proc::ip, proc::user, proc::password, proc::db, user));

    //conveniently deletes both the layout and widget inside for some reason
    while(!ui->verticalLayout->isEmpty())
        delete ui->verticalLayout->takeAt(0)->layout()->takeAt(0)->widget();

    for (int i = 0; i < DMVect.size(); i++) {
        //make the datetime look a little better
        DMVect[i][2].pop_back();
        DMVect[i][2].pop_back();
        DMVect[i][2].pop_back();
        DMVect[i][2].insert(11,"\n");

        QHBoxLayout* messageBanner = CreateDMBanner(DMVect[i][0], DMVect[i][1], DMVect[i][2]);
        ui->verticalLayout->addLayout(messageBanner);
    }

    ui->backButton->setVisible(true);
    ui->scrollArea2->setVisible(false);
    selectedUser = user;
    ui->selectedUser->setText(QString::fromStdString(selectedUser));
    mode = 1;
}

void MessageWindow::ReloadInbox(void)
{
    std::list<std::string> DMVect;
    DMVect = Utils::DMList(proc::ip, proc::user, proc::password, proc::db);

    int originalSize = DMVect.size();

    for (int i = 0; i < originalSize; i++) {
        QHBoxLayout* messageBanner = CreateInboxBanner(DMVect.front());
        ui->verticalLayout->addLayout(messageBanner);
        DMVect.pop_front();
    }

    ui->backButton->setVisible(false);
    ui->scrollArea2->setVisible(true);
    selectedUser = "\0";
    mode = 0;
}

void MessageWindow::on_backButton_clicked()
{
    //empty the messages
    while(!ui->verticalLayout->isEmpty())
    {
        QLayout* hbox = ui->verticalLayout->takeAt(0)->layout();

        while(!hbox->isEmpty())
        {
            QWidget* button = hbox->takeAt(0)->widget();
            delete button;
        }
        delete hbox;
    }

    //reload the list
    ReloadInbox();
}


void MessageWindow::on_sendButton_clicked()
{
    std::string text = ui->textBox->toPlainText().toStdString();

    if(mode == 0)
    {
        std::string userID = Utils::UserLookup(proc::ip, proc::user, proc::password, proc::db, text);

        if (userID != "\0")
        {
            ui->textBox->setPlainText("");
            ClickOnUserDM(text);
            return;
        }

        QMessageBox* box = new QMessageBox();
        box->setText("User not found.");
        box->show();
        return;
    }

    else if (mode == 1)
    {
        if (selectedUser != "\0")
        {
            std::string msgRecipient = Utils::UserLookup(proc::ip, proc::user, proc::password, proc::db, selectedUser);

            Utils::SendDM(proc::ip, proc::user, proc::password, proc::db, msgRecipient, text);
            ui->textBox->setPlainText("");

            //empty the messages
            while(!ui->verticalLayout->isEmpty())
            {
                QLayout* hbox = ui->verticalLayout->takeAt(0)->layout();

                while(!hbox->isEmpty())
                {
                    QWidget* button = hbox->takeAt(0)->widget();
                    delete button;
                }
                delete hbox;
            }

            //reload
            ClickOnUserDM(selectedUser);
        }

        return;
    }
}

