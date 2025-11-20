#include "messagewindow.h"
#include "ui_messagewindow.h"
#include "../hdr/Utils.h"
#include "../hdr/proc.h"

MessageWindow::MessageWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MessageWindow)
{
    ui->setupUi(this);
    QScrollArea* scrollBoxMain = new QScrollArea();
    QVBoxLayout* vertLayout = new QVBoxLayout();

    //set the layout to be a verticle scroller
    scrollBoxMain->setLayout(vertLayout);

    //call thread info from sql and stores it into the vector
    //std::vector<std::vector<std::string>> DMVect;
    //DMVect = Utils::DMHistory(proc::ip, proc::user, proc::password, proc::db, "5");
    //DMVect = Utils::DMList(proc::ip, proc::user, proc::password, proc::db);

    ReloadInbox();
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
    pbUser->setFixedHeight(100);
    pbUser->setFixedWidth(150);
    pbUser->setFlat(true);

    QPushButton::connect(pbUser, &QPushButton::clicked, this, [this, user]() {
        ClickOnUserDM(user);
    });

    bannerBox->addWidget(pbUser);
    return bannerBox;
}

class QHBoxLayout* MessageWindow::CreateDMBanner(std::string user, std::string msg)
{
    ///create HBox to store the banners content
    QHBoxLayout* bannerBox = new QHBoxLayout();

    ///creating buttons
    QPushButton* pbUser = new QPushButton(QString::fromStdString(user));
    QPushButton* pbMsg = new QPushButton(QString::fromStdString(msg));

    ///resizing buttons
    pbUser->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    pbUser->setFixedHeight(100);
    pbUser->setFixedWidth(150);
    pbUser->setFlat(true);

    pbMsg->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    pbMsg->setFixedHeight(100);
    pbMsg->setFixedWidth(150);
    pbMsg->setFlat(true);

    bannerBox->addWidget(pbUser);
    bannerBox->addWidget(pbMsg);
    return bannerBox;
}

void MessageWindow::ClickOnUserDM(std::string user)
{
    std::vector<std::vector<std::string>> DMVect;
    DMVect = Utils::DMHistory(proc::ip, proc::user, proc::password, proc::db, user);

    //conveniently deletes both the layout and widget inside for some reason
    while(!ui->verticalLayout->isEmpty())
        delete ui->verticalLayout->takeAt(0)->layout()->takeAt(0)->widget();

    for (int i = 0; i < DMVect.size(); i++) {
        QHBoxLayout* messageBanner = CreateDMBanner(DMVect[i][0], DMVect[i][1]);
        ui->verticalLayout->addLayout(messageBanner);
    }

    ui->backButton->setVisible(true);
    ui->followerBox->setVisible(false);
    selectedUser = user;
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
    ui->followerBox->setVisible(true);
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
            ClickOnUserDM(userID);
        }

        return;
    }

    else if (mode == 1)
    {
        if (selectedUser != "\0")
        {
            Utils::SendDM(proc::ip, proc::user, proc::password, proc::db, selectedUser, text);
            ui->textBox->setPlainText("");
        }

        return;
    }
}

