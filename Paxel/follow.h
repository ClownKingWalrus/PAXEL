#ifndef FOLLOW_H
#define FOLLOW_H

#include <QMainWindow>
#include <QString>

using namespace std;

namespace Ui {
class Follow;
}

class Follow : public QMainWindow
{
    Q_OBJECT

public:
    explicit Follow(QWidget *parent = nullptr, string userID = "");
    ~Follow();

public:
    Ui::Follow *ui;
private slots:
    void FollowButton_clicked(string userID, string userID2);
    void Followers_clicked(string userID);
    void Following_clicked(string userID);
};

#endif // FOLLOW_H
