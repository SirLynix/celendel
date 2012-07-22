#include "EquipmentWidget.h"
#include "../Shared/Constants.h"

#include <QLayout>

EquipmentDialog::EquipmentDialog(QWidget* par) : QDialog(par)
{
    QVBoxLayout* lay = new QVBoxLayout;
    setLayout(lay);

}

void EquipmentDialog::setEntity(const EntityInformations& ent)
{
    m_entity = ent;
}
