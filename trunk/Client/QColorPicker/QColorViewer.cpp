#include "QColorViewer.h"
#include "QColorPicker\qtcolortriangle.h"

QColor removeAlpha(const QColor& col)
{
    return QColor(col.red(), col.green(), col.blue());
}

QColorViewer::QColorViewer(QWidget *par):QWidget(par)
{
    setMinimumSize(15, 15);
}

void QColorViewer::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.setPen(actualPen);
    if(isEnabled())
        p.setBrush(QBrush(actualColor));
    else
        p.setBrush(QBrush(toGreyScale(actualColor)));
    p.drawRect( QRect( 2, 2, width()-4, height()-4 ) );
}

void QColorViewer::setPen(const QPen &p)
{
    actualPen = p;
}

QPen QColorViewer::pen() const
{
    return actualPen;
}

void QColorViewer::setColor(const QColor &col)
{
    actualColor = removeAlpha(col);
    update();
}

QColor QColorViewer::color() const
{
    return actualColor;
}


void QColorViewer::changeColor(const QColor &col)
{
    actualColor = col;
    update();
}
