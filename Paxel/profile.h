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

public slots:
    void on_Logout_clicked();

private slots:
    void on_Home_clicked();

public:
    Ui::Profile *ui;
};

#endif // PROFILE_H
