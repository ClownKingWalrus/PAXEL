#include "mainwindow.h"
#include "threadmenuwindow.h"
#include "discussionboard.h"

#include <QApplication>
#include <mysql/jdbc.h> //proof of concept that this include exist

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DiscussionBoard w;
    w.show();

    // ThreadMenuWindow test(nullptr, "Q0VHY6CUENSWOD1");
    // test.show();

    return a.exec();
}
