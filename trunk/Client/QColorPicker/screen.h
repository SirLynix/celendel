#ifndef SCREEN_H
#define SCREEN_H

#include <QWidget>
#include <QLabel>

#include <QMouseEvent>


class Screen : public QWidget
{
    Q_OBJECT
public:
    Screen();

private:
    QLabel *label;

protected:
    virtual void mousePressEvent(QMouseEvent *event);

signals:
    void colorSelected(QColor color);
};

#endif // SCREEN_H
