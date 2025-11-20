#ifndef PROFILE_H
#define PROFILE_H

#include <QMainWindow>
using namespace std;

namespace Ui {
class Profile;
}

class Profile : public QMainWindow
{
    Q_OBJECT

public:
    explicit Profile(QWidget *parent = nullptr, string userID = "");
    ~Profile();

public slots:
    void on_Logout_clicked();

private slots:
    void Back_clicked();
    void Followers_clicked(string userID);
    void Following_clicked(string userID);

    void on_AddInterestsProfile_clicked();

public:
    Ui::Profile *ui;

protected:
    void resizeEvent(QResizeEvent* event) override;
};

#endif // PROFILE_H
