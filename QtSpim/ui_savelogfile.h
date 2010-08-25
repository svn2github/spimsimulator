/********************************************************************************
** Form generated from reading UI file 'savelogfile.ui'
**
** Created: Mon Aug 23 20:38:13 2010
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
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
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
    QPushButton *BrowsePushButton;
    QLabel *label_2;
    QLineEdit *SaveLineEdit;
    QPushButton *SavePushButton;
    QPushButton *AbortPushButton;
    QRadioButton *TextRadioButton;
    QSpacerItem *verticalSpacer;
    QRadioButton *HTMLRadioButton;

    void setupUi(QDialog *SaveLogFileDialog)
    {
        if (SaveLogFileDialog->objectName().isEmpty())
            SaveLogFileDialog->setObjectName(QString::fromUtf8("SaveLogFileDialog"));
        SaveLogFileDialog->resize(370, 230);
        verticalLayoutWidget = new QWidget(SaveLogFileDialog);
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

        BrowsePushButton = new QPushButton(verticalLayoutWidget);
        BrowsePushButton->setObjectName(QString::fromUtf8("BrowsePushButton"));

        gridLayout->addWidget(BrowsePushButton, 8, 2, 1, 1);

        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 9, 0, 1, 1);

        SaveLineEdit = new QLineEdit(verticalLayoutWidget);
        SaveLineEdit->setObjectName(QString::fromUtf8("SaveLineEdit"));

        gridLayout->addWidget(SaveLineEdit, 9, 1, 1, 1);

        SavePushButton = new QPushButton(verticalLayoutWidget);
        SavePushButton->setObjectName(QString::fromUtf8("SavePushButton"));

        gridLayout->addWidget(SavePushButton, 9, 2, 1, 1);

        AbortPushButton = new QPushButton(verticalLayoutWidget);
        AbortPushButton->setObjectName(QString::fromUtf8("AbortPushButton"));

        gridLayout->addWidget(AbortPushButton, 10, 2, 1, 1);

        TextRadioButton = new QRadioButton(verticalLayoutWidget);
        TextRadioButton->setObjectName(QString::fromUtf8("TextRadioButton"));
        TextRadioButton->setChecked(true);

        gridLayout->addWidget(TextRadioButton, 7, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 60, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 6, 0, 1, 1);

        HTMLRadioButton = new QRadioButton(verticalLayoutWidget);
        HTMLRadioButton->setObjectName(QString::fromUtf8("HTMLRadioButton"));

        gridLayout->addWidget(HTMLRadioButton, 7, 1, 1, 1);


        retranslateUi(SaveLogFileDialog);
        QObject::connect(SavePushButton, SIGNAL(clicked()), SaveLogFileDialog, SLOT(accept()));
        QObject::connect(AbortPushButton, SIGNAL(clicked()), SaveLogFileDialog, SLOT(reject()));

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
        BrowsePushButton->setText(QApplication::translate("SaveLogFileDialog", "Browse", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("SaveLogFileDialog", "Save to file", 0, QApplication::UnicodeUTF8));
        SavePushButton->setText(QApplication::translate("SaveLogFileDialog", "Save", 0, QApplication::UnicodeUTF8));
        AbortPushButton->setText(QApplication::translate("SaveLogFileDialog", "Abort", 0, QApplication::UnicodeUTF8));
        TextRadioButton->setText(QApplication::translate("SaveLogFileDialog", "Text", 0, QApplication::UnicodeUTF8));
        HTMLRadioButton->setText(QApplication::translate("SaveLogFileDialog", "HTML", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SaveLogFileDialog: public Ui_SaveLogFileDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SAVELOGFILE_H
