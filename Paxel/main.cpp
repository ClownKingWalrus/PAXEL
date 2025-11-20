#include "mainwindow.h"
#include "threadmenuwindow.h"
#include "discussionboard.h"
#include "homescreen.h"
#include "replieswindow.h"
#include "profile.h"
#include "followers.h"
#include "interestselect.h"
#include "windowsettings.h"
#include <QApplication>
#include <QFontDatabase>
#include <QDebug>
#include <mysql/jdbc.h> //proof of concept that this include exist
#include "../hdr/Utils.h"
#include "../hdr/proc.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Utils::InitSql(proc::ip, proc::user, proc::password, proc::db);

    interestselect i;
    MainWindow w;
    w.show();
    centerOnScreen(&w);
    return a.exec();
}
