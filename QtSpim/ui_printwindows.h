/********************************************************************************
** Form generated from reading UI file 'printwindows.ui'
**
** Created: Sun Aug 22 19:45:40 2010
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRINTWINDOWS_H
#define UI_PRINTWINDOWS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PrintWindowsDialog
{
public:
    QWidget *verticalLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *label;
    QCheckBox *RegsCheckBox;
    QCheckBox *TextCheckBox;
    QCheckBox *DataCheckBox;
    QCheckBox *ConsoleCheckBox;
    QPushButton *SavePushButton;
    QPushButton *AbortPushButton;

    void setupUi(QDialog *PrintWindowsDialog)
    {
        if (PrintWindowsDialog->objectName().isEmpty())
            PrintWindowsDialog->setObjectName(QString::fromUtf8("PrintWindowsDialog"));
        PrintWindowsDialog->resize(370, 230);
        verticalLayoutWidget = new QWidget(PrintWindowsDialog);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 10, 350, 210));
        gridLayout = new QGridLayout(verticalLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 2, 0, 1, 1);

        RegsCheckBox = new QCheckBox(verticalLayoutWidget);
        RegsCheckBox->setObjectName(QString::fromUtf8("RegsCheckBox"));

        gridLayout->addWidget(RegsCheckBox, 2, 1, 1, 1);

        TextCheckBox = new QCheckBox(verticalLayoutWidget);
        TextCheckBox->setObjectName(QString::fromUtf8("TextCheckBox"));

        gridLayout->addWidget(TextCheckBox, 3, 1, 1, 1);

        DataCheckBox = new QCheckBox(verticalLayoutWidget);
        DataCheckBox->setObjectName(QString::fromUtf8("DataCheckBox"));

        gridLayout->addWidget(DataCheckBox, 4, 1, 1, 1);

        ConsoleCheckBox = new QCheckBox(verticalLayoutWidget);
        ConsoleCheckBox->setObjectName(QString::fromUtf8("ConsoleCheckBox"));

        gridLayout->addWidget(ConsoleCheckBox, 5, 1, 1, 1);

        SavePushButton = new QPushButton(verticalLayoutWidget);
        SavePushButton->setObjectName(QString::fromUtf8("SavePushButton"));

        gridLayout->addWidget(SavePushButton, 6, 1, 1, 1);

        AbortPushButton = new QPushButton(verticalLayoutWidget);
        AbortPushButton->setObjectName(QString::fromUtf8("AbortPushButton"));

        gridLayout->addWidget(AbortPushButton, 6, 2, 1, 1);

        verticalLayoutWidget->raise();
        AbortPushButton->raise();

        retranslateUi(PrintWindowsDialog);
        QObject::connect(SavePushButton, SIGNAL(clicked()), PrintWindowsDialog, SLOT(accept()));
        QObject::connect(AbortPushButton, SIGNAL(clicked()), PrintWindowsDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(PrintWindowsDialog);
    } // setupUi

    void retranslateUi(QDialog *PrintWindowsDialog)
    {
        PrintWindowsDialog->setWindowTitle(QApplication::translate("PrintWindowsDialog", "Print Windows", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("PrintWindowsDialog", "Print windows ", 0, QApplication::UnicodeUTF8));
        RegsCheckBox->setText(QApplication::translate("PrintWindowsDialog", "Registers", 0, QApplication::UnicodeUTF8));
        TextCheckBox->setText(QApplication::translate("PrintWindowsDialog", "Text Segments", 0, QApplication::UnicodeUTF8));
        DataCheckBox->setText(QApplication::translate("PrintWindowsDialog", "Data Segments", 0, QApplication::UnicodeUTF8));
        ConsoleCheckBox->setText(QApplication::translate("PrintWindowsDialog", "Console", 0, QApplication::UnicodeUTF8));
        SavePushButton->setText(QApplication::translate("PrintWindowsDialog", "Print", 0, QApplication::UnicodeUTF8));
        AbortPushButton->setText(QApplication::translate("PrintWindowsDialog", "Abort", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class PrintWindowsDialog: public Ui_PrintWindowsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRINTWINDOWS_H
