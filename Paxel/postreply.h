#ifndef POSTREPLY_H
#define POSTREPLY_H
#include <QDialog>

namespace Ui {
class PostReply;
}

class PostReply : public QDialog
{
    Q_OBJECT

public:
    explicit PostReply(QWidget *parent, const QString& threadID, const QString& replyToID);
    ~PostReply();

private slots:
    void on_replySend_clicked();
    void on_replyCancel_clicked();

private:
    Ui::PostReply *ui;

    QString threadID;
    QString replyToID;
};

#endif // POSTREPLY_H
