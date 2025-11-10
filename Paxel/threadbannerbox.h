#ifndef THREADBANNERBOX_H
#define THREADBANNERBOX_H

#include <QObject>
#include <QWidget>
#include <QPushButton>

class ThreadBannerBox : public QWidget
{
    Q_OBJECT
public:
    explicit ThreadBannerBox(const QString& userName, const QString& threadName, const QString& threadID, QWidget *parent = nullptr);

    void OnClickProfile(const QString& userName);
    void OnClickBanner(const QString& threadName);
    void OnClickLike(const QString& threadID, const std::string& userID);
    void OnClickFollowThread(const QString& threadID, const std::string& userID);
signals:

protected:
    void resizeEvent(QResizeEvent* event) override; //since this is protected it needs to be protected here

private:
    QPushButton* profileButton;
    QPushButton* threadButton;
    QPushButton* likeButton;
    QPushButton* followThreadButton;
};

#endif // THREADBANNERBOX_H
