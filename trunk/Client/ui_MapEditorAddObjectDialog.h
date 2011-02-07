/********************************************************************************
** Form generated from reading UI file 'MapEditorAddObjectDialog.ui'
**
** Created: Mon 7. Feb 22:25:08 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAPEDITORADDOBJECTDIALOG_H
#define UI_MAPEDITORADDOBJECTDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NewMapItemDialog
{
public:
    QLineEdit *text;
    QLabel *label;
    QSpinBox *RSIDSpinBox;
    QDialogButtonBox *buttonBox;
    QSpinBox *coordX;
    QSpinBox *coordY;
    QLabel *label_2;
    QFrame *colorFrame;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *colorLayout;

    void setupUi(QDialog *NewMapItemDialog)
    {
        if (NewMapItemDialog->objectName().isEmpty())
            NewMapItemDialog->setObjectName(QString::fromUtf8("NewMapItemDialog"));
        NewMapItemDialog->setWindowModality(Qt::WindowModal);
        NewMapItemDialog->resize(426, 194);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(NewMapItemDialog->sizePolicy().hasHeightForWidth());
        NewMapItemDialog->setSizePolicy(sizePolicy);
        NewMapItemDialog->setModal(true);
        text = new QLineEdit(NewMapItemDialog);
        text->setObjectName(QString::fromUtf8("text"));
        text->setGeometry(QRect(10, 40, 379, 20));
        label = new QLabel(NewMapItemDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 20, 379, 21));
        RSIDSpinBox = new QSpinBox(NewMapItemDialog);
        RSIDSpinBox->setObjectName(QString::fromUtf8("RSIDSpinBox"));
        RSIDSpinBox->setGeometry(QRect(250, 130, 171, 20));
        RSIDSpinBox->setAlignment(Qt::AlignCenter);
        RSIDSpinBox->setMaximum(2000000000);
        buttonBox = new QDialogButtonBox(NewMapItemDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(250, 160, 161, 23));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        buttonBox->setCenterButtons(false);
        coordX = new QSpinBox(NewMapItemDialog);
        coordX->setObjectName(QString::fromUtf8("coordX"));
        coordX->setGeometry(QRect(260, 90, 61, 22));
        coordX->setAlignment(Qt::AlignCenter);
        coordY = new QSpinBox(NewMapItemDialog);
        coordY->setObjectName(QString::fromUtf8("coordY"));
        coordY->setGeometry(QRect(330, 90, 61, 22));
        coordY->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(NewMapItemDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(250, 70, 161, 21));
        colorFrame = new QFrame(NewMapItemDialog);
        colorFrame->setObjectName(QString::fromUtf8("colorFrame"));
        colorFrame->setGeometry(QRect(10, 70, 231, 121));
        colorFrame->setFrameShape(QFrame::StyledPanel);
        colorFrame->setFrameShadow(QFrame::Raised);
        verticalLayoutWidget = new QWidget(colorFrame);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(0, 0, 231, 121));
        colorLayout = new QVBoxLayout(verticalLayoutWidget);
        colorLayout->setObjectName(QString::fromUtf8("colorLayout"));
        colorLayout->setContentsMargins(0, 0, 0, 0);

        retranslateUi(NewMapItemDialog);

        QMetaObject::connectSlotsByName(NewMapItemDialog);
    } // setupUi

    void retranslateUi(QDialog *NewMapItemDialog)
    {
        NewMapItemDialog->setWindowTitle(QApplication::translate("NewMapItemDialog", "Nouvel objet", 0, QApplication::UnicodeUTF8));
        text->setPlaceholderText(QApplication::translate("NewMapItemDialog", "Nom...", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("NewMapItemDialog", "Nom de l'objet :", 0, QApplication::UnicodeUTF8));
        RSIDSpinBox->setSuffix(QString());
        RSIDSpinBox->setPrefix(QApplication::translate("NewMapItemDialog", "RSID : ", 0, QApplication::UnicodeUTF8));
        coordX->setPrefix(QApplication::translate("NewMapItemDialog", "X : ", 0, QApplication::UnicodeUTF8));
        coordY->setPrefix(QApplication::translate("NewMapItemDialog", "Y : ", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("NewMapItemDialog", "Coordonn\303\251es :", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class NewMapItemDialog: public Ui_NewMapItemDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAPEDITORADDOBJECTDIALOG_H
