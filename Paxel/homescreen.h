#ifndef HOMESCREEN_H
#define HOMESCREEN_H

#include <QMainWindow>

namespace Ui {
class HomeScreen;
}

class HomeScreen : public QMainWindow
{
    Q_OBJECT

public:
    explicit HomeScreen(QWidget *parent = nullptr);
    ~HomeScreen();

public:
    Ui::HomeScreen *ui;
private slots:
    void on_LogOut_clicked();
    void on_LogOut_clicked(bool checked);
};

#endif // HOMESCREEN_H
