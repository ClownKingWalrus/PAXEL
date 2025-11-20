#ifndef FOLLOWERS_H
#define FOLLOWERS_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>

using namespace std;

namespace Ui {
class Followers;
}
class Followers : public QMainWindow
{
    Q_OBJECT

public:
    explicit Followers(QWidget *parent = nullptr, string userID = "");
    ~Followers();

private slots:
    void Following_clicked(string userID);
    void Back_clicked(string userID);

protected:
    void resizeEvent(QResizeEvent* event) override;

public:
    Ui::Followers *ui;

private:
    void onClicked(string followerID);
    class QHBoxLayout* CreateProfileBanner(const string& userID, const string& username);
    QVBoxLayout* ProfileLayout;
    void loadProfiles(const string& host, const string& user, const string& password, const string& dbName, string userID);
};

#endif // FOLLOWERS_H
