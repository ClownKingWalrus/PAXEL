#ifndef YOURPAXELBOARD_H
#define YOURPAXELBOARD_H

#include <QMainWindow>
#include <QHBoxLayout>

namespace Ui {
class CreateBoardWindow;
}

class CreateBoardWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CreateBoardWindow(QWidget *parent = nullptr);
    ~CreateBoardWindow();

protected:
    void resizeEvent(QResizeEvent* event) override;

private slots:
    void on_pushButton_clicked();

    void on_HomeScreenButton_clicked();

private:
    int boardCount;
    Ui::CreateBoardWindow *ui;
    void loadOwnBoards(const std::string& host, const std::string& user, const std::string& password, const std::string& dbName); //loads the boards from the SQL
    class QHBoxLayout* CreateBoardBanner(const std::string& boardID, const std::string& boardName); //Creates the boards variables for the ui
    QVBoxLayout* bannerLayout; //The banner layout pointer
    void ClickOnBoardName(std::string boardThreads); //Clicking on a board will send you to threads
};

#endif // YOURPAXELBOARD_H
