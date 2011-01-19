#include "AboutWindow.h"

#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

AboutWindow::AboutWindow(const QString& text, QWidget* parent) : QDialog(parent)
{
    QPushButton *ok=new QPushButton(tr("Ok"), this);
    connect(ok, SIGNAL(pressed()), this, SLOT(accept()));
    QLabel *label=new QLabel(text, this);
    label->setOpenExternalLinks(true);
    label->setScaledContents(true);
    QVBoxLayout* la=new QVBoxLayout(this);

    la->addWidget(label);
    la->addWidget(ok);
}

int AboutWindow::open(const QString& text, QWidget* parent)
{
    AboutWindow win(text, parent);
    return win.exec();
}
