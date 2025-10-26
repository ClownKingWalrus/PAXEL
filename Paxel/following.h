#ifndef FOLLOWING_H
#define FOLLOWING_H

#include <QMainWindow>

namespace Ui {
class Following;
}

class Following : public QMainWindow
{
    Q_OBJECT

public:
    explicit Following(QWidget *parent = nullptr);
    ~Following();
    void on_Back_clicked();
    void onScroll(int value);
    void onClicked();

private slots:
    void on_Followers_2_clicked();

public:
    Ui::Following *ui;
    int ProfileCount = 0;
    void loadProfiles(int count);
};

#endif // FOLLOWING_H
