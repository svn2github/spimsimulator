/********************************************************************************
** Form generated from reading UI file 'spimview.ui'
**
** Created: Thu Aug 5 22:07:18 2010
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SPIMVIEW_H
#define UI_SPIMVIEW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDockWidget>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QTextEdit>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SpimView
{
public:
    QAction *action_Open;
    QAction *action_Close;
    QAction *action_Save_Log_FIle;
    QAction *action_Exit;
    QAction *action_Clear_Registers;
    QAction *action_Reinitialize_Simulator;
    QAction *actionRe_Load_Source_File;
    QAction *action_Run;
    QAction *action_Single_Step;
    QAction *action_Multiple_Step;
    QAction *actionSet_Breakpoint;
    QAction *action_List_Breakpoints;
    QAction *actionChange_Memory_Location;
    QAction *action_Display_Symbols;
    QAction *actionSettings;
    QAction *actionBinary;
    QAction *actionOctal;
    QAction *actionHex;
    QAction *actionDecimal;
    QAction *actionChar;
    QAction *actionUser_Text;
    QAction *actionKernel_Text;
    QAction *actionNarrow_Range;
    QAction *actionComments;
    QAction *actionInstruction_Value;
    QAction *actionUser_Data;
    QAction *actionUser_Stack;
    QAction *actionKernel_Data;
    QAction *actionNarrow_Display;
    QAction *actionBinary_2;
    QAction *actionOctal_2;
    QAction *actionHex_2;
    QAction *actionDecimal_2;
    QAction *actionString;
    QAction *actionInteger_Registers;
    QAction *actionFP_Registers;
    QAction *actionText_Segment;
    QAction *actionData_Segment;
    QAction *actionConsole;
    QAction *actionSPIM_Messages;
    QAction *actionClear_Console;
    QAction *actionToolbar;
    QAction *actionStatus_Bar;
    QAction *actionView_Help;
    QAction *actionAbout_SPIM;
    QWidget *centralWidget;
    QTextEdit *xTextSegTextEdit;
    QMenuBar *menuBar;
    QMenu *menu_File;
    QMenu *menu_Simulator;
    QMenu *menu_Registers;
    QMenu *menu_Text_Segment;
    QMenu *menu_Data_Segment;
    QMenu *menu_Window;
    QMenu *menu_Help;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QDockWidget *IntRegDockWidget;
    QTextEdit *IntRegTextEdit;
    QDockWidget *FPRegDockWidget;
    QTextEdit *FPRegTextEdit;
    QDockWidget *TextSegDockWidget;
    QTextEdit *TextSegmentTextEdit;
    QDockWidget *DataSegDockWidget;
    QTextEdit *DataSegTextEdit;
    QDockWidget *ConsoleDockWidget;
    QTextEdit *ConsoleTextEdit;

    void setupUi(QMainWindow *SpimView)
    {
        if (SpimView->objectName().isEmpty())
            SpimView->setObjectName(QString::fromUtf8("SpimView"));
        SpimView->resize(1042, 768);
        SpimView->setDockOptions(QMainWindow::AnimatedDocks|QMainWindow::ForceTabbedDocks|QMainWindow::VerticalTabs);
        action_Open = new QAction(SpimView);
        action_Open->setObjectName(QString::fromUtf8("action_Open"));
        action_Close = new QAction(SpimView);
        action_Close->setObjectName(QString::fromUtf8("action_Close"));
        action_Save_Log_FIle = new QAction(SpimView);
        action_Save_Log_FIle->setObjectName(QString::fromUtf8("action_Save_Log_FIle"));
        action_Exit = new QAction(SpimView);
        action_Exit->setObjectName(QString::fromUtf8("action_Exit"));
        action_Clear_Registers = new QAction(SpimView);
        action_Clear_Registers->setObjectName(QString::fromUtf8("action_Clear_Registers"));
        action_Reinitialize_Simulator = new QAction(SpimView);
        action_Reinitialize_Simulator->setObjectName(QString::fromUtf8("action_Reinitialize_Simulator"));
        actionRe_Load_Source_File = new QAction(SpimView);
        actionRe_Load_Source_File->setObjectName(QString::fromUtf8("actionRe_Load_Source_File"));
        action_Run = new QAction(SpimView);
        action_Run->setObjectName(QString::fromUtf8("action_Run"));
        action_Single_Step = new QAction(SpimView);
        action_Single_Step->setObjectName(QString::fromUtf8("action_Single_Step"));
        action_Multiple_Step = new QAction(SpimView);
        action_Multiple_Step->setObjectName(QString::fromUtf8("action_Multiple_Step"));
        actionSet_Breakpoint = new QAction(SpimView);
        actionSet_Breakpoint->setObjectName(QString::fromUtf8("actionSet_Breakpoint"));
        action_List_Breakpoints = new QAction(SpimView);
        action_List_Breakpoints->setObjectName(QString::fromUtf8("action_List_Breakpoints"));
        actionChange_Memory_Location = new QAction(SpimView);
        actionChange_Memory_Location->setObjectName(QString::fromUtf8("actionChange_Memory_Location"));
        action_Display_Symbols = new QAction(SpimView);
        action_Display_Symbols->setObjectName(QString::fromUtf8("action_Display_Symbols"));
        actionSettings = new QAction(SpimView);
        actionSettings->setObjectName(QString::fromUtf8("actionSettings"));
        actionBinary = new QAction(SpimView);
        actionBinary->setObjectName(QString::fromUtf8("actionBinary"));
        actionBinary->setCheckable(true);
        actionOctal = new QAction(SpimView);
        actionOctal->setObjectName(QString::fromUtf8("actionOctal"));
        actionOctal->setCheckable(true);
        actionHex = new QAction(SpimView);
        actionHex->setObjectName(QString::fromUtf8("actionHex"));
        actionHex->setCheckable(true);
        actionHex->setChecked(true);
        actionDecimal = new QAction(SpimView);
        actionDecimal->setObjectName(QString::fromUtf8("actionDecimal"));
        actionDecimal->setCheckable(true);
        actionChar = new QAction(SpimView);
        actionChar->setObjectName(QString::fromUtf8("actionChar"));
        actionChar->setCheckable(true);
        actionUser_Text = new QAction(SpimView);
        actionUser_Text->setObjectName(QString::fromUtf8("actionUser_Text"));
        actionUser_Text->setCheckable(true);
        actionUser_Text->setChecked(true);
        actionKernel_Text = new QAction(SpimView);
        actionKernel_Text->setObjectName(QString::fromUtf8("actionKernel_Text"));
        actionKernel_Text->setCheckable(true);
        actionKernel_Text->setChecked(true);
        actionNarrow_Range = new QAction(SpimView);
        actionNarrow_Range->setObjectName(QString::fromUtf8("actionNarrow_Range"));
        actionComments = new QAction(SpimView);
        actionComments->setObjectName(QString::fromUtf8("actionComments"));
        actionComments->setCheckable(true);
        actionComments->setChecked(true);
        actionInstruction_Value = new QAction(SpimView);
        actionInstruction_Value->setObjectName(QString::fromUtf8("actionInstruction_Value"));
        actionInstruction_Value->setCheckable(true);
        actionInstruction_Value->setChecked(true);
        actionUser_Data = new QAction(SpimView);
        actionUser_Data->setObjectName(QString::fromUtf8("actionUser_Data"));
        actionUser_Data->setCheckable(true);
        actionUser_Data->setChecked(true);
        actionUser_Stack = new QAction(SpimView);
        actionUser_Stack->setObjectName(QString::fromUtf8("actionUser_Stack"));
        actionUser_Stack->setCheckable(true);
        actionUser_Stack->setChecked(true);
        actionKernel_Data = new QAction(SpimView);
        actionKernel_Data->setObjectName(QString::fromUtf8("actionKernel_Data"));
        actionKernel_Data->setCheckable(true);
        actionKernel_Data->setChecked(true);
        actionNarrow_Display = new QAction(SpimView);
        actionNarrow_Display->setObjectName(QString::fromUtf8("actionNarrow_Display"));
        actionBinary_2 = new QAction(SpimView);
        actionBinary_2->setObjectName(QString::fromUtf8("actionBinary_2"));
        actionBinary_2->setCheckable(true);
        actionOctal_2 = new QAction(SpimView);
        actionOctal_2->setObjectName(QString::fromUtf8("actionOctal_2"));
        actionOctal_2->setCheckable(true);
        actionHex_2 = new QAction(SpimView);
        actionHex_2->setObjectName(QString::fromUtf8("actionHex_2"));
        actionHex_2->setCheckable(true);
        actionHex_2->setChecked(true);
        actionDecimal_2 = new QAction(SpimView);
        actionDecimal_2->setObjectName(QString::fromUtf8("actionDecimal_2"));
        actionDecimal_2->setCheckable(true);
        actionString = new QAction(SpimView);
        actionString->setObjectName(QString::fromUtf8("actionString"));
        actionString->setCheckable(true);
        actionInteger_Registers = new QAction(SpimView);
        actionInteger_Registers->setObjectName(QString::fromUtf8("actionInteger_Registers"));
        actionInteger_Registers->setCheckable(true);
        actionInteger_Registers->setChecked(true);
        actionFP_Registers = new QAction(SpimView);
        actionFP_Registers->setObjectName(QString::fromUtf8("actionFP_Registers"));
        actionFP_Registers->setCheckable(true);
        actionFP_Registers->setChecked(true);
        actionText_Segment = new QAction(SpimView);
        actionText_Segment->setObjectName(QString::fromUtf8("actionText_Segment"));
        actionText_Segment->setCheckable(true);
        actionText_Segment->setChecked(true);
        actionData_Segment = new QAction(SpimView);
        actionData_Segment->setObjectName(QString::fromUtf8("actionData_Segment"));
        actionData_Segment->setCheckable(true);
        actionData_Segment->setChecked(true);
        actionConsole = new QAction(SpimView);
        actionConsole->setObjectName(QString::fromUtf8("actionConsole"));
        actionConsole->setCheckable(true);
        actionConsole->setChecked(true);
        actionSPIM_Messages = new QAction(SpimView);
        actionSPIM_Messages->setObjectName(QString::fromUtf8("actionSPIM_Messages"));
        actionSPIM_Messages->setCheckable(true);
        actionSPIM_Messages->setChecked(true);
        actionClear_Console = new QAction(SpimView);
        actionClear_Console->setObjectName(QString::fromUtf8("actionClear_Console"));
        actionToolbar = new QAction(SpimView);
        actionToolbar->setObjectName(QString::fromUtf8("actionToolbar"));
        actionToolbar->setCheckable(true);
        actionToolbar->setChecked(true);
        actionStatus_Bar = new QAction(SpimView);
        actionStatus_Bar->setObjectName(QString::fromUtf8("actionStatus_Bar"));
        actionView_Help = new QAction(SpimView);
        actionView_Help->setObjectName(QString::fromUtf8("actionView_Help"));
        actionAbout_SPIM = new QAction(SpimView);
        actionAbout_SPIM->setObjectName(QString::fromUtf8("actionAbout_SPIM"));
        centralWidget = new QWidget(SpimView);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        xTextSegTextEdit = new QTextEdit(centralWidget);
        xTextSegTextEdit->setObjectName(QString::fromUtf8("xTextSegTextEdit"));
        xTextSegTextEdit->setGeometry(QRect(0, 0, 0, 0));
        xTextSegTextEdit->setUndoRedoEnabled(false);
        xTextSegTextEdit->setReadOnly(true);
        SpimView->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(SpimView);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1042, 21));
        menu_File = new QMenu(menuBar);
        menu_File->setObjectName(QString::fromUtf8("menu_File"));
        menu_Simulator = new QMenu(menuBar);
        menu_Simulator->setObjectName(QString::fromUtf8("menu_Simulator"));
        menu_Registers = new QMenu(menuBar);
        menu_Registers->setObjectName(QString::fromUtf8("menu_Registers"));
        menu_Text_Segment = new QMenu(menuBar);
        menu_Text_Segment->setObjectName(QString::fromUtf8("menu_Text_Segment"));
        menu_Data_Segment = new QMenu(menuBar);
        menu_Data_Segment->setObjectName(QString::fromUtf8("menu_Data_Segment"));
        menu_Window = new QMenu(menuBar);
        menu_Window->setObjectName(QString::fromUtf8("menu_Window"));
        menu_Help = new QMenu(menuBar);
        menu_Help->setObjectName(QString::fromUtf8("menu_Help"));
        SpimView->setMenuBar(menuBar);
        mainToolBar = new QToolBar(SpimView);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        SpimView->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(SpimView);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        SpimView->setStatusBar(statusBar);
        IntRegDockWidget = new QDockWidget(SpimView);
        IntRegDockWidget->setObjectName(QString::fromUtf8("IntRegDockWidget"));
        IntRegDockWidget->setAllowedAreas(Qt::LeftDockWidgetArea);
        IntRegTextEdit = new QTextEdit();
        IntRegTextEdit->setObjectName(QString::fromUtf8("IntRegTextEdit"));
        IntRegTextEdit->setMinimumSize(QSize(275, 310));
        IntRegTextEdit->setUndoRedoEnabled(false);
        IntRegTextEdit->setReadOnly(true);
        IntRegDockWidget->setWidget(IntRegTextEdit);
        SpimView->addDockWidget(static_cast<Qt::DockWidgetArea>(1), IntRegDockWidget);
        FPRegDockWidget = new QDockWidget(SpimView);
        FPRegDockWidget->setObjectName(QString::fromUtf8("FPRegDockWidget"));
        FPRegDockWidget->setAllowedAreas(Qt::LeftDockWidgetArea);
        FPRegTextEdit = new QTextEdit();
        FPRegTextEdit->setObjectName(QString::fromUtf8("FPRegTextEdit"));
        FPRegTextEdit->setUndoRedoEnabled(false);
        FPRegTextEdit->setReadOnly(true);
        FPRegDockWidget->setWidget(FPRegTextEdit);
        SpimView->addDockWidget(static_cast<Qt::DockWidgetArea>(1), FPRegDockWidget);
        TextSegDockWidget = new QDockWidget(SpimView);
        TextSegDockWidget->setObjectName(QString::fromUtf8("TextSegDockWidget"));
        TextSegmentTextEdit = new QTextEdit();
        TextSegmentTextEdit->setObjectName(QString::fromUtf8("TextSegmentTextEdit"));
        TextSegmentTextEdit->setMinimumSize(QSize(749, 600));
        TextSegmentTextEdit->setUndoRedoEnabled(false);
        TextSegmentTextEdit->setReadOnly(true);
        TextSegDockWidget->setWidget(TextSegmentTextEdit);
        SpimView->addDockWidget(static_cast<Qt::DockWidgetArea>(2), TextSegDockWidget);
        DataSegDockWidget = new QDockWidget(SpimView);
        DataSegDockWidget->setObjectName(QString::fromUtf8("DataSegDockWidget"));
        DataSegDockWidget->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
        DataSegTextEdit = new QTextEdit();
        DataSegTextEdit->setObjectName(QString::fromUtf8("DataSegTextEdit"));
        DataSegTextEdit->setUndoRedoEnabled(false);
        DataSegTextEdit->setReadOnly(true);
        DataSegDockWidget->setWidget(DataSegTextEdit);
        SpimView->addDockWidget(static_cast<Qt::DockWidgetArea>(2), DataSegDockWidget);
        ConsoleDockWidget = new QDockWidget(SpimView);
        ConsoleDockWidget->setObjectName(QString::fromUtf8("ConsoleDockWidget"));
        ConsoleDockWidget->setAllowedAreas(Qt::AllDockWidgetAreas);
        ConsoleTextEdit = new QTextEdit();
        ConsoleTextEdit->setObjectName(QString::fromUtf8("ConsoleTextEdit"));
        ConsoleTextEdit->setUndoRedoEnabled(false);
        ConsoleTextEdit->setReadOnly(true);
        ConsoleDockWidget->setWidget(ConsoleTextEdit);
        SpimView->addDockWidget(static_cast<Qt::DockWidgetArea>(2), ConsoleDockWidget);

        menuBar->addAction(menu_File->menuAction());
        menuBar->addAction(menu_Simulator->menuAction());
        menuBar->addAction(menu_Registers->menuAction());
        menuBar->addAction(menu_Text_Segment->menuAction());
        menuBar->addAction(menu_Data_Segment->menuAction());
        menuBar->addAction(menu_Window->menuAction());
        menuBar->addAction(menu_Help->menuAction());
        menu_File->addAction(action_Open);
        menu_File->addAction(actionRe_Load_Source_File);
        menu_File->addAction(action_Close);
        menu_File->addSeparator();
        menu_File->addAction(action_Save_Log_FIle);
        menu_File->addSeparator();
        menu_File->addAction(action_Exit);
        menu_Simulator->addAction(action_Clear_Registers);
        menu_Simulator->addAction(action_Reinitialize_Simulator);
        menu_Simulator->addSeparator();
        menu_Simulator->addAction(action_Run);
        menu_Simulator->addAction(action_Single_Step);
        menu_Simulator->addAction(action_Multiple_Step);
        menu_Simulator->addSeparator();
        menu_Simulator->addAction(actionSet_Breakpoint);
        menu_Simulator->addAction(action_List_Breakpoints);
        menu_Simulator->addSeparator();
        menu_Simulator->addAction(actionChange_Memory_Location);
        menu_Simulator->addSeparator();
        menu_Simulator->addAction(action_Display_Symbols);
        menu_Simulator->addSeparator();
        menu_Simulator->addAction(actionSettings);
        menu_Registers->addAction(actionBinary);
        menu_Registers->addAction(actionOctal);
        menu_Registers->addAction(actionHex);
        menu_Registers->addAction(actionDecimal);
        menu_Registers->addAction(actionChar);
        menu_Text_Segment->addAction(actionUser_Text);
        menu_Text_Segment->addAction(actionKernel_Text);
        menu_Text_Segment->addSeparator();
        menu_Text_Segment->addAction(actionNarrow_Range);
        menu_Text_Segment->addSeparator();
        menu_Text_Segment->addAction(actionComments);
        menu_Text_Segment->addAction(actionInstruction_Value);
        menu_Data_Segment->addAction(actionUser_Data);
        menu_Data_Segment->addAction(actionUser_Stack);
        menu_Data_Segment->addAction(actionKernel_Data);
        menu_Data_Segment->addSeparator();
        menu_Data_Segment->addAction(actionNarrow_Display);
        menu_Data_Segment->addSeparator();
        menu_Data_Segment->addAction(actionBinary_2);
        menu_Data_Segment->addAction(actionOctal_2);
        menu_Data_Segment->addAction(actionHex_2);
        menu_Data_Segment->addAction(actionDecimal_2);
        menu_Data_Segment->addAction(actionString);
        menu_Window->addAction(actionInteger_Registers);
        menu_Window->addAction(actionFP_Registers);
        menu_Window->addAction(actionText_Segment);
        menu_Window->addAction(actionData_Segment);
        menu_Window->addAction(actionConsole);
        menu_Window->addAction(actionSPIM_Messages);
        menu_Window->addSeparator();
        menu_Window->addAction(actionClear_Console);
        menu_Window->addAction(actionToolbar);
        menu_Help->addAction(actionView_Help);
        menu_Help->addAction(actionAbout_SPIM);

        retranslateUi(SpimView);

        QMetaObject::connectSlotsByName(SpimView);
    } // setupUi

    void retranslateUi(QMainWindow *SpimView)
    {
        SpimView->setWindowTitle(QApplication::translate("SpimView", "SpimView", 0, QApplication::UnicodeUTF8));
        action_Open->setText(QApplication::translate("SpimView", "&Open Source File", 0, QApplication::UnicodeUTF8));
        action_Close->setText(QApplication::translate("SpimView", "&Close Source File", 0, QApplication::UnicodeUTF8));
        action_Save_Log_FIle->setText(QApplication::translate("SpimView", "&Save Log FIle", 0, QApplication::UnicodeUTF8));
        action_Exit->setText(QApplication::translate("SpimView", "&Exit", 0, QApplication::UnicodeUTF8));
        action_Clear_Registers->setText(QApplication::translate("SpimView", "&Clear Registers", 0, QApplication::UnicodeUTF8));
        action_Reinitialize_Simulator->setText(QApplication::translate("SpimView", "Re&initialize Simulator", 0, QApplication::UnicodeUTF8));
        actionRe_Load_Source_File->setText(QApplication::translate("SpimView", "Re&Load Source File", 0, QApplication::UnicodeUTF8));
        action_Run->setText(QApplication::translate("SpimView", "&Run", 0, QApplication::UnicodeUTF8));
        action_Single_Step->setText(QApplication::translate("SpimView", "&Single Step", 0, QApplication::UnicodeUTF8));
        action_Multiple_Step->setText(QApplication::translate("SpimView", "&Multiple Step", 0, QApplication::UnicodeUTF8));
        actionSet_Breakpoint->setText(QApplication::translate("SpimView", "Set &Breakpoint", 0, QApplication::UnicodeUTF8));
        action_List_Breakpoints->setText(QApplication::translate("SpimView", "&List Breakpoints", 0, QApplication::UnicodeUTF8));
        actionChange_Memory_Location->setText(QApplication::translate("SpimView", "Change &Memory Location", 0, QApplication::UnicodeUTF8));
        action_Display_Symbols->setText(QApplication::translate("SpimView", "&Display Symbols", 0, QApplication::UnicodeUTF8));
        actionSettings->setText(QApplication::translate("SpimView", "Settings", 0, QApplication::UnicodeUTF8));
        actionBinary->setText(QApplication::translate("SpimView", "Binary", 0, QApplication::UnicodeUTF8));
        actionOctal->setText(QApplication::translate("SpimView", "Octal", 0, QApplication::UnicodeUTF8));
        actionHex->setText(QApplication::translate("SpimView", "Hex", 0, QApplication::UnicodeUTF8));
        actionDecimal->setText(QApplication::translate("SpimView", "Decimal", 0, QApplication::UnicodeUTF8));
        actionChar->setText(QApplication::translate("SpimView", "Char", 0, QApplication::UnicodeUTF8));
        actionUser_Text->setText(QApplication::translate("SpimView", "User Text", 0, QApplication::UnicodeUTF8));
        actionKernel_Text->setText(QApplication::translate("SpimView", "Kernel Text", 0, QApplication::UnicodeUTF8));
        actionNarrow_Range->setText(QApplication::translate("SpimView", "Narrow Display", 0, QApplication::UnicodeUTF8));
        actionComments->setText(QApplication::translate("SpimView", "Comments", 0, QApplication::UnicodeUTF8));
        actionInstruction_Value->setText(QApplication::translate("SpimView", "Instruction Value", 0, QApplication::UnicodeUTF8));
        actionUser_Data->setText(QApplication::translate("SpimView", "User Data", 0, QApplication::UnicodeUTF8));
        actionUser_Stack->setText(QApplication::translate("SpimView", "User Stack", 0, QApplication::UnicodeUTF8));
        actionKernel_Data->setText(QApplication::translate("SpimView", "Kernel Data", 0, QApplication::UnicodeUTF8));
        actionNarrow_Display->setText(QApplication::translate("SpimView", "Narrow Display", 0, QApplication::UnicodeUTF8));
        actionBinary_2->setText(QApplication::translate("SpimView", "Binary", 0, QApplication::UnicodeUTF8));
        actionOctal_2->setText(QApplication::translate("SpimView", "Octal", 0, QApplication::UnicodeUTF8));
        actionHex_2->setText(QApplication::translate("SpimView", "Hex", 0, QApplication::UnicodeUTF8));
        actionDecimal_2->setText(QApplication::translate("SpimView", "Decimal", 0, QApplication::UnicodeUTF8));
        actionString->setText(QApplication::translate("SpimView", "String", 0, QApplication::UnicodeUTF8));
        actionInteger_Registers->setText(QApplication::translate("SpimView", "Integer Registers", 0, QApplication::UnicodeUTF8));
        actionFP_Registers->setText(QApplication::translate("SpimView", "FP Registers", 0, QApplication::UnicodeUTF8));
        actionText_Segment->setText(QApplication::translate("SpimView", "Text Segment", 0, QApplication::UnicodeUTF8));
        actionData_Segment->setText(QApplication::translate("SpimView", "Data Segment", 0, QApplication::UnicodeUTF8));
        actionConsole->setText(QApplication::translate("SpimView", "Console", 0, QApplication::UnicodeUTF8));
        actionSPIM_Messages->setText(QApplication::translate("SpimView", "SPIM Messages", 0, QApplication::UnicodeUTF8));
        actionClear_Console->setText(QApplication::translate("SpimView", "Clear Console", 0, QApplication::UnicodeUTF8));
        actionToolbar->setText(QApplication::translate("SpimView", "Toolbar", 0, QApplication::UnicodeUTF8));
        actionStatus_Bar->setText(QApplication::translate("SpimView", "Status Bar", 0, QApplication::UnicodeUTF8));
        actionView_Help->setText(QApplication::translate("SpimView", "View Help", 0, QApplication::UnicodeUTF8));
        actionAbout_SPIM->setText(QApplication::translate("SpimView", "About SPIM", 0, QApplication::UnicodeUTF8));
        menu_File->setTitle(QApplication::translate("SpimView", "&File", 0, QApplication::UnicodeUTF8));
        menu_Simulator->setTitle(QApplication::translate("SpimView", "&Simulator", 0, QApplication::UnicodeUTF8));
        menu_Registers->setTitle(QApplication::translate("SpimView", "&Registers", 0, QApplication::UnicodeUTF8));
        menu_Text_Segment->setTitle(QApplication::translate("SpimView", "&Text Segment", 0, QApplication::UnicodeUTF8));
        menu_Data_Segment->setTitle(QApplication::translate("SpimView", "&Data Segment", 0, QApplication::UnicodeUTF8));
        menu_Window->setTitle(QApplication::translate("SpimView", "&Window", 0, QApplication::UnicodeUTF8));
        menu_Help->setTitle(QApplication::translate("SpimView", "&Help", 0, QApplication::UnicodeUTF8));
        IntRegDockWidget->setWindowTitle(QApplication::translate("SpimView", "Integer Registers", 0, QApplication::UnicodeUTF8));
        FPRegDockWidget->setWindowTitle(QApplication::translate("SpimView", "FP Registers", 0, QApplication::UnicodeUTF8));
        TextSegDockWidget->setWindowTitle(QApplication::translate("SpimView", "Text Segment", 0, QApplication::UnicodeUTF8));
        DataSegDockWidget->setWindowTitle(QApplication::translate("SpimView", "Data Segment", 0, QApplication::UnicodeUTF8));
        ConsoleDockWidget->setWindowTitle(QApplication::translate("SpimView", "Console", 0, QApplication::UnicodeUTF8));
        ConsoleTextEdit->setWindowTitle(QApplication::translate("SpimView", "Console", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SpimView: public Ui_SpimView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SPIMVIEW_H
