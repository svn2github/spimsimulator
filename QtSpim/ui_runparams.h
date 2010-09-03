/********************************************************************************
** Form generated from reading UI file 'runparams.ui'
**
** Created: Thu Sep 2 21:43:51 2010
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RUNPARAMS_H
#define UI_RUNPARAMS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QSpacerItem>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SetRunParametersDialog
{
public:
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *addressLineEdit;
    QSpacerItem *horizontalSpacer;
    QLabel *label_2;
    QLineEdit *argsLineEdit;
    QDialogButtonBox *buttonBox;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *SetRunParametersDialog)
    {
        if (SetRunParametersDialog->objectName().isEmpty())
            SetRunParametersDialog->setObjectName(QString::fromUtf8("SetRunParametersDialog"));
        SetRunParametersDialog->resize(318, 207);
        gridLayoutWidget = new QWidget(SetRunParametersDialog);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 10, 298, 187));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(gridLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        addressLineEdit = new QLineEdit(gridLayoutWidget);
        addressLineEdit->setObjectName(QString::fromUtf8("addressLineEdit"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(addressLineEdit->sizePolicy().hasHeightForWidth());
        addressLineEdit->setSizePolicy(sizePolicy);

        gridLayout->addWidget(addressLineEdit, 1, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 2, 0, 1, 1);

        label_2 = new QLabel(gridLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 3, 0, 1, 1);

        argsLineEdit = new QLineEdit(gridLayoutWidget);
        argsLineEdit->setObjectName(QString::fromUtf8("argsLineEdit"));
        sizePolicy.setHeightForWidth(argsLineEdit->sizePolicy().hasHeightForWidth());
        argsLineEdit->setSizePolicy(sizePolicy);

        gridLayout->addWidget(argsLineEdit, 4, 0, 1, 1);

        buttonBox = new QDialogButtonBox(gridLayoutWidget);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        buttonBox->setCenterButtons(true);

        gridLayout->addWidget(buttonBox, 6, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer, 5, 0, 1, 1);


        retranslateUi(SetRunParametersDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), SetRunParametersDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SetRunParametersDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(SetRunParametersDialog);
    } // setupUi

    void retranslateUi(QDialog *SetRunParametersDialog)
    {
        SetRunParametersDialog->setWindowTitle(QApplication::translate("SetRunParametersDialog", "Set Run Parameters", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("SetRunParametersDialog", "Address or label to start running program", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("SetRunParametersDialog", "Command-line arguments to pass to program", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SetRunParametersDialog: public Ui_SetRunParametersDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RUNPARAMS_H
