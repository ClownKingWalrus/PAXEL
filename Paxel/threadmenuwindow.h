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
    explicit ThreadMenuWindow(QWidget *parent = nullptr, std::string boardID = "");
    ~ThreadMenuWindow();

private slots:
    void on_BackHome_clicked();

public:
    class QPushButton* createThread;
    class QPushButton* followBoards;
    class QPushButton* reloadButton;
    Ui::ThreadMenuWindow *ui;
    class ThreadBannerBox* CreateThreadBanner(std::string userName, std::string threadName, std::string threadID);
    void CreateThreadButtonClicked();
    std::string boardIDT;
    void BoardsFollowClicked(std::string boardID);

protected:
    void resizeEvent(QResizeEvent* event) override;
};

#endif // THREADMENUWINDOW_H
