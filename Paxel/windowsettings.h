#ifndef WINDOWSETTINGS_H
#define WINDOWSETTINGS_H
#include <QWidget>
#include <QScreen>
#include <QGuiApplication>

inline void centerOnScreen(QWidget *widget)
{
    QScreen *screen = widget->screen();
    QRect screenGeometry = screen->availableGeometry();
    widget->move(screenGeometry.center() - widget->rect().center());
}

#endif // WINDOWSETTINGS_H
