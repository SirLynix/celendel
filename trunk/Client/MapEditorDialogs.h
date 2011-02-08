#ifndef DEF_MAPEDITORDIALOGS
#define DEF_MAPEDITORDIALOGS

#include <QDialog>
#include "..\Shared\Constants.h"
#include "ui_MapEditorAddObjectDialog.h"

class QLineEdit;
class QSpinBox;
class QPushButton;
class QColorPickerWidget;


class RSIDDialog : public QDialog
{
    public:

    RSIDDialog(QWidget* parent=0);

    int newLine();

    int changeLine(RSID id, const QString& name = QString());

    RSID getRSID() const { return m_spinBox->value(); }
    QString getName() const {  return m_lineEdit->text(); }

    private:

    bool m_used;

    QSpinBox* m_spinBox;
    QLineEdit* m_lineEdit;
    QPushButton* m_accept;
    QPushButton* m_cancel;

};

class AddObjectDialog : public QDialog
{
    public:
    AddObjectDialog(QWidget* parent=0, QPoint defaultCase=QPoint(), QPoint maxCase=QPoint(MAP_MAX_SIZE,MAP_MAX_SIZE), QString defaultText=QString(), RSID defaultRSID=0);

    QPoint getCoords() const;
    QString getText() const;
    RSID getRSID() const;
    QColor getColor() const;

    private:

    QColorPickerWidget* m_colorPicker;

    Ui::NewMapItemDialog ui;
};


#endif //Guard
