#ifndef MESSAGEWINDOW_H
#define MESSAGEWINDOW_H

#include <QMainWindow>

namespace Ui {
class MessageWindow;
}

class MessageWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MessageWindow(QWidget *parent = nullptr);
    ~MessageWindow();

private slots:
    void on_backButton_clicked();

    void on_sendButton_clicked();

private:
    int mode = 0;
    std::string selectedUser = "\0";

    Ui::MessageWindow *ui;
    class QHBoxLayout* CreateInboxBanner(std::string user);
    class QHBoxLayout* CreateDMBanner(std::string user, std::string msg);
    void ClickOnUserDM(std::string threadCommentName);
    void ClearLayout(QLayout *layout);
    void ReloadInbox(void);
};

#endif // MESSAGEWINDOW_H
