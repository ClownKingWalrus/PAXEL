#include "YourPaxelBoard.h"
#include "ui_YourPaxelBoard.h"
#include "homescreen.h"
#include "../hdr/Utils.h"
#include "profile.h"
#include "threadmenuwindow.h"
#include "profilepicture.h"
#include "createboardorthread.h"
#include "../hdr/proc.h"

#include <QMessageBox>
#include <QPainter>
#include <qevent.h>

CreateBoardWindow::CreateBoardWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CreateBoardWindow)
{
    ui->setupUi(this);

    bannerLayout = new QVBoxLayout(ui->scrollAreaWidgetContents);
    ui->scrollAreaWidgetContents->setLayout(bannerLayout);

    loadOwnBoards(proc::ip, proc::user, proc::password, proc::db);

    QPixmap pixmapHS4(":/images/Images/Paxel banner.png");
    QPixmap scaledPixmapHS4 = pixmapHS4.scaled(150, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QPainter painter(&scaledPixmapHS4);
    painter.setPen(Qt::black);
    painter.setFont(QFont("MS Sans Serif", 16, QFont::Bold));
    painter.drawText(scaledPixmapHS4.rect(), Qt::AlignCenter, "Paxel Boards");
    painter.end();
    ui->Banner->setPixmap(scaledPixmapHS4);

    resize(1000, 800);
}

void CreateBoardWindow::loadOwnBoards(const std::string& host, const std::string& user, const std::string& password, const std::string& dbName) {

    std::vector<std::pair<std::string, std::string>> boardVect;
    boardVect = Utils::GetOwnBoards(host, user, password, dbName);
    HomeScreen temp;

    for (const auto& board : boardVect ) {
        QHBoxLayout* boardBanner = CreateBoardBanner(board.first, board.second);
        boardCount++;
        bannerLayout->addLayout(boardBanner);
    }
}

CreateBoardWindow::~CreateBoardWindow()
{
    delete ui;
}

QHBoxLayout* CreateBoardWindow::CreateBoardBanner(const string& boardID, const string& boardName) {
    QHBoxLayout* bannerBox = new QHBoxLayout();

    QPushButton* idButton = new QPushButton(QString::fromStdString(boardID));
    QPushButton* titleButton = new QPushButton(QString::fromStdString(boardName));

    std::string userTemp = boardID; //not sure if touching the memory is dangroud this is a failsafe
    int userID = Utils::GetUserIDFromBoardID(proc::ip, proc::user, proc::password, proc::db, std::stoi(userTemp));
    //load the pixmap if it exist
    QPixmap pix = ProfilePicture::CreatePixMapFromSql(userID);
    if (!pix.isNull()) {
        QIcon icon(pix.scaled(64, 64, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        idButton->setIcon(icon);
        idButton->setIconSize(idButton->size());
        idButton->setText("");
        idButton->setStyleSheet(
            "QPushButton {"
            "   color: rgba(0,0,0,0);"               /* hide text */
            "   border: none;"
            "   border-radius: 8px;"
            "   background-color: rgb(35, 242, 24);" /* button background */
            "   font-family: 'MS Sans Serif';"
            "   font-weight: bold;"
            "   text-align: center;"
            "}"
            "QPushButton:hover {"
            "   background-color: rgb(50, 200, 30);"  /* hover color */
            "}"
            );
    }

    idButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    titleButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    idButton->setMinimumSize(150, 45);
    idButton->setFlat(true);

    titleButton->setMinimumSize(250, 45);
    titleButton->setFlat(true);

    titleButton->setStyleSheet(
        "QPushButton { background-color: rgb(8, 136, 245); color: black; font-family: MS Sans Serif; font-weight: bold;}"  // blue
        "border-radius: 8px;"
        );

    bannerBox->addWidget(idButton, 1);
    bannerBox->addWidget(titleButton, 3);

    bannerBox->setContentsMargins(10, 5, 10, 5);
    bannerBox->setSpacing(15);

    QPushButton::connect(titleButton, &QPushButton::clicked, this, [this, boardID]() {
        ClickOnBoardName(boardID);
    });

    QPushButton::connect(idButton, &QPushButton::clicked, this, [this, userID]() {
        ClickID(to_string(userID));
    });


    return bannerBox;
}

void CreateBoardWindow::ClickOnBoardName (string boardID) {
    ThreadMenuWindow* threadList = new ThreadMenuWindow(this, boardID);
    threadList->show();
    hide();
}

void CreateBoardWindow::ClickID(string userID) {
    Profile *userProf = new Profile(this);
    userProf->show();
    hide();
}

void CreateBoardWindow::on_pushButton_clicked() {
    CreateBoardOrThread* createBoardWindow = new CreateBoardOrThread(this);
    createBoardWindow->show();
    hide();
}


void CreateBoardWindow::on_HomeScreenButton_clicked()
{
    this->hide();
    if (parentWidget()) {
        parentWidget()->show();
    }
}

void CreateBoardWindow::resizeEvent(QResizeEvent* event) {
    QMainWindow::resizeEvent(event);
    QSize newSize = event->size();

    // Access the width and height
    int newWidth = newSize.width();
    int newHeight = newSize.height();
}