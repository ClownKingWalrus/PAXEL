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

