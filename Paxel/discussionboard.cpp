#include "discussionboard.h"
#include "ui_discussionboard.h"
#include "../hdr/Utils.h"

#include <QScrollBar>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
using namespace std;

DiscussionBoard::DiscussionBoard(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DiscussionBoard)
{
    ui->setupUi(this);
     connect(ui->scrollArea->verticalScrollBar(), &QScrollBar::valueChanged,
            this, &DiscussionBoard::onScroll);

    loadBoards("73.17.181.142", "paxel", "Password1!", "paxel");;
}
DiscussionBoard::~DiscussionBoard()
{
    delete ui;
}

void DiscussionBoard::loadBoards(const string& host, const string& user, const string& password, const string& dbName) {

    vector<pair<string, string>> boardVect;
    boardVect = Utils::BoardUpdate(host, user, password, dbName);

    for (const auto& board : boardVect ) {
        QHBoxLayout* boardBanner = CreateBoardBanner(board.first, board.second);
        ui->verticalLayout->addLayout(boardBanner);
    }
}

QHBoxLayout* DiscussionBoard::CreateBoardBanner(const string& boardID, const string& boardName) {
    QHBoxLayout* bannerBox = new QHBoxLayout();

    QPushButton* idButton = new QPushButton(QString::fromStdString(boardID));
    QPushButton* titleButton = new QPushButton(QString::fromStdString(boardName));

    idButton->setFixedSize(150, 80);
    idButton->setFlat(true);

    titleButton->setMinimumSize(250, 80);
    titleButton->setFlat(true);

    bannerBox->addWidget(idButton);
    bannerBox->addWidget(titleButton);

    return bannerBox;
}

void DiscussionBoard::onScroll(int value)
{
    QScrollBar* bar = ui->scrollArea->verticalScrollBar();
    if (value >= bar->maximum() - 50) {
        qDebug() << "User scrolled near bottom";
        // You can implement paginated loading if needed
    }
}


