<<<<<<< HEAD
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "signup.h"
#include "ui_signup.h"
#include "homescreen.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    SignUp *SignUpSignUp = new SignUp;
    HomeScreen *HomeScreenHomeScreen = new HomeScreen;

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
=======
#include "mainwindow.h"
#include "ui_homescreen.h"
#include "ui_mainwindow.h"
#include "signup.h"
#include "ui_signup.h"
#include "homescreen.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    SignUp *SignUpSignUp = new SignUp;
    HomeScreen *HomeScreenHomeScreen = new HomeScreen;

    connect(ui->SignUp1,SIGNAL(clicked(bool)),this,SLOT(hide()));
    connect(ui->SignUp1,SIGNAL(clicked(bool)),SignUpSignUp,SLOT(show()));

    connect(SignUpSignUp->ui->Login2,SIGNAL(clicked(bool)),SignUpSignUp,SLOT(hide()));
    connect(SignUpSignUp->ui->Login2,SIGNAL(clicked(bool)),this,SLOT(show()));

    connect(ui->Login1,SIGNAL(clicked(bool)),this,SLOT(hide()));
    connect(ui->Login1,SIGNAL(clicked(bool)),HomeScreenHomeScreen,SLOT(show()));

    connect(HomeScreenHomeScreen->ui->LogOut,SIGNAL(clicked(bool)),HomeScreenHomeScreen,SLOT(hide()));
    connect(HomeScreenHomeScreen->ui->LogOut,SIGNAL(clicked(bool)),this,SLOT(show()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
>>>>>>> d0026905569ce309e51e78cf5bf594451ab92d8b
