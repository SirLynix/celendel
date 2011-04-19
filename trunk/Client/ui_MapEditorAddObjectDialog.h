/********************************************************************************
** Form generated from reading UI file 'MapEditorAddObjectDialog.ui'
**
** Created: Tue 19. Apr 15:05:47 2011
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
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_NewMapItemDialog
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *text;
    QLabel *label_2;
    QSpinBox *coordX;
    QSpinBox *coordY;
    QSpinBox *RSIDSpinBox;
    QDialogButtonBox *buttonBox;
    QGroupBox *colorGroupBox;
    QHBoxLayout *horizontalLayout;
    QHBoxLayout *colorLayout;

    void setupUi(QDialog *NewMapItemDialog)
    {
        if (NewMapItemDialog->objectName().isEmpty())
            NewMapItemDialog->setObjectName(QString::fromUtf8("NewMapItemDialog"));
        NewMapItemDialog->setWindowModality(Qt::WindowModal);
        NewMapItemDialog->resize(644, 397);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(NewMapItemDialog->sizePolicy().hasHeightForWidth());
        NewMapItemDialog->setSizePolicy(sizePolicy);
        NewMapItemDialog->setModal(true);
        gridLayout_2 = new QGridLayout(NewMapItemDialog);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(NewMapItemDialog);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        text = new QLineEdit(NewMapItemDialog);
        text->setObjectName(QString::fromUtf8("text"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Maximum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(text->sizePolicy().hasHeightForWidth());
        text->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(text, 1, 0, 1, 1);

        label_2 = new QLabel(NewMapItemDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(label_2, 4, 0, 1, 1);

        coordX = new QSpinBox(NewMapItemDialog);
        coordX->setObjectName(QString::fromUtf8("coordX"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(coordX->sizePolicy().hasHeightForWidth());
        coordX->setSizePolicy(sizePolicy3);
        coordX->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(coordX, 5, 0, 1, 1);

        coordY = new QSpinBox(NewMapItemDialog);
        coordY->setObjectName(QString::fromUtf8("coordY"));
        sizePolicy3.setHeightForWidth(coordY->sizePolicy().hasHeightForWidth());
        coordY->setSizePolicy(sizePolicy3);
        coordY->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(coordY, 5, 1, 1, 1);

        RSIDSpinBox = new QSpinBox(NewMapItemDialog);
        RSIDSpinBox->setObjectName(QString::fromUtf8("RSIDSpinBox"));
        RSIDSpinBox->setAlignment(Qt::AlignCenter);
        RSIDSpinBox->setMaximum(2000000000);

        gridLayout->addWidget(RSIDSpinBox, 1, 1, 1, 1);

        buttonBox = new QDialogButtonBox(NewMapItemDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        sizePolicy2.setHeightForWidth(buttonBox->sizePolicy().hasHeightForWidth());
        buttonBox->setSizePolicy(sizePolicy2);
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        buttonBox->setCenterButtons(true);

        gridLayout->addWidget(buttonBox, 7, 1, 1, 1);

        colorGroupBox = new QGroupBox(NewMapItemDialog);
        colorGroupBox->setObjectName(QString::fromUtf8("colorGroupBox"));
        colorGroupBox->setCheckable(true);
        horizontalLayout = new QHBoxLayout(colorGroupBox);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        colorLayout = new QHBoxLayout();
        colorLayout->setObjectName(QString::fromUtf8("colorLayout"));

        horizontalLayout->addLayout(colorLayout);

        buttonBox->raise();

        gridLayout->addWidget(colorGroupBox, 6, 0, 1, 2);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        buttonBox->raise();
        buttonBox->raise();

        retranslateUi(NewMapItemDialog);

        QMetaObject::connectSlotsByName(NewMapItemDialog);
    } // setupUi

    void retranslateUi(QDialog *NewMapItemDialog)
    {
        NewMapItemDialog->setWindowTitle(QApplication::translate("NewMapItemDialog", "Nouvel objet", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("NewMapItemDialog", "Nom de l'objet :", 0, QApplication::UnicodeUTF8));
        text->setPlaceholderText(QApplication::translate("NewMapItemDialog", "Nom...", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("NewMapItemDialog", "Coordonn\303\251es :", 0, QApplication::UnicodeUTF8));
        coordX->setPrefix(QApplication::translate("NewMapItemDialog", "X : ", 0, QApplication::UnicodeUTF8));
        coordY->setPrefix(QApplication::translate("NewMapItemDialog", "Y : ", 0, QApplication::UnicodeUTF8));
        RSIDSpinBox->setSuffix(QString());
        RSIDSpinBox->setPrefix(QApplication::translate("NewMapItemDialog", "RSID : ", 0, QApplication::UnicodeUTF8));
        colorGroupBox->setTitle(QApplication::translate("NewMapItemDialog", "Teinte :", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class NewMapItemDialog: public Ui_NewMapItemDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAPEDITORADDOBJECTDIALOG_H
