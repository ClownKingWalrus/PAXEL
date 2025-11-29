#ifndef FOLLOWING_H
#define FOLLOWING_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>

using namespace std;

namespace Ui {
class Following;
}

class Following : public QMainWindow
{
    Q_OBJECT

public:
    explicit Following(QWidget *parent = nullptr, string userID = "");
    ~Following();

protected:
    void resizeEvent(QResizeEvent* event) override;

private slots:
    void Followers_2_clicked(string userID);
    void Back_clicked(string userID);

public:
    Ui::Following *ui;

private:
    void onClicked(string followingID);
    class QHBoxLayout* CreateProfileBanner(const string& userID, const string& username);
    QVBoxLayout* ProfileLayout;
    void loadProfiles(const string& host, const string& user, const string& password, const string& dbName, string userID);
};

#endif // FOLLOWING_H
