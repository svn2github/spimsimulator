/********************************************************************************
** Form generated from reading UI file 'settings.ui'
**
** Created: Wed Sep 1 21:39:39 2010
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGS_H
#define UI_SETTINGS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTabWidget>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <settablecheckbox.h>

QT_BEGIN_NAMESPACE

class Ui_SettingDialog
{
public:
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QGroupBox *groupBox_3;
    QWidget *gridLayoutWidget_3;
    QGridLayout *gridLayout_3;
    QCheckBox *loadExceptionHandlerCheckBox;
    QLabel *label_2;
    QToolButton *exceptionHandlerToolButton;
    QLineEdit *exceptionHandlerLineEdit;
    QSpacerItem *horizontalSpacer_3;
    QGroupBox *groupBox_2;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_2;
    settableCheckBox *bareMachineCheckBox;
    settableCheckBox *delayedBranchCheckBox;
    settableCheckBox *delayedLoadCheckBox;
    QCheckBox *mappedIOCheckBox;
    settableCheckBox *pseudoInstCheckBox;
    QPushButton *simplePushButton;
    QPushButton *barePushButton;
    QWidget *tab_2;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QLineEdit *recentFilesLineEdit;
    QGroupBox *groupBox_4;
    QWidget *gridLayoutWidget_4;
    QGridLayout *gridLayout_4;
    QToolButton *regWinFontToolButton;
    QToolButton *regWinBackgroundToolButton;
    QLineEdit *regWinFontLineEdit;
    QLineEdit *regWinBackgroundLineEdit;
    QLabel *label;
    QLabel *label_4;
    QLineEdit *regWinFontColorLineEdit;
    QLabel *label_7;
    QToolButton *regWinFontColorToolButton;
    QSpacerItem *horizontalSpacer;
    QGroupBox *groupBox_41;
    QWidget *gridLayoutWidget_41;
    QGridLayout *gridLayout_41;
    QToolButton *textWinFontToolButton;
    QToolButton *textWinBackgroundToolButton;
    QLineEdit *textWinFontLineEdit;
    QLineEdit *textWinBackgroundLineEdit;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_8;
    QLineEdit *textWinFontColorLineEdit;
    QToolButton *textWinFontColorToolButton;
    QSpacerItem *horizontalSpacer_2;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *SettingDialog)
    {
        if (SettingDialog->objectName().isEmpty())
            SettingDialog->setObjectName(QString::fromUtf8("SettingDialog"));
        SettingDialog->resize(600, 466);
        tabWidget = new QTabWidget(SettingDialog);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(10, 0, 580, 421));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        gridLayoutWidget = new QWidget(tab);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(20, 10, 531, 371));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        groupBox_3 = new QGroupBox(gridLayoutWidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        gridLayoutWidget_3 = new QWidget(groupBox_3);
        gridLayoutWidget_3->setObjectName(QString::fromUtf8("gridLayoutWidget_3"));
        gridLayoutWidget_3->setGeometry(QRect(20, 20, 491, 61));
        gridLayout_3 = new QGridLayout(gridLayoutWidget_3);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        loadExceptionHandlerCheckBox = new QCheckBox(gridLayoutWidget_3);
        loadExceptionHandlerCheckBox->setObjectName(QString::fromUtf8("loadExceptionHandlerCheckBox"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(loadExceptionHandlerCheckBox->sizePolicy().hasHeightForWidth());
        loadExceptionHandlerCheckBox->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(loadExceptionHandlerCheckBox, 0, 0, 1, 1);

        label_2 = new QLabel(gridLayoutWidget_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(label_2, 0, 2, 1, 1);

        exceptionHandlerToolButton = new QToolButton(gridLayoutWidget_3);
        exceptionHandlerToolButton->setObjectName(QString::fromUtf8("exceptionHandlerToolButton"));

        gridLayout_3->addWidget(exceptionHandlerToolButton, 0, 4, 1, 1);

        exceptionHandlerLineEdit = new QLineEdit(gridLayoutWidget_3);
        exceptionHandlerLineEdit->setObjectName(QString::fromUtf8("exceptionHandlerLineEdit"));
        sizePolicy.setHeightForWidth(exceptionHandlerLineEdit->sizePolicy().hasHeightForWidth());
        exceptionHandlerLineEdit->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(exceptionHandlerLineEdit, 0, 3, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_3, 0, 1, 1, 1);


        gridLayout->addWidget(groupBox_3, 1, 0, 1, 1);

        groupBox_2 = new QGroupBox(gridLayoutWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayoutWidget_2 = new QWidget(groupBox_2);
        gridLayoutWidget_2->setObjectName(QString::fromUtf8("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(20, 30, 491, 88));
        gridLayout_2 = new QGridLayout(gridLayoutWidget_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        bareMachineCheckBox = new settableCheckBox(gridLayoutWidget_2);
        bareMachineCheckBox->setObjectName(QString::fromUtf8("bareMachineCheckBox"));

        gridLayout_2->addWidget(bareMachineCheckBox, 0, 0, 1, 1);

        delayedBranchCheckBox = new settableCheckBox(gridLayoutWidget_2);
        delayedBranchCheckBox->setObjectName(QString::fromUtf8("delayedBranchCheckBox"));

        gridLayout_2->addWidget(delayedBranchCheckBox, 1, 0, 1, 1);

        delayedLoadCheckBox = new settableCheckBox(gridLayoutWidget_2);
        delayedLoadCheckBox->setObjectName(QString::fromUtf8("delayedLoadCheckBox"));

        gridLayout_2->addWidget(delayedLoadCheckBox, 1, 1, 1, 1);

        mappedIOCheckBox = new QCheckBox(gridLayoutWidget_2);
        mappedIOCheckBox->setObjectName(QString::fromUtf8("mappedIOCheckBox"));

        gridLayout_2->addWidget(mappedIOCheckBox, 2, 0, 1, 1);

        pseudoInstCheckBox = new settableCheckBox(gridLayoutWidget_2);
        pseudoInstCheckBox->setObjectName(QString::fromUtf8("pseudoInstCheckBox"));

        gridLayout_2->addWidget(pseudoInstCheckBox, 0, 1, 1, 1);

        simplePushButton = new QPushButton(groupBox_2);
        simplePushButton->setObjectName(QString::fromUtf8("simplePushButton"));
        simplePushButton->setGeometry(QRect(120, 140, 100, 23));
        barePushButton = new QPushButton(groupBox_2);
        barePushButton->setObjectName(QString::fromUtf8("barePushButton"));
        barePushButton->setGeometry(QRect(300, 140, 100, 23));

        gridLayout->addWidget(groupBox_2, 0, 0, 1, 1);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        verticalLayoutWidget = new QWidget(tab_2);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(20, 10, 531, 371));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        groupBox = new QGroupBox(verticalLayoutWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        horizontalLayoutWidget_2 = new QWidget(groupBox);
        horizontalLayoutWidget_2->setObjectName(QString::fromUtf8("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(20, 20, 300, 80));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(horizontalLayoutWidget_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_2->addWidget(label_3);

        recentFilesLineEdit = new QLineEdit(horizontalLayoutWidget_2);
        recentFilesLineEdit->setObjectName(QString::fromUtf8("recentFilesLineEdit"));
        sizePolicy.setHeightForWidth(recentFilesLineEdit->sizePolicy().hasHeightForWidth());
        recentFilesLineEdit->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(recentFilesLineEdit);


        verticalLayout->addWidget(groupBox);

        groupBox_4 = new QGroupBox(verticalLayoutWidget);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        gridLayoutWidget_4 = new QWidget(groupBox_4);
        gridLayoutWidget_4->setObjectName(QString::fromUtf8("gridLayoutWidget_4"));
        gridLayoutWidget_4->setGeometry(QRect(20, 20, 480, 91));
        gridLayout_4 = new QGridLayout(gridLayoutWidget_4);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        regWinFontToolButton = new QToolButton(gridLayoutWidget_4);
        regWinFontToolButton->setObjectName(QString::fromUtf8("regWinFontToolButton"));

        gridLayout_4->addWidget(regWinFontToolButton, 0, 2, 1, 1);

        regWinBackgroundToolButton = new QToolButton(gridLayoutWidget_4);
        regWinBackgroundToolButton->setObjectName(QString::fromUtf8("regWinBackgroundToolButton"));

        gridLayout_4->addWidget(regWinBackgroundToolButton, 1, 2, 1, 1);

        regWinFontLineEdit = new QLineEdit(gridLayoutWidget_4);
        regWinFontLineEdit->setObjectName(QString::fromUtf8("regWinFontLineEdit"));
        sizePolicy.setHeightForWidth(regWinFontLineEdit->sizePolicy().hasHeightForWidth());
        regWinFontLineEdit->setSizePolicy(sizePolicy);

        gridLayout_4->addWidget(regWinFontLineEdit, 0, 1, 1, 1);

        regWinBackgroundLineEdit = new QLineEdit(gridLayoutWidget_4);
        regWinBackgroundLineEdit->setObjectName(QString::fromUtf8("regWinBackgroundLineEdit"));
        sizePolicy.setHeightForWidth(regWinBackgroundLineEdit->sizePolicy().hasHeightForWidth());
        regWinBackgroundLineEdit->setSizePolicy(sizePolicy);

        gridLayout_4->addWidget(regWinBackgroundLineEdit, 1, 1, 1, 1);

        label = new QLabel(gridLayoutWidget_4);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_4->addWidget(label, 0, 0, 1, 1);

        label_4 = new QLabel(gridLayoutWidget_4);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_4->addWidget(label_4, 1, 0, 1, 1);

        regWinFontColorLineEdit = new QLineEdit(gridLayoutWidget_4);
        regWinFontColorLineEdit->setObjectName(QString::fromUtf8("regWinFontColorLineEdit"));

        gridLayout_4->addWidget(regWinFontColorLineEdit, 0, 5, 1, 1);

        label_7 = new QLabel(gridLayoutWidget_4);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_4->addWidget(label_7, 0, 4, 1, 1);

        regWinFontColorToolButton = new QToolButton(gridLayoutWidget_4);
        regWinFontColorToolButton->setObjectName(QString::fromUtf8("regWinFontColorToolButton"));

        gridLayout_4->addWidget(regWinFontColorToolButton, 0, 6, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer, 0, 3, 1, 1);


        verticalLayout->addWidget(groupBox_4);

        groupBox_41 = new QGroupBox(verticalLayoutWidget);
        groupBox_41->setObjectName(QString::fromUtf8("groupBox_41"));
        gridLayoutWidget_41 = new QWidget(groupBox_41);
        gridLayoutWidget_41->setObjectName(QString::fromUtf8("gridLayoutWidget_41"));
        gridLayoutWidget_41->setGeometry(QRect(20, 20, 503, 91));
        gridLayout_41 = new QGridLayout(gridLayoutWidget_41);
        gridLayout_41->setObjectName(QString::fromUtf8("gridLayout_41"));
        gridLayout_41->setContentsMargins(0, 0, 0, 0);
        textWinFontToolButton = new QToolButton(gridLayoutWidget_41);
        textWinFontToolButton->setObjectName(QString::fromUtf8("textWinFontToolButton"));

        gridLayout_41->addWidget(textWinFontToolButton, 0, 2, 1, 1);

        textWinBackgroundToolButton = new QToolButton(gridLayoutWidget_41);
        textWinBackgroundToolButton->setObjectName(QString::fromUtf8("textWinBackgroundToolButton"));

        gridLayout_41->addWidget(textWinBackgroundToolButton, 1, 2, 1, 1);

        textWinFontLineEdit = new QLineEdit(gridLayoutWidget_41);
        textWinFontLineEdit->setObjectName(QString::fromUtf8("textWinFontLineEdit"));
        sizePolicy.setHeightForWidth(textWinFontLineEdit->sizePolicy().hasHeightForWidth());
        textWinFontLineEdit->setSizePolicy(sizePolicy);

        gridLayout_41->addWidget(textWinFontLineEdit, 0, 1, 1, 1);

        textWinBackgroundLineEdit = new QLineEdit(gridLayoutWidget_41);
        textWinBackgroundLineEdit->setObjectName(QString::fromUtf8("textWinBackgroundLineEdit"));
        sizePolicy.setHeightForWidth(textWinBackgroundLineEdit->sizePolicy().hasHeightForWidth());
        textWinBackgroundLineEdit->setSizePolicy(sizePolicy);

        gridLayout_41->addWidget(textWinBackgroundLineEdit, 1, 1, 1, 1);

        label_5 = new QLabel(gridLayoutWidget_41);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_41->addWidget(label_5, 0, 0, 1, 1);

        label_6 = new QLabel(gridLayoutWidget_41);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_41->addWidget(label_6, 1, 0, 1, 1);

        label_8 = new QLabel(gridLayoutWidget_41);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_41->addWidget(label_8, 0, 4, 1, 1);

        textWinFontColorLineEdit = new QLineEdit(gridLayoutWidget_41);
        textWinFontColorLineEdit->setObjectName(QString::fromUtf8("textWinFontColorLineEdit"));

        gridLayout_41->addWidget(textWinFontColorLineEdit, 0, 5, 1, 1);

        textWinFontColorToolButton = new QToolButton(gridLayoutWidget_41);
        textWinFontColorToolButton->setObjectName(QString::fromUtf8("textWinFontColorToolButton"));

        gridLayout_41->addWidget(textWinFontColorToolButton, 0, 6, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_41->addItem(horizontalSpacer_2, 0, 3, 1, 1);


        verticalLayout->addWidget(groupBox_41);

        tabWidget->addTab(tab_2, QString());
        buttonBox = new QDialogButtonBox(SettingDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(210, 430, 180, 23));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        buttonBox->setCenterButtons(true);
        QWidget::setTabOrder(tabWidget, bareMachineCheckBox);
        QWidget::setTabOrder(bareMachineCheckBox, pseudoInstCheckBox);
        QWidget::setTabOrder(pseudoInstCheckBox, delayedBranchCheckBox);
        QWidget::setTabOrder(delayedBranchCheckBox, delayedLoadCheckBox);
        QWidget::setTabOrder(delayedLoadCheckBox, mappedIOCheckBox);
        QWidget::setTabOrder(mappedIOCheckBox, simplePushButton);
        QWidget::setTabOrder(simplePushButton, barePushButton);
        QWidget::setTabOrder(barePushButton, loadExceptionHandlerCheckBox);
        QWidget::setTabOrder(loadExceptionHandlerCheckBox, exceptionHandlerLineEdit);
        QWidget::setTabOrder(exceptionHandlerLineEdit, exceptionHandlerToolButton);
        QWidget::setTabOrder(exceptionHandlerToolButton, buttonBox);
        QWidget::setTabOrder(buttonBox, recentFilesLineEdit);
        QWidget::setTabOrder(recentFilesLineEdit, regWinFontLineEdit);
        QWidget::setTabOrder(regWinFontLineEdit, regWinFontToolButton);
        QWidget::setTabOrder(regWinFontToolButton, regWinFontColorLineEdit);
        QWidget::setTabOrder(regWinFontColorLineEdit, regWinFontColorToolButton);
        QWidget::setTabOrder(regWinFontColorToolButton, regWinBackgroundLineEdit);
        QWidget::setTabOrder(regWinBackgroundLineEdit, regWinBackgroundToolButton);
        QWidget::setTabOrder(regWinBackgroundToolButton, textWinFontLineEdit);
        QWidget::setTabOrder(textWinFontLineEdit, textWinFontToolButton);
        QWidget::setTabOrder(textWinFontToolButton, textWinFontColorLineEdit);
        QWidget::setTabOrder(textWinFontColorLineEdit, textWinFontColorToolButton);
        QWidget::setTabOrder(textWinFontColorToolButton, textWinBackgroundLineEdit);
        QWidget::setTabOrder(textWinBackgroundLineEdit, textWinBackgroundToolButton);

        retranslateUi(SettingDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), SettingDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SettingDialog, SLOT(reject()));

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(SettingDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingDialog)
    {
        SettingDialog->setWindowTitle(QApplication::translate("SettingDialog", "QtSPIM Settings", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("SettingDialog", "Exception Handler", 0, QApplication::UnicodeUTF8));
        loadExceptionHandlerCheckBox->setText(QApplication::translate("SettingDialog", "Load Exception Handler", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("SettingDialog", "File", 0, QApplication::UnicodeUTF8));
        exceptionHandlerToolButton->setText(QApplication::translate("SettingDialog", "...", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("SettingDialog", "MIPS Simulation Settings", 0, QApplication::UnicodeUTF8));
        bareMachineCheckBox->setText(QApplication::translate("SettingDialog", "Bare Machine", 0, QApplication::UnicodeUTF8));
        delayedBranchCheckBox->setText(QApplication::translate("SettingDialog", "Enable Delayed Branches", 0, QApplication::UnicodeUTF8));
        delayedLoadCheckBox->setText(QApplication::translate("SettingDialog", "Enable Delayed Loads", 0, QApplication::UnicodeUTF8));
        mappedIOCheckBox->setText(QApplication::translate("SettingDialog", "Enable Mapped IO", 0, QApplication::UnicodeUTF8));
        pseudoInstCheckBox->setText(QApplication::translate("SettingDialog", "Accept Pseudo Instructions", 0, QApplication::UnicodeUTF8));
        simplePushButton->setText(QApplication::translate("SettingDialog", "Simple Machine", 0, QApplication::UnicodeUTF8));
        barePushButton->setText(QApplication::translate("SettingDialog", "Bare Machine", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("SettingDialog", "MIPS", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("SettingDialog", "Simulator", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("SettingDialog", "Length of Recent File list", 0, QApplication::UnicodeUTF8));
        groupBox_4->setTitle(QApplication::translate("SettingDialog", "Register Windows", 0, QApplication::UnicodeUTF8));
        regWinFontToolButton->setText(QApplication::translate("SettingDialog", "...", 0, QApplication::UnicodeUTF8));
        regWinBackgroundToolButton->setText(QApplication::translate("SettingDialog", "...", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("SettingDialog", "Font", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("SettingDialog", "Background Color", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("SettingDialog", "Color", 0, QApplication::UnicodeUTF8));
        regWinFontColorToolButton->setText(QApplication::translate("SettingDialog", "...", 0, QApplication::UnicodeUTF8));
        groupBox_41->setTitle(QApplication::translate("SettingDialog", "Text and Data Windows", 0, QApplication::UnicodeUTF8));
        textWinFontToolButton->setText(QApplication::translate("SettingDialog", "...", 0, QApplication::UnicodeUTF8));
        textWinBackgroundToolButton->setText(QApplication::translate("SettingDialog", "...", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("SettingDialog", "Font", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("SettingDialog", "Background Color", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("SettingDialog", "Color", 0, QApplication::UnicodeUTF8));
        textWinFontColorToolButton->setText(QApplication::translate("SettingDialog", "...", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("SettingDialog", "QtSPIM", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SettingDialog: public Ui_SettingDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGS_H
