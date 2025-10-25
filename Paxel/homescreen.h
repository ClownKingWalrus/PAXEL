#ifndef HOMESCREEN_H
#define HOMESCREEN_H

#include <QMainWindow>
#include <QHBoxLayout>

using namespace std;

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
    void onScroll(int value);

private:
    void loadBoards(const string& host, const string& user, const string& password, const string& dbName);
    class QHBoxLayout* CreateBoardBanner(const string& boardID, const string& boardName);
};

#endif // HOMESCREEN_H
