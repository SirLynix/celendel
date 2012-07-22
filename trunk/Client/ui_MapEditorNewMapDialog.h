/********************************************************************************
** Form generated from reading UI file 'MapEditorNewMapDialog.ui'
**
** Created: Sat 21. Jul 13:52:12 2012
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAPEDITORNEWMAPDIALOG_H
#define UI_MAPEDITORNEWMAPDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_NewMapDialog
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *mapName;
    QComboBox *typeCB;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout;
    QSpinBox *mapSizeX;
    QSpinBox *mapSizeY;
    QGroupBox *groupBox_4;
    QHBoxLayout *horizontalLayout_3;
    QSpinBox *RSIDSpinBox;
    QGroupBox *groupBox_5;
    QHBoxLayout *horizontalLayout_4;
    QLineEdit *mapFile;
    QPushButton *mbrowse;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *ressFile;
    QPushButton *browse;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *NewMapDialog)
    {
        if (NewMapDialog->objectName().isEmpty())
            NewMapDialog->setObjectName(QString::fromUtf8("NewMapDialog"));
        NewMapDialog->resize(252, 368);
        verticalLayout = new QVBoxLayout(NewMapDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox = new QGroupBox(NewMapDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        mapName = new QLineEdit(groupBox);
        mapName->setObjectName(QString::fromUtf8("mapName"));

        verticalLayout_2->addWidget(mapName);


        verticalLayout->addWidget(groupBox);

        typeCB = new QComboBox(NewMapDialog);
        typeCB->setObjectName(QString::fromUtf8("typeCB"));

        verticalLayout->addWidget(typeCB);

        groupBox_2 = new QGroupBox(NewMapDialog);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        horizontalLayout = new QHBoxLayout(groupBox_2);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        mapSizeX = new QSpinBox(groupBox_2);
        mapSizeX->setObjectName(QString::fromUtf8("mapSizeX"));

        horizontalLayout->addWidget(mapSizeX);

        mapSizeY = new QSpinBox(groupBox_2);
        mapSizeY->setObjectName(QString::fromUtf8("mapSizeY"));
        mapSizeY->setAccelerated(true);

        horizontalLayout->addWidget(mapSizeY);


        verticalLayout->addWidget(groupBox_2);

        groupBox_4 = new QGroupBox(NewMapDialog);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        horizontalLayout_3 = new QHBoxLayout(groupBox_4);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        RSIDSpinBox = new QSpinBox(groupBox_4);
        RSIDSpinBox->setObjectName(QString::fromUtf8("RSIDSpinBox"));

        horizontalLayout_3->addWidget(RSIDSpinBox);


        verticalLayout->addWidget(groupBox_4);

        groupBox_5 = new QGroupBox(NewMapDialog);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        horizontalLayout_4 = new QHBoxLayout(groupBox_5);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        mapFile = new QLineEdit(groupBox_5);
        mapFile->setObjectName(QString::fromUtf8("mapFile"));

        horizontalLayout_4->addWidget(mapFile);

        mbrowse = new QPushButton(groupBox_5);
        mbrowse->setObjectName(QString::fromUtf8("mbrowse"));

        horizontalLayout_4->addWidget(mbrowse);


        verticalLayout->addWidget(groupBox_5);

        groupBox_3 = new QGroupBox(NewMapDialog);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        horizontalLayout_2 = new QHBoxLayout(groupBox_3);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        ressFile = new QLineEdit(groupBox_3);
        ressFile->setObjectName(QString::fromUtf8("ressFile"));

        horizontalLayout_2->addWidget(ressFile);

        browse = new QPushButton(groupBox_3);
        browse->setObjectName(QString::fromUtf8("browse"));

        horizontalLayout_2->addWidget(browse);


        verticalLayout->addWidget(groupBox_3);

        buttonBox = new QDialogButtonBox(NewMapDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        buttonBox->setCenterButtons(true);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(NewMapDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), NewMapDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), NewMapDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(NewMapDialog);
    } // setupUi

    void retranslateUi(QDialog *NewMapDialog)
    {
        NewMapDialog->setWindowTitle(QApplication::translate("NewMapDialog", "Nouvelle carte...", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("NewMapDialog", "Nom de la carte :", 0, QApplication::UnicodeUTF8));
        mapName->setPlaceholderText(QApplication::translate("NewMapDialog", "Nom de la carte...", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("NewMapDialog", "Taille de la carte :", 0, QApplication::UnicodeUTF8));
        mapSizeX->setSuffix(QString());
        mapSizeX->setPrefix(QApplication::translate("NewMapDialog", "X : ", 0, QApplication::UnicodeUTF8));
        mapSizeY->setSuffix(QString());
        mapSizeY->setPrefix(QApplication::translate("NewMapDialog", "Y : ", 0, QApplication::UnicodeUTF8));
        groupBox_4->setTitle(QApplication::translate("NewMapDialog", "Contenu :", 0, QApplication::UnicodeUTF8));
        RSIDSpinBox->setPrefix(QApplication::translate("NewMapDialog", "RSID par d\303\251fault : ", 0, QApplication::UnicodeUTF8));
        groupBox_5->setTitle(QApplication::translate("NewMapDialog", "Fichier de carte :", 0, QApplication::UnicodeUTF8));
        mapFile->setPlaceholderText(QApplication::translate("NewMapDialog", "Nom du fichier...", 0, QApplication::UnicodeUTF8));
        mbrowse->setText(QApplication::translate("NewMapDialog", "...", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("NewMapDialog", "Set d'image :", 0, QApplication::UnicodeUTF8));
        ressFile->setPlaceholderText(QApplication::translate("NewMapDialog", "Nom du fichier...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        browse->setToolTip(QApplication::translate("NewMapDialog", "Parcourir...", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        browse->setWhatsThis(QApplication::translate("NewMapDialog", "Parcourir...", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        browse->setText(QApplication::translate("NewMapDialog", "...", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class NewMapDialog: public Ui_NewMapDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAPEDITORNEWMAPDIALOG_H
