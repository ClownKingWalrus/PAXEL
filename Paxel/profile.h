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

private slots:
    void on_Followers_clicked();
    void on_Following_clicked();

public:
    Ui::Profile *ui;
};

#endif // PROFILE_H
