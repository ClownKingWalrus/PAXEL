#ifndef THREADBANNERBOX_H
#define THREADBANNERBOX_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

class ThreadBannerBox : public QWidget
{
    Q_OBJECT
public:
    explicit ThreadBannerBox(const QString& userName, const QString& threadName, const QString& threadID, QWidget *parent = nullptr);

    void OnClickProfile(const QString& userName);
    void OnClickBanner(const QString& threadName);
    void OnClickLike(const QString& threadID);
    void OnClickFollowThread(const QString& threadID);
signals:

private:
    QPushButton* profileButton;
    QPushButton* threadButton;
    QPushButton* likeButton;
    QPushButton* followThreadButton;
    QPushButton* replyToThreadButton;

    QWidget* repliesBox;
    QVBoxLayout* repliesLayout;
    bool repliesVisible = false;
    void loadReplies(const QString& threadID);
    QString userID;
};

#endif // THREADBANNERBOX_H

