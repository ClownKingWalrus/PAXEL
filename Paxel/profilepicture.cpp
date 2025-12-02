#include "profilepicture.h"
#include "../hdr/Utils.h"
#include <QFileInfo>
#include <QBuffer>
#include "../hdr/proc.h"

ProfilePicture::ProfilePicture(QWidget *parent)
    : QLabel{parent}
{
    setAcceptDrops(true);
    setAlignment(Qt::AlignCenter);
    setStyleSheet("border: 1px solid gray; background: #eee;");
}

void ProfilePicture::dragEnterEvent(QDragEnterEvent *event) {
    if (event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
    }
}

void ProfilePicture::dropEvent(QDropEvent *event) {
    if (!event->mimeData()->hasUrls()) {
        return;
    }

    QUrl url = event->mimeData()->urls().first(); //loads the first image dragged in
    QString path = url.toLocalFile();

    QPixmap pixmap(path);//create a pixmap from the path

    if ("MainProfilePicture" == this->objectName()){
        if (!pixmap.isNull()) {
            setPixmap(pixmap.scaled(300, 600, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
    } else {
        if (!pixmap.isNull()) {
            setPixmap(pixmap.scaled(64, 64, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
    }

    if (!pixmap.isNull()) {
        QByteArray byte;
        QBuffer buffer(&byte);
        buffer.open(QIODevice::WriteOnly);
        pixmap.save(&buffer, "JPG");
        Utils::SaveImageToSql(proc::ip, proc::user, proc::password, proc::db, byte);
    }

}

QPixmap ProfilePicture::CreatePixMapFromSql() {
    QByteArray byte(Utils::LoadImageFromSql(proc::ip, proc::user, proc::password, proc::db));
    QPixmap pix;
    pix.loadFromData(byte);
    if (!pix.isNull()) {
        return pix;
    }
    return {};
}

QPixmap ProfilePicture::CreatePixMapFromSql(int userID) {
    QByteArray byte(Utils::LoadImageFromSql(proc::ip, proc::user, proc::password, proc::db, userID));
    QPixmap pix;
    pix.loadFromData(byte);
    if (!pix.isNull()) {
        return pix;
    }
    return {};
}
