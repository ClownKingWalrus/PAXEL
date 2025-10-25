#ifndef FOLLOW_H
#define FOLLOW_H

#include <QMainWindow>
#include <QString>

namespace Ui {
class Follow;
}

class Follow : public QMainWindow
{
    Q_OBJECT

public:
    explicit Follow(QWidget *parent = nullptr);
    ~Follow();

public:
    Ui::Follow *ui;
private slots:
    void on_FollowButton_clicked();
    void on_Followers_clicked();
    void on_Following_clicked();
    void on_Back_clicked();
};

#endif // FOLLOW_H
