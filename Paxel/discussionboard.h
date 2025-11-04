#ifndef DISCUSSIONBOARD_H
#define DISCUSSIONBOARD_H

#include <QMainWindow>
#include <QHBoxLayout>

using namespace std;

namespace Ui {
class DiscussionBoard;
}

class DiscussionBoard : public QMainWindow
{
    Q_OBJECT

public:
    explicit DiscussionBoard(QWidget *parent = nullptr);
    explicit DiscussionBoard(QWidget *parent, int UserID);
    ~DiscussionBoard();

private slots:
    void onScroll(int value);

private:
    Ui::DiscussionBoard *ui;
    void loadBoards(const string& host, const string& user, const string& password, const string& dbName);
    void loadBoards(const string& host, const string& user, const string& password, const string& dbName, int userID);
    class QHBoxLayout* CreateBoardBanner(const string& boardID, const string& boardName);
    void ClickOnBoardName(std::string boardThreads);
};

#endif // DISCUSSIONBOARD_H
