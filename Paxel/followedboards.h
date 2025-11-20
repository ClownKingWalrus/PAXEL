#ifndef FOLLOWEDBOARDS_H
#define FOLLOWEDBOARDS_H

#include <QMainWindow>
#include <QVBoxLayout>

using namespace std;
namespace Ui {
class FollowedBoards;
}

class FollowedBoards : public QMainWindow
{
    Q_OBJECT

public:
    explicit FollowedBoards(QWidget *parent = nullptr, string boardID = "");
    ~FollowedBoards();

private slots:
    void on_Back_clicked();

protected:
    void resizeEvent(QResizeEvent* event) override;

private:
    Ui::FollowedBoards *ui;

private:
    void onClicked(string followerID);
    class QHBoxLayout* CreateBoardBanner(const string& boardID, const string& boardName);
    QVBoxLayout* bannerLayout;
    void loadBoards(const string& host, const string& user, const string& password, const string& dbName, string boardID);
};

#endif // FOLLOWEDBOARDS_H
