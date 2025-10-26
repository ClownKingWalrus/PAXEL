#ifndef HOMESCREEN_H
#define HOMESCREEN_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>

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
    void on_Profile_clicked(); //
    void onScroll(int value); // loads more boards as boxes are scrolled

private:
    void loadBoards(const string& host, const string& user, const string& password, const string& dbName); //loads the boards from the SQL
    class QHBoxLayout* CreateBoardBanner(const string& boardID, const string& boardName); //Creates the boards variables for the ui
    QVBoxLayout* bannerLayout; //The banner layout pointer
    void ClickOnBoardName(string boardThreads); //Clicking on a board will send you to threads
};

#endif // HOMESCREEN_H
