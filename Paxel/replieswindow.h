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

private slots:
    void on_replySend_clicked();
    void on_replyCancel_clicked();
    void on_backToThreads_clicked();

private:
    std::string threadID;
    std::string replyID;

    Ui::RepliesWindow *ui;
    class QHBoxLayout* CreateBanner(std::string userName, std::string threadName, std::string threadCommentID, std::string commentReply, int height);
    void ClickOnBanner(std::string threadCommentPage);
    void ClickOnProfile(std::string userID);
    void ClickOnReply(std::string userID);
    void endReply(void);

protected:
    void resizeEvent(QResizeEvent* event) override;
};

#endif // REPLIESWINDOW_H
