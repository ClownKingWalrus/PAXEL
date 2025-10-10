<<<<<<< HEAD
#include "signup.h"
#include "ui_signup.h"

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
=======
#include "signup.h"
#include "ui_signup.h"

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
>>>>>>> d0026905569ce309e51e78cf5bf594451ab92d8b
