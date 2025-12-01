#include "mainwindow.h"
#include "threadmenuwindow.h"
#include "discussionboard.h"
#include "replieswindow.h"
#include "windowsettings.h"
#include <QApplication>
#include <QFontDatabase>
#include <QDebug>
#include <mysql/jdbc.h> //proof of concept that this include exist

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // DiscussionBoard w;
    // w.show();

     //ThreadMenuWindow test(nullptr, "IYGS9O9EVDZVPLF");
     //test.show();

    RepliesWindow test(nullptr, "2T2EF1CIGLX7H2D");
    test.show();

<<<<<<< HEAD
    MainWindow w;
    w.show();
    centerOnScreen(&w);
=======
    //MainWindow w;
    //w.show();
>>>>>>> 9417bec (Create New Comments Fixed)
    return a.exec();
}
