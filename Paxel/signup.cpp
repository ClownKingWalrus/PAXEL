#include "signup.h"
#include "ui_signup.h"
#include "../hdr/Utils.h"
#include "../hdr/proc.h"
#include <QRegularExpression>
#include <QMessageBox>

SignUp::SignUp(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SignUp)
{
    ui->setupUi(this);
}

SignUp::~SignUp()
{
    delete ui;
}




void SignUp::on_YesButton_clicked()
{
    this->over18 = true;
}


void SignUp::on_NoButton_clicked()
{
    this->over18 = false;
}


void SignUp::on_SignUp2_clicked()
{
    if (!this->over18) {
        QMessageBox* box = new QMessageBox();
        box->setText("If you are not over 18 you must leave");
        box->show();
        return;
    }

    if (ui->lineEditUserName->text().toStdString().size() <= 2) {
        QMessageBox* box = new QMessageBox();
        box->setText("Invalid Username, Usernames must be 3 or more characters long");
        box->show();
        return;
    }
    if (ui->lineEditPassword->text().toStdString().size() <= 3) {
        QMessageBox* box = new QMessageBox();
        box->setText("Password must be longer than 3 characters");
        box->show();
        return;
    }

    //regex email validation
    if (ui->lineEditEmail->text().toStdString().empty()) {
        QMessageBox* box = new QMessageBox();
        box->setText("Email is empty");
        box->show();
        return;
    }

    QRegularExpression regex("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b", QRegularExpression::CaseInsensitiveOption);

    if (!regex.match(ui->lineEditEmail->text()).hasMatch()) {
        QMessageBox* box = new QMessageBox();
        box->setText("Invalid Email");
        box->show();
        return;
    }



    //should be the last check as it's the most taxing
    //if UsernameChecker returns true that means there is no username in the database implying its free to use
    if (!Utils::UsernameChecker(proc::ip, proc::user, proc::password, proc::db, ui->lineEditUserName->text().toStdString())) {
        QMessageBox* box = new QMessageBox();
        box->setText("Username already taken");
        box->show();
        return;
    }

    if (!Utils::EmailChecker(proc::ip, proc::user, proc::password, proc::db, ui->lineEditEmail->text().toStdString())) {
        QMessageBox* box = new QMessageBox();
        box->setText("Email already in use");
        box->show();
        return;
    }

    QMessageBox* box = new QMessageBox();
    box->setText("Attempting to create Paxel Account");
    box->show();

    Utils::CreateProfile(proc::ip, proc::user, proc::password, proc::db, ui->lineEditUserName->text().toStdString(), ui->lineEditPassword->text().toStdString(), ui->lineEditEmail->text().toStdString());
    if (Utils::UsernameChecker(proc::ip, proc::user, proc::password, proc::db, ui->lineEditUserName->text().toStdString())) {
        QMessageBox* box = new QMessageBox();
        box->setText("Account Created");
        box->show();
        //at this point account created so we can take the user to the interest selector
    } else {
        QMessageBox* box = new QMessageBox();
        box->setText("Account Failed");
        box->show();
        return;
    }


    return;
}

