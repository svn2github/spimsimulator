/********************************************************************************
** Form generated from reading UI file 'savelogfile.ui'
**
** Created: Sun Aug 29 14:37:39 2010
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SAVELOGFILE_H
#define UI_SAVELOGFILE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QToolButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SaveLogFileDialog
{
public:
    QWidget *verticalLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *label;
    QCheckBox *RegsCheckBox;
    QCheckBox *TextCheckBox;
    QCheckBox *DataCheckBox;
    QCheckBox *ConsoleCheckBox;
    QLabel *label_2;
    QLineEdit *SaveLineEdit;
    QSpacerItem *verticalSpacer;
    QToolButton *saveFileToolButton;
    QRadioButton *TextRadioButton;
    QRadioButton *HTMLRadioButton;
    QSpacerItem *verticalSpacer_2;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *SaveLogFileDialog)
    {
        if (SaveLogFileDialog->objectName().isEmpty())
            SaveLogFileDialog->setObjectName(QString::fromUtf8("SaveLogFileDialog"));
        SaveLogFileDialog->resize(370, 286);
        verticalLayoutWidget = new QWidget(SaveLogFileDialog);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 10, 350, 235));
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

        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 10, 0, 1, 1);

        SaveLineEdit = new QLineEdit(verticalLayoutWidget);
        SaveLineEdit->setObjectName(QString::fromUtf8("SaveLineEdit"));

        gridLayout->addWidget(SaveLineEdit, 10, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer, 6, 0, 1, 1);

        saveFileToolButton = new QToolButton(verticalLayoutWidget);
        saveFileToolButton->setObjectName(QString::fromUtf8("saveFileToolButton"));

        gridLayout->addWidget(saveFileToolButton, 10, 2, 1, 1);

        TextRadioButton = new QRadioButton(verticalLayoutWidget);
        TextRadioButton->setObjectName(QString::fromUtf8("TextRadioButton"));
        TextRadioButton->setChecked(true);

        gridLayout->addWidget(TextRadioButton, 7, 1, 1, 1);

        HTMLRadioButton = new QRadioButton(verticalLayoutWidget);
        HTMLRadioButton->setObjectName(QString::fromUtf8("HTMLRadioButton"));

        gridLayout->addWidget(HTMLRadioButton, 8, 1, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer_2, 9, 0, 1, 1);

        buttonBox = new QDialogButtonBox(SaveLogFileDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(110, 250, 156, 23));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        retranslateUi(SaveLogFileDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), SaveLogFileDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SaveLogFileDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(SaveLogFileDialog);
    } // setupUi

    void retranslateUi(QDialog *SaveLogFileDialog)
    {
        SaveLogFileDialog->setWindowTitle(QApplication::translate("SaveLogFileDialog", "Select Windows", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("SaveLogFileDialog", "Save windows ", 0, QApplication::UnicodeUTF8));
        RegsCheckBox->setText(QApplication::translate("SaveLogFileDialog", "Registers", 0, QApplication::UnicodeUTF8));
        TextCheckBox->setText(QApplication::translate("SaveLogFileDialog", "Text Segments", 0, QApplication::UnicodeUTF8));
        DataCheckBox->setText(QApplication::translate("SaveLogFileDialog", "Data Segments", 0, QApplication::UnicodeUTF8));
        ConsoleCheckBox->setText(QApplication::translate("SaveLogFileDialog", "Console", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("SaveLogFileDialog", "Save to file", 0, QApplication::UnicodeUTF8));
        saveFileToolButton->setText(QApplication::translate("SaveLogFileDialog", "...", 0, QApplication::UnicodeUTF8));
        TextRadioButton->setText(QApplication::translate("SaveLogFileDialog", "Text", 0, QApplication::UnicodeUTF8));
        HTMLRadioButton->setText(QApplication::translate("SaveLogFileDialog", "HTML", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SaveLogFileDialog: public Ui_SaveLogFileDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SAVELOGFILE_H
