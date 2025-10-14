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

public slots:
    void timefunction();

public:
    Ui::HomeScreen *ui;
    QTimer *timer;

private slots:
    void on_Profile_clicked();
};

#endif // HOMESCREEN_H
