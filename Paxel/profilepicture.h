#ifndef PROFILEPICTURE_H
#define PROFILEPICTURE_H

#include <QLabel>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QPixmap>

class ProfilePicture : public QLabel
{
    Q_OBJECT
public:
    explicit ProfilePicture(QWidget *parent = nullptr);

    static QPixmap CreatePixMapFromSql();
    static QPixmap CreatePixMapFromSql(int userID);
protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;

};

#endif // PROFILEPICTURE_H
