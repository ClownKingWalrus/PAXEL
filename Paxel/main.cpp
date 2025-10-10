<<<<<<< HEAD
#include "mainwindow.h"
#include "threadmenuwindow.h"

#include <QApplication>
#include <mysql/jdbc.h> //proof of concept that this include exist

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ///Testing
    //MainWindow w;
    //w.show();
    ///Testing

    ThreadMenuWindow test(nullptr, "Q0VHY6CUENSWOD1");
    test.show();

    return a.exec();
}
=======
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
>>>>>>> d0026905569ce309e51e78cf5bf594451ab92d8b
