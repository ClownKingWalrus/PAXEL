#include "createboardorthread.h"
#include "ui_createboardorthread.h"
#include "../hdr/Utils.h"
#include "../hdr/proc.h"
#include "YourPaxelBoard.h"
#include <QMessageBox>
#include <qevent.h>
#include <QPixmap>
#include <QPainter>

CreateBoardOrThread::CreateBoardOrThread(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CreateBoardOrThread)
{
    ui->setupUi(this);
    //lay out in vertical format
    bannerLayout = new QVBoxLayout(ui->scrollAreaWidgetContents);
    ui->scrollAreaWidgetContents->setLayout(bannerLayout);

    //create Horzonatal boxes and return like 4 buttons per row
    LoadInterest(proc::ip, proc::user, proc::password, proc::db);

    ui->Back->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    ui->Submit->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    ui->Back->setMinimumSize(150, 45);
    ui->Back->setFlat(true);
    ui->Back->setFont(QFont("MS Sans Serif", 20));

    ui->Submit->setMinimumSize(250, 45);
    ui->Submit->setFlat(true);
    ui->Submit->setFont(QFont("MS Sans Serif", 20));

    ui->Title->setMinimumSize(250,250);
    ui->Title->setPlaceholderText("Enter Title...");
    ui->Title->setFont(QFont("MS Sans Serif", 20));

    QPixmap pixmap1(":/images/Images/NotePad.png");
    QPixmap scaledPixmap1 = pixmap1.scaled(120, 120, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->NotePad->setPixmap(scaledPixmap1);

    QPixmap pixmap2(":/images/Images/Pencil.png");
    QPixmap scaledPixmap2 = pixmap2.scaled(120, 120, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->Pencil->setPixmap(scaledPixmap2);
}

CreateBoardOrThread::~CreateBoardOrThread()
{
    delete ui;
}

void CreateBoardOrThread::LoadInterest(const std::string& host, const std::string& user, const std::string& password, const std::string& dbName) {

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

    resize(1000, 800);
}

void CreateBoardOrThread::onInterestButtonClick(std::string InterestID) {
    //the lambda honestly handels everything we need above
}

void CreateBoardOrThread::ChangeToThreadWindow() {
    std::cout << "Change to Threads Window Called\n\n\n";
    ui->verticalLayout_2->removeWidget(ui->scrollArea);
    ui->scrollArea->deleteLater();
    QLineEdit* lineEdit = new QLineEdit();
    lineEdit->setPlaceholderText("Enter Description...");
    lineEdit->setMinimumSize(250,250);
    lineEdit->setFont(QFont("MS Sans Serif", 20));
    ui->verticalLayout_2->addWidget(lineEdit);
    ui->Submit->disconnect(ui->Submit, &QPushButton::clicked, this, &CreateBoardOrThread::on_Submit_clicked);//unbinding
    ui->Submit->connect(ui->Submit, &QPushButton::clicked, this, &CreateBoardOrThread::ThreadSumbit);// this is called binding functions gamers, used in game dev btw
    std::cout << "Did it Bind????\n\n\n";
    this->isThread = true;
}

void CreateBoardOrThread::on_Submit_clicked()
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

    if (ui->Title->text().isEmpty()) {
        QMessageBox* box = new QMessageBox();
        box->setText("Please insert a title");
        box->show();
        return;
    }

    if (ui->Title->text().size() <= 2) {
        QMessageBox* box = new QMessageBox();
        box->setText("Title must be atleast 3 characters long");
        box->show();
        return;
    }

    if (!Utils::BoardNameCheck(proc::ip, proc::user, proc::password, proc::db, ui->Title->text().toStdString())) {
        QMessageBox* box = new QMessageBox();
        box->setText("BoardName Already Taken");
        box->show();
        return;
    }

    QMessageBox* box = new QMessageBox();
    box->setText("Creating board");
    box->show();
    Utils::CreateBoard(proc::ip, proc::user, proc::password, proc::db, ui->Title->text().toStdString(), IntrestList);

    CreateBoardWindow *BT = new CreateBoardWindow();
    if (!Utils::BoardNameCheck(proc::ip, proc::user, proc::password, proc::db, ui->Title->text().toStdString())) {
        QMessageBox* box = new QMessageBox();
        box->setText("Board Created");
        box->show();
        hide();
        BT->show();
        this->close();
        return;
    }
    hide();
    BT->show();
    this->close();
}

void CreateBoardOrThread::ThreadSumbit()
{
    if (ui->Title->text().isEmpty()) {
        QMessageBox* box = new QMessageBox();
        box->setText("Please insert a title");
        box->show();
        return;
    }

    if (ui->Title->text().size() <= 2) {
        QMessageBox* box = new QMessageBox();
        box->setText("Title must be atleast 3 characters long");
        box->show();
        return;
    }

    if (!Utils::BoardNameCheck(proc::ip, proc::user, proc::password, proc::db, ui->Title->text().toStdString())) {
        QMessageBox* box = new QMessageBox();
        box->setText("Thread Title Already Taken");
        box->show();
        return;
    }

    QMessageBox* box = new QMessageBox();
    box->setText("Creating Thread");
    box->show();
    Utils::CreateThread(proc::ip, proc::user, proc::password, proc::db, ui->Title->text().toStdString(), boardID);

    if (!Utils::ThreadNameCheck(proc::ip, proc::user, proc::password, proc::db, ui->Title->text().toStdString())) {
        QMessageBox* box = new QMessageBox();
        box->setText("Thread Created");
        box->show();
        return;
    }
}

void CreateBoardOrThread::resizeEvent(QResizeEvent* event) {
    QMainWindow::resizeEvent(event);
    QSize newSize = event->size();

    // Access the width and height
    int newWidth = newSize.width();
    int newHeight = newSize.height();
}

void CreateBoardOrThread::on_Back_clicked()
{
    this->hide();
    if (parentWidget()) {
        parentWidget()->show();
    }
}


