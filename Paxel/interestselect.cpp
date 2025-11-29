#include "interestselect.h"
#include "ui_interestselect.h"
#include "../hdr/Utils.h"
#include "../hdr/proc.h"
#include "mainwindow.h"
#include <QMessageBox>


interestselect::interestselect(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::interestselect)
{
    ui->setupUi(this);
    bannerLayout = new QVBoxLayout(ui->scrollAreaWidgetContents);
    ui->scrollAreaWidgetContents->setLayout(bannerLayout);
    LoadInterest(proc::ip, proc::user, proc::password, proc::db);

}

void interestselect::LoadInterest(const std::string& host, const std::string& user, const std::string& password, const std::string& dbName) {

    std::vector<std::pair<std::string, std::string>> boardVect;
    boardVect = Utils::GetInterestButtons(host, user, password, dbName);

    QHBoxLayout* boardBanner = new QHBoxLayout();
    for (int i = 0; i < boardVect.size(); i++) {
        QPushButton* titleButton = new QPushButton(QString::fromStdString(boardVect[i].first));
        titleButton->setStyleSheet(R"(
                                    QPushButton {
                                        font: 700 17pt "MS Sans Serif";
                                        color: rgb(255, 255, 255);
                                        background-color: rgb(139, 0, 0); /*dark red */
                                    }
                                    QPushButton:hover {
                                        background-color: rgb(178, 34, 34); /* lighter red on hover*/
                                    }
                                    )");
        bool* clicked = new bool(false);
        std::string intrestID = boardVect[i].second;

        QPushButton::connect(titleButton, &QPushButton::clicked, this, [this, intrestID, clicked, titleButton]() {
            if (*clicked == false) {
                *clicked = true;
                titleButton->setStyleSheet(R"(
                                            QPushButton {
                                                font: 700 17pt "MS Sans Serif";
                                                color: rgb(0, 0, 0);
                                                background-color: rgb(35, 193, 24); /*dark green*/
                                            }
                                            QPushButton:hover {
                                                background-color: rgb(35, 203, 24); /*greener on hover*/
                                            }
                                            )");
                interestButtonMap[intrestID] = true;
                onInterestButtonClick(intrestID);
            } else {
                *clicked = false;
                interestButtonMap[intrestID] = false;
                titleButton->setStyleSheet(R"(
                                            QPushButton {
                                                font: 700 17pt "MS Sans Serif";
                                                color: rgb(255, 255, 255);
                                                background-color: rgb(139, 0, 0); /* dark red*/
                                            }
                                            QPushButton:hover {
                                                background-color: rgb(178, 34, 34); /* lighter red*/
                                            }
                                            )");
                onInterestButtonClick(intrestID);
            }
        });
        boardBanner->addWidget(titleButton);
        if (i % 4 == 0) {
            bannerLayout->addLayout(boardBanner);
            boardBanner = new QHBoxLayout();
        }
    }
    //encase its like 1,2,3 or some variation
    if (boardVect.size() % 4 != 0) {
        boardBanner->addLayout(boardBanner);
    }
}

void interestselect::onInterestButtonClick(std::string InterestID) {
    //the lambda honestly handels everything we need above
}

interestselect::~interestselect()
{
    delete ui;
}


void interestselect::on_pushButton_clicked()
{
    if (interestButtonMap.empty()) {
        QMessageBox* box = new QMessageBox();
        box->setText("Select an interest");
        box->show();
        return;
    }
    std::vector<std::string> IntrestList;

    bool anySelectedButton = false;
    for (const auto &pair : interestButtonMap) {
        if (pair.second == true) {
            IntrestList.push_back(pair.first);
            anySelectedButton = true;
        }
    }

    if (!anySelectedButton) {
        QMessageBox* box = new QMessageBox();
        box->setText("Select an interest");
        box->show();
        return;
    }


    std::cout << "\nPOP1\n";
    if (!Utils::UserInterestCheck(proc::ip, proc::user, proc::password, proc::db, IntrestList, userName)) {
        QMessageBox* box = new QMessageBox();
        box->setText("Interests not set");
        box->show();
        return;
    }

    std::cout << "InterestList Size: " << IntrestList.size() << "\n";
    Utils::AddInterest(proc::ip, proc::user, proc::password, proc::db, IntrestList, userName);

    std::cout << "passed 1\n";
    if (Utils::UserInterestCheck(proc::ip, proc::user, proc::password, proc::db, IntrestList)) {
        QMessageBox* box = new QMessageBox();
        box->setText("Interests set");
        box->show();
    } else {
        std::cout << "Failed to set interest or somthign\n";
    }
    QMessageBox* box = new QMessageBox();
    box->setText("Please Login with your new credentials");
    box->show();
    MainWindow* mainWin = new MainWindow();
    mainWin->show();
    parentWidget()->close();
    this->close();
}


