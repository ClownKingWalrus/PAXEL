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
    ~DiscussionBoard();

private slots:
    void onScroll(int value);

private:
    Ui::DiscussionBoard *ui;
    void loadBoards(const string& host, const string& user, const string& password, const string& dbName);
    class QHBoxLayout* CreateBoardBanner(const string& boardID, const string& boardName);
};

#endif // DISCUSSIONBOARD_H
