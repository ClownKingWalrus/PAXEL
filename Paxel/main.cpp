#include "mainwindow.h"
#include "threadmenuwindow.h"
#include "discussionboard.h"
#include "replieswindow.h"

#include <QApplication>
#include <mysql/jdbc.h> //proof of concept that this include exist

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //DiscussionBoard w;
    //w.show();

     //ThreadMenuWindow test(nullptr, "IYGS9O9EVDZVPLF");
     //test.show();

    //RepliesWindow test(nullptr, "2T2EF1CIGLX7H2D");
    //test.show();

    MainWindow w;
    w.show();
    return a.exec();
}
