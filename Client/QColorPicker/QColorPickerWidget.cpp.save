#include "QColorPickerWidget.h"

#include <QLabel>
#include <QPushbutton>
#include <QLayout>
#include <QGridLayout>
#include <QSlider>
#include <QSpinBox>
#include <QGroupBox>
#include "qtcolortriangle.h"
#include "QColorViewer.h"
#include "screen.h"

#include <QDebug>

QColorPickerWidget::QColorPickerWidget(QWidget *parent):QWidget(parent)
{
    m_alphaEnabled=true;
    m_spinBoxesEnabled=true;
    scr=NULL;
    m_colorTriangle = new QtColorTriangle(this);

    connect(m_colorTriangle, SIGNAL(colorChanged(QColor)), this, SLOT(colorChgd()));

    m_colorView = new ColorViewer(this);
    m_colorView->setColor(m_colorTriangle->color());
    connect(m_colorTriangle, SIGNAL(colorChanged(QColor)), m_colorView, SLOT(changeColor(QColor)));

    m_pickColor = new QPushButton(tr("Pick a color"), this);
    connect(m_pickColor, SIGNAL(released()), this, SLOT(pickMode()));

    m_alphaSlider=new QSlider(Qt::Horizontal,this); m_alphaSlider->setRange(0,255); m_alphaSlider->setValue(255);
    m_alphaLabel=new QLabel(tr("Alpha"),this); m_alphaLabel->setAlignment(Qt::AlignHCenter);

    m_spinBoxesGB=new QGroupBox(tr("Valeurs :"),this);
    QVBoxLayout* lay=new QVBoxLayout();
    m_spinBoxesGB->setLayout(lay);

    m_alphaSB=new QSpinBox(this); m_alphaSB->setRange(0,255); lay->addWidget(m_alphaSB);
    m_redSB=new QSpinBox(this); m_alphaSB->setRange(0,255); lay->addWidget(m_redSB);
    m_blueSB=new QSpinBox(this); m_alphaSB->setRange(0,255); lay->addWidget(m_blueSB);
    m_greenSB=new QSpinBox(this); m_alphaSB->setRange(0,255); lay->addWidget(m_greenSB);

    layout = new QGridLayout;
    layout->addWidget(  m_colorTriangle,  0, 0, 4, 2);
    layout->addWidget(  m_colorView,      1, 5, 2, 2);
    layout->addWidget(  m_pickColor,      0, 5, 1, -1);
    layout->addWidget(  m_alphaSlider,    3, 3, 1, 2);
    layout->addWidget(  m_alphaLabel,     3, 2, 1, 1);
    layout->addWidget(  m_spinBoxesGB,    0, 2, 3, 3);

    setLayout(layout);
}

void QColorPickerWidget::pickMode()
{
    delete scr;
    scr = new Screen();
    connect(scr, SIGNAL(colorSelected(QColor)), m_colorTriangle, SLOT(setColor(QColor)));
}

void QColorPickerWidget::setAlphaEnabled(bool b)
{
    m_alphaEnabled=b;
    refresh();
}

void QColorPickerWidget::setSpinBoxesEnabled(bool b)
{
     m_spinBoxesEnabled=b;
     refresh();
}

void QColorPickerWidget::refresh()
{
    m_alphaSlider->setVisible(m_alphaEnabled);
    m_alphaLabel->setVisible(m_alphaEnabled);
    m_spinBoxesGB->setVisible(m_spinBoxesEnabled);
    m_alphaSB->setVisible(m_spinBoxesEnabled&&m_alphaEnabled);
}

void QColorPickerWidget::setColor(const QColor &col)
{
    m_colorView->setColor(col);
    m_colorTriangle->setColor(col);
    m_alphaSlider->setValue(col.alpha());
}

QColor QColorPickerWidget::color() const
{
    return QColor(m_colorView->color().red(),m_colorView->color().green(),m_colorView->color().blue(),m_alphaSlider->value());
}


void QColorPickerWidget::colorChgd()
{
    emit colorChanged(color());
}
