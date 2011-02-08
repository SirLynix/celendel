#include "MapEditorDialogs.h"

#include <QSpinBox>
#include <QLineEdit>
#include <QLayout>
#include <QPushButton>
#include "QColorPicker/QColorPickerWidget.h"


RSIDDialog::RSIDDialog(QWidget* parent) : QDialog(parent), m_used(false)
{
    m_spinBox=new QSpinBox(this);
    m_lineEdit=new QLineEdit(this);
    m_lineEdit->setPlaceholderText(tr("Fichier de ressource..."));
    QHBoxLayout* l=new QHBoxLayout();
    l->addWidget(m_spinBox);
    m_spinBox->setMaximum(MAX_LOADED_RESSOURCES);
    m_spinBox->setPrefix(tr("RSID : "));
    l->addWidget(m_lineEdit);

    QVBoxLayout* vl=new QVBoxLayout();
    vl->addLayout(l);

    m_accept = new QPushButton(tr("Valider"), this);
    connect(m_accept, SIGNAL(pressed()), this, SLOT(accept()));
    m_cancel = new QPushButton(tr("Retour"), this);
    connect(m_cancel, SIGNAL(pressed()), this, SLOT(reject()));

    QHBoxLayout* h=new QHBoxLayout();
    h->addWidget(m_accept);
    h->addWidget(m_cancel);
    vl->addLayout(h);

    setLayout(vl);

}

int RSIDDialog::newLine()
{
    if(m_used)
        return 0;

    m_used=true;

    return exec();
}

int RSIDDialog::changeLine(RSID id, const QString& name)
{
    if(m_used)
        return 0;

    m_used=true;

    m_spinBox->setValue(id);
    m_spinBox->setEnabled(false);
    m_lineEdit->setText(name);

    return exec();
}

/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///

AddObjectDialog::AddObjectDialog(QWidget* parent, QPoint defaultCase, QPoint maxCase, QString defaultText, RSID defaultRSID) : QDialog(parent)
{
    ui.setupUi(this);
    ui.coordX->setValue(defaultCase.x()); ui.coordX->setMaximum(MAP_MAX_SIZE);
    ui.coordY->setValue(defaultCase.y()); ui.coordY->setMaximum(MAP_MAX_SIZE);
    ui.text->setText(defaultText);
    ui.RSIDSpinBox->setValue(defaultRSID); ui.RSIDSpinBox->setMaximum(MAX_LOADED_RESSOURCES);

    m_colorPicker = new QColorPickerWidget(this);
    ui.colorLayout->addWidget(m_colorPicker);

    connect(ui.buttonBox->button(QDialogButtonBox::Ok), SIGNAL(pressed()), this, SLOT(accept()));
    connect(ui.buttonBox->button(QDialogButtonBox::Cancel), SIGNAL(pressed()), this, SLOT(reject()));
}

QPoint AddObjectDialog::getCoords() const { return QPoint(ui.coordX->value(), ui.coordY->value()); }
QString AddObjectDialog::getText() const { return ui.text->text(); }
RSID AddObjectDialog::getRSID() const { return ui.RSIDSpinBox->value(); }
QColor AddObjectDialog::getColor() const
{
    if(ui.colorGroupBox->isEnabled())
        return m_colorPicker->color();

    return QColor(255,255,255,255);
}

