#ifndef PROFILE_H
#define PROFILE_H

#include <QMainWindow>

namespace Ui {
class Profile;
}

class Profile : public QMainWindow
{
    Q_OBJECT

public:
    explicit Profile(QWidget *parent = nullptr);
    ~Profile();
    void FollowCount();

public slots:
    void on_Logout_clicked();

private slots:
    void on_Back_clicked();
    void on_Followers_clicked();
    void on_Following_clicked();

public:
    Ui::Profile *ui;
};

#endif // PROFILE_H
