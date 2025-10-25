#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "signup.h"
#include "ui_signup.h"
#include "homescreen.h"
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap pixmap1(":/images/Images/clouds.png");
    QPixmap scaledPixmap1 = pixmap1.scaled(300, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->Clouds1->setPixmap(scaledPixmap1);

    QPixmap pixmap2(":/images/Images/Clouds reverse.png");
    QPixmap scaledPixmap2 = pixmap2.scaled(300, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->Clouds2->setPixmap(scaledPixmap2);

    QPixmap pixmap3(":/images/Images/Boards.png");
    QPixmap scaledPixmap3 = pixmap3.scaled(500, 500, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->Boards->setPixmap(scaledPixmap3);

    QPixmap pixmap4(":/images/Images/Pool.png");
    QPixmap scaledPixmap4 = pixmap4.scaled(300, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->Pool->setPixmap(scaledPixmap4);

    SignUp *SignUpSignUp = new SignUp;
    HomeScreen *HomeScreenHomeScreen = new HomeScreen;
   // DiscussionBoard *DiscussionBoardDiscussionBoard = new DiscussionBoard;

    connect(ui->SignUp1,SIGNAL(clicked(bool)),this,SLOT(hide()));
    connect(ui->SignUp1,SIGNAL(clicked(bool)),SignUpSignUp,SLOT(show()));

    connect(SignUpSignUp->ui->Login2,SIGNAL(clicked(bool)),SignUpSignUp,SLOT(hide()));
    connect(SignUpSignUp->ui->Login2,SIGNAL(clicked(bool)),this,SLOT(show()));

    connect(ui->Login1,SIGNAL(clicked(bool)),this,SLOT(hide()));
    connect(ui->Login1,SIGNAL(clicked(bool)),HomeScreenHomeScreen,SLOT(show()));

    // connect(HomeScreenHomeScreen->ui->LogOut,SIGNAL(clicked(bool)),HomeScreenHomeScreen,SLOT(hide()));
    // connect(HomeScreenHomeScreen->ui->LogOut,SIGNAL(clicked(bool)),this,SLOT(show()));

   // connect(HomeScreenHomeScreen->ui->pushButton_2,SIGNAL(clicked(bool)),this,SLOT(hide()));
   // connect(HomeScreenHomeScreen->ui->pushButton_2,SIGNAL(clicked(bool)),DiscussionBoardDiscussionBoard,SLOT(show()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
