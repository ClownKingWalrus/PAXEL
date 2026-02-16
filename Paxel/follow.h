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

protected:
    void resizeEvent(QResizeEvent* event) override;

private slots:
    void FollowButton_clicked(string userID);
    void Followers_clicked(string userID);
    void Following_clicked(string userID);
    void BlockButton_clicked(string userID);
    void on_Back_clicked();
};

#endif // FOLLOW_H
