#ifndef SIGNUP_H
#define SIGNUP_H

#include <QMainWindow>

namespace Ui {
class SignUp;
}

class SignUp : public QMainWindow
{
    Q_OBJECT

public:
    explicit SignUp(QWidget *parent = nullptr);
    ~SignUp();

public:
    Ui::SignUp *ui;
private:
        bool over18 = false;

private slots:
    void on_YesButton_clicked();
    void on_NoButton_clicked();
    void on_SignUp2_clicked();
};

#endif // SIGNUP_H
