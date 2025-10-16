#ifndef REPLIESWINDOW_H
#define REPLIESWINDOW_H

#include <QMainWindow>

namespace Ui {
class RepliesWindow;
}

class RepliesWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RepliesWindow(QWidget *parent = nullptr);
    explicit RepliesWindow(QWidget *parent = nullptr, std::string boardID = "");
    ~RepliesWindow();

private:
    Ui::RepliesWindow *ui;
    class QHBoxLayout* CreateBanner(std::string userName, std::string threadName, int height);
    void ClickOnBanner(std::string threadCommentPage);
    void ClickOnProfile(std::string userID);
    void on_backToThreads_clicked();
};

#endif // MAINWINDOW_H
