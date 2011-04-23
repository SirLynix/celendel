#include "MapEditorDialogs.h"

#include <QSpinBox>
#include <QLineEdit>
#include <QLayout>
#include <QPushButton>
#include <QFileDialog>
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
    b=false;
    ui.setupUi(this);
    ui.coordX->setValue(defaultCase.x()); ui.coordX->setMaximum(maxCase.x());
    ui.coordY->setValue(defaultCase.y()); ui.coordY->setMaximum(maxCase.y());
    ui.text->setText(defaultText);
    ui.RSIDSpinBox->setValue(defaultRSID); ui.RSIDSpinBox->setMaximum(MAX_LOADED_RESSOURCES);

    connect(ui.valueSB,SIGNAL(valueChanged(int)),ui.valueSlider,SLOT(setValue(int)));
    connect(ui.valueSlider,SIGNAL(valueChanged(int)),this,SLOT(vcng(int)));

    ui.valueSB->setValue(75);

    m_colorPicker = new QColorPickerWidget(this);
    ui.colorLayout->addWidget(m_colorPicker);
    ui.buttonBox->button(QDialogButtonBox::Ok)->setDefault(false);
    connect(ui.buttonBox->button(QDialogButtonBox::Ok), SIGNAL(pressed()), this, SLOT(accept()));
    connect(ui.buttonBox->button(QDialogButtonBox::Cancel), SIGNAL(pressed()), this, SLOT(reject()));
}

void AddObjectDialog::vcng(int i)
{
    if(b)
    {
        b=false;
        return;
    }
    b=true;
    ui.valueSB->setValue(i);
}

QPoint AddObjectDialog::getCoords() const { return QPoint(ui.coordX->value(), ui.coordY->value()); }
QString AddObjectDialog::getText() const { return ui.text->text(); }
RSID AddObjectDialog::getRSID() const { return ui.RSIDSpinBox->value(); }
int AddObjectDialog::getColorValue() const { if(ui.colorGroupBox->isEnabled()) {return ui.valueSB->value(); } return 0; }
QColor AddObjectDialog::getColor() const
{
    if(ui.colorGroupBox->isEnabled())
        return m_colorPicker->color();

    return QColor(255,255,255,255);
}

/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///

NewMapDialog::NewMapDialog(QWidget* parent) : QDialog(parent)
{
    ui.setupUi(this);
    ui.RSIDSpinBox->setMaximum(MAX_LOADED_RESSOURCES);
    ui.mapSizeX->setRange(1,MAP_MAX_SIZE); ui.mapSizeY->setRange(1,MAP_MAX_SIZE);
}

void NewMapDialog::on_browse_pressed()
{
    QString file = QFileDialog::getOpenFileName(this, tr("Sélectionnez un fichier..."), QString(), tr("Fichiers de liste (*.list);;Tous les fichiers (*.*)"));
    if(file.isEmpty())
        return;
    ui.ressFile->setText(file);
}

QString NewMapDialog::getName() const { return ui.mapName->text();}
QString NewMapDialog::getRessourceList() const  { return ui.ressFile->text(); }
RSID NewMapDialog::getRSID() const { return ui.RSIDSpinBox->value(); }
QPoint NewMapDialog::getSize() const { return QPoint(ui.mapSizeX->value(),ui.mapSizeY->value()); }
