#ifndef FOLLOWERS_H
#define FOLLOWERS_H

#include <QMainWindow>

namespace Ui {
class Followers;
}

class Followers : public QMainWindow
{
    Q_OBJECT

public:
    explicit Followers(QWidget *parent = nullptr);
    ~Followers();
    void on_Back_clicked();
    void onScroll(int value);
    void onClicked();

public:
    Ui::Followers *ui;
    int ProfileCount = 0;
    void loadProfiles(int count);
private slots:
    void on_Following_clicked();
};

#endif // FOLLOWERS_H
