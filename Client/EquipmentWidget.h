#ifndef EQUIPMENTWIDGET_H
#define EQUIPMENTWIDGET_H

#include <QWidget>
#include "../Shared/Constants.h"

#include <QDialog>

class EquipmentDialog : public QDialog
{
    Q_OBJECT
    public:
        EquipmentDialog(QWidget* parent=0);
        void setEntity(const EntityInformations& ent);

    private:
        EntityInformations m_entity;
};

#endif
