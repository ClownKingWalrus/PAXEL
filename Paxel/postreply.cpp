#include "PostReply.h"
#include "ui_PostReply.h"
#include "../hdr/Utils.h"
#include "../hdr/proc.h"
using namespace std;

PostReply::PostReply(QWidget *parent, const QString& threadID, const QString& replyToID)
    : QDialog(parent),
    ui(new Ui::PostReply),
    threadID(threadID),
    replyToID(replyToID)
{
    ui->setupUi(this);
}

PostReply::~PostReply()
{
    delete ui;
}

void PostReply::on_replySend_clicked()
{
    QString text = ui->replyingBox->toPlainText();

    string repID = replyToID.toStdString();

    if (repID == threadID.toStdString())
        repID = "";

    Utils::CreateReply(proc::ip, proc::user, proc::password, proc::db, threadID.toStdString(), text.toStdString(), repID);
    close();
}

void PostReply::on_replyCancel_clicked()
{
    close();
}
