#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "signup.h"
#include "ui_signup.h"
#include "homescreen.h"
// #include "ui_discussionboard.h"
// #include "discussionboard.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    SignUp *SignUpSignUp = new SignUp;
    HomeScreen *HomeScreenHomeScreen = new HomeScreen;
   // DiscussionBoard *DiscussionBoardDiscussionBoard = new DiscussionBoard;

    connect(ui->SignUp1,SIGNAL(clicked(bool)),this,SLOT(hide()));
    connect(ui->SignUp1,SIGNAL(clicked(bool)),SignUpSignUp,SLOT(show()));

    connect(SignUpSignUp->ui->Login2,SIGNAL(clicked(bool)),SignUpSignUp,SLOT(hide()));
    connect(SignUpSignUp->ui->Login2,SIGNAL(clicked(bool)),this,SLOT(show()));

    connect(ui->Login1,SIGNAL(clicked(bool)),this,SLOT(hide()));
    connect(ui->Login1,SIGNAL(clicked(bool)),HomeScreenHomeScreen,SLOT(show()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
