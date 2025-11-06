#include "YourPaxelBoard.h"
#include "ui_YourPaxelBoard.h"
#include "homescreen.h"
#include "../hdr/Utils.h"
#include "threadmenuwindow.h"
#include "createboardorthread.h"

#include <QMessageBox>
#include <QPainter>

CreateBoardWindow::CreateBoardWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CreateBoardWindow)
{
    ui->setupUi(this);

    bannerLayout = new QVBoxLayout(ui->scrollAreaWidgetContents);
    ui->scrollAreaWidgetContents->setLayout(bannerLayout);

    loadOwnBoards(proc::ip, proc::user, proc::password, proc::db, proc::userID);

    QPixmap pixmapHS4(":/images/Images/Paxel banner.png");
    QPixmap scaledPixmapHS4 = pixmapHS4.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QPainter painter(&scaledPixmapHS4);
    painter.setPen(Qt::black);
    painter.setFont(QFont("MS Sans Serif", 16, QFont::Bold));
    painter.drawText(scaledPixmapHS4.rect(), Qt::AlignCenter, "Paxel Boards");
    painter.end();
    ui->Banner->setPixmap(scaledPixmapHS4);

}

void CreateBoardWindow::loadOwnBoards(const std::string& host, const std::string& user, const std::string& password, const std::string& dbName, int UserID) {

    std::vector<std::pair<std::string, std::string>> boardVect;
    boardVect = Utils::GetOwnBoards(host, user, password, dbName, UserID);
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

    idButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    titleButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    idButton->setMinimumSize(150, 45);
    idButton->setFlat(true);

    titleButton->setMinimumSize(250, 45);
    titleButton->setFlat(true);

    idButton->setStyleSheet(
        "QPushButton { background-color: rgb(35, 242, 24); color: black; font-family: MS Sans Serif; font-weight: bold; }"  // green
        "border-radius: 8px;"        // rounded corners
        );

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

    return bannerBox;
}

void CreateBoardWindow::ClickOnBoardName (string boardID) {
    ThreadMenuWindow* threadList = new ThreadMenuWindow(this, boardID);
    threadList->show();

}

void CreateBoardWindow::on_pushButton_clicked()
{
    // if (boardCount > 300) {
    //     QMessageBox* box = new QMessageBox();
    //     box->setText("You own too many boards to create any more");
    //     box->show();
    //     return;
    // }
    //assuming not too many boards
    CreateBoardOrThread* createBoardWindow = new CreateBoardOrThread(this);
    createBoardWindow->show();
}


void CreateBoardWindow::on_HomeScreenButton_clicked()
{
    this->close();
}

