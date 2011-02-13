#ifndef DEF_COLORVIEWER
#define DEF_COLORVIEWER

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>

class QColorViewer : public QWidget
{
    Q_OBJECT

public:
    QColorViewer(QWidget *parent = 0);

    void setPen(const QPen &pen);
    QPen pen() const;

    void setColor(const QColor &color);
    QColor color() const;

public slots:
    void changeColor(const QColor &color);

protected:
    void paintEvent(QPaintEvent *event);

private:
    QPen actualPen;
    QBrush actualBrush;
    QColor actualColor;
};

#endif
