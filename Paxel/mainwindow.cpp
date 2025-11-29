#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "signup.h"
#include "ui_signup.h"
#include "homescreen.h"
#include "windowsettings.h"
#include "../hdr/Utils.h"
#include "../hdr/proc.h"
#include <QPixmap>
#include <QScreen>
#include <qevent.h>

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

    connect(ui->SignUp1,SIGNAL(clicked(bool)),this,SLOT(hide()));
    connect(ui->SignUp1,SIGNAL(clicked(bool)),SignUpSignUp,SLOT(show()));

    connect(SignUpSignUp->ui->Login2,SIGNAL(clicked(bool)),SignUpSignUp,SLOT(hide()));
    connect(SignUpSignUp->ui->Login2,SIGNAL(clicked(bool)),this,SLOT(show()));

    QPushButton::connect(ui->Login1, &QPushButton::clicked, this, [this]() {
        LoginButton();
    });


    QCheckBox* myCheckBox = ui -> checkBox;
    myCheckBox->setStyleSheet("QCheckBox::indicator:checked { background-color: black; }"
                              "QCheckBox::indicator {border: 1px solid black; }"
                              "QCheckBox::indicator:unchecked {background-color: white;}");

    connect(myCheckBox, &QCheckBox::checkStateChanged, this, [=](Qt::CheckState state) {
        // Check if the checkbox is checked
        if (state == Qt::Checked) {
            // If it's checked, set the echo mode of the line edit to normal
            ui->lineEdit_2->setEchoMode(QLineEdit::Normal);
        }
        else {
            ui->lineEdit_2->setEchoMode(QLineEdit::Password);
        }
    });
    resize(1000, 800);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showEvent(QShowEvent *event)
{
    QMainWindow::showEvent(event);
    centerOnScreen(this);
}

void MainWindow::LoginButton() {
    if (Utils::Login(proc::ip, proc::user, proc::password, proc::db, ui->lineEdit->text().toStdString(), ui->lineEdit_2->text().toStdString())) {
        std::cout << "+++Login Succeded+++\n";
        HomeScreen* Homescreen = new HomeScreen();
        Homescreen->show();
        this->close();
    } else {
        return;
    }
}

void MainWindow::resizeEvent(QResizeEvent* event) {
    QMainWindow::resizeEvent(event);
    QSize newSize = event->size();

    // Access the width and height
    int newWidth = newSize.width();
    int newHeight = newSize.height();
}
