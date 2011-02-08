#include <QtGui>
#include "screen.h"

Screen::Screen()
{
    label = new QLabel(this);
    label->setPixmap(QPixmap::grabWindow(QApplication::desktop()->winId()));
    label->move(0,0);
    showFullScreen();
}

void Screen::mousePressEvent(QMouseEvent *event)
{
    emit colorSelected( label->pixmap()->toImage().pixel( event->pos() ) );
    close();
}
