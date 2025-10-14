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
    class QPushButton* createThread;
    Ui::ThreadMenuWindow *ui;
    class ThreadBannerBox* CreateThreadBanner(std::string userName, std::string threadName, std::string threadID);
    void CreateThreadButtonClicked(std::string uuid);
    std::string boardIDT;
};

#endif // THREADMENUWINDOW_H