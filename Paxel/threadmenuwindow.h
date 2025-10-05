#ifndef THREADMENUWINDOW_H
#define THREADMENUWINDOW_H

#include <QMainWindow>

namespace Ui {
class ThreadMenuWindow;
}

class ThreadMenuWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ThreadMenuWindow(QWidget *parent = nullptr);
    explicit ThreadMenuWindow(QWidget *parent = nullptr, std::string boardID = "");
    ~ThreadMenuWindow();

private:
    Ui::ThreadMenuWindow *ui;
    class QHBoxLayout* CreateThreadBanner(std::string userName, std::string threadName);
    void ClickOnBanner(std::string threadCommentPage);
    void ClickOnProfile(std::string userID);
};

#endif // THREADMENUWINDOW_H
