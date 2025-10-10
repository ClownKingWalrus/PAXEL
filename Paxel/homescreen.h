<<<<<<< HEAD
#ifndef HOMESCREEN_H
#define HOMESCREEN_H

#include <QWidget>

namespace Ui {
class HomeScreen;
}

class HomeScreen : public QWidget
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
=======
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
>>>>>>> d0026905569ce309e51e78cf5bf594451ab92d8b
