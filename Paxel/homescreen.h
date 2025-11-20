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
    class QHBoxLayout* CreateBoardBanner(const string& boardID, const string& boardName); //Creates the boards variables for the ui

private slots:
    void on_Profile_clicked(); //
    void onScroll(int value); // loads more boards as boxes are scrolled
    void on_CreateBoardButton_clicked();// allows the user to create boards onto the main paxel baord
    void BoardsFollowed_clicked(string userID);
    void on_messages_Button_clicked();
    void on_about_paxel_clicked();
    void on_help_Button_clicked();
    void on_Search_clicked();
    void on_Send_clicked();
    void ClickID(string userID);

protected:
    void resizeEvent(QResizeEvent* event) override;

private:
    void loadBoards(const string& host, const string& user, const string& password, const string& dbName); //loads the boards from the SQL
    QVBoxLayout* bannerLayout; //The banner layout pointer
    void ClickOnBoardName(string boardThreads); //Clicking on a board will send you to threads


};

#endif // HOMESCREEN_H

