<<<<<<< HEAD
#include "homescreen.h"
#include "ui_homescreen.h"
#include "profile.h"
#include <QTimer>
#include <QDateTime>
HomeScreen::HomeScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomeScreen)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timefunction()));
    timer->start(1000);
}

HomeScreen::~HomeScreen()
{
    delete ui;
}

void HomeScreen::on_Profile_clicked()
{
    Profile *ProfileProfile = new Profile;
    hide();
    ProfileProfile->show();
}
void HomeScreen::timefunction() {
    QTime time = QTime::currentTime();
    QString time_text = time.toString("hh : mm ap");
    ui->Clock->setText(time_text);
}

=======
#include "homescreen.h"
#include "ui_homescreen.h"
#include <QMessageBox>
HomeScreen::HomeScreen(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::HomeScreen)
{
    ui->setupUi(this);
}

HomeScreen::~HomeScreen()
{
    delete ui;
}

void HomeScreen::on_LogOut_clicked()
{

}


void HomeScreen::on_LogOut_clicked(bool checked)
{
    QMessageBox::question(this,tr("Logout"),tr("Do You Want To Logout"));
}

>>>>>>> d0026905569ce309e51e78cf5bf594451ab92d8b
