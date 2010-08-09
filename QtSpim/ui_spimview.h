/********************************************************************************
** Form generated from reading UI file 'spimview.ui'
**
** Created: Sun Aug 8 21:08:37 2010
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

QT_BEGIN_NAMESPACE

class Ui_SpimView
{
public:
    QAction *action_File_Load;
    QAction *action_File_SaveLog;
    QAction *action_File_Exit;
    QAction *action_Sim_ClearRegisters;
    QAction *action_Sim_Reinitialize;
    QAction *action_File_Reload;
    QAction *action_Sim_Run;
    QAction *action_Sim_SingleStep;
    QAction *action_Sim_MultipleStep;
    QAction *action_Sim_SetBreakpoint;
    QAction *action_Sim_ListBreakpoints;
    QAction *action_Sim_SetMemoryLocation;
    QAction *action_Sim_DisplaySymbols;
    QAction *action_Sim_Settings;
    QAction *action_Reg_DisplayBinary;
    QAction *action_Reg_DisplayOctal;
    QAction *action_Reg_DisplayHex;
    QAction *action_Reg_DisplayDecimal;
    QAction *action_Reg_DisplayChar;
    QAction *action_Text_DisplayUserText;
    QAction *action_Text_DisplayKernelText;
    QAction *action_Text_NarrowRange;
    QAction *action_Text_DisplayComments;
    QAction *action_Text_DisplayInstructionValue;
    QAction *action_Data_DisplayUserData;
    QAction *action_Data_DisplayUserStack;
    QAction *action_Data_DisplayKernelData;
    QAction *action_Data_NarrowDisplay;
    QAction *action_Data_DisplayBinary;
    QAction *action_Data_DisplayOctal;
    QAction *action_Data_DisplayHex;
    QAction *action_Data_DisplayDecimal;
    QAction *actionString;
    QAction *action_Win_IntRegisters;
    QAction *action_Win_FPRegisters;
    QAction *action_Win_TextSegment;
    QAction *action_Win_Data_Segment;
    QAction *action_Win_Console;
    QAction *action_Win_Messages;
    QAction *action_Win_ClearConsole;
    QAction *action_Win_Toolbar;
    QAction *actionStatus_Bar;
    QAction *action_Help_ViewHelp;
    QAction *action_Help_AboutSPIM;
    QTextEdit *centralWidget;
    QMenuBar *menuBar;
    QMenu *menu_File;
    QMenu *menu_Simulator;
    QMenu *menu_Registers;
    QMenu *menu_Text_Segment;
    QMenu *menu_Data_Segment;
    QMenu *menu_Window;
    QMenu *menu_Help;
    QToolBar *main_Win_ToolBar;
    QStatusBar *statusBar;
    QDockWidget *IntRegDockWidget;
    QTextEdit *IntRegTextEdit;
    QDockWidget *FPRegDockWidget;
    QTextEdit *FPRegTextEdit;
    QDockWidget *TextSegDockWidget;
    QTextEdit *TextSegmentTextEdit;
    QDockWidget *DataSegDockWidget;
    QTextEdit *DataSegTextEdit;

    void setupUi(QMainWindow *SpimView)
    {
        if (SpimView->objectName().isEmpty())
            SpimView->setObjectName(QString::fromUtf8("SpimView"));
        SpimView->resize(1024, 768);
        SpimView->setDockOptions(QMainWindow::AnimatedDocks|QMainWindow::ForceTabbedDocks|QMainWindow::VerticalTabs);
        action_File_Load = new QAction(SpimView);
        action_File_Load->setObjectName(QString::fromUtf8("action_File_Load"));
        action_File_SaveLog = new QAction(SpimView);
        action_File_SaveLog->setObjectName(QString::fromUtf8("action_File_SaveLog"));
        action_File_Exit = new QAction(SpimView);
        action_File_Exit->setObjectName(QString::fromUtf8("action_File_Exit"));
        action_Sim_ClearRegisters = new QAction(SpimView);
        action_Sim_ClearRegisters->setObjectName(QString::fromUtf8("action_Sim_ClearRegisters"));
        action_Sim_Reinitialize = new QAction(SpimView);
        action_Sim_Reinitialize->setObjectName(QString::fromUtf8("action_Sim_Reinitialize"));
        action_File_Reload = new QAction(SpimView);
        action_File_Reload->setObjectName(QString::fromUtf8("action_File_Reload"));
        action_Sim_Run = new QAction(SpimView);
        action_Sim_Run->setObjectName(QString::fromUtf8("action_Sim_Run"));
        action_Sim_SingleStep = new QAction(SpimView);
        action_Sim_SingleStep->setObjectName(QString::fromUtf8("action_Sim_SingleStep"));
        action_Sim_MultipleStep = new QAction(SpimView);
        action_Sim_MultipleStep->setObjectName(QString::fromUtf8("action_Sim_MultipleStep"));
        action_Sim_SetBreakpoint = new QAction(SpimView);
        action_Sim_SetBreakpoint->setObjectName(QString::fromUtf8("action_Sim_SetBreakpoint"));
        action_Sim_ListBreakpoints = new QAction(SpimView);
        action_Sim_ListBreakpoints->setObjectName(QString::fromUtf8("action_Sim_ListBreakpoints"));
        action_Sim_SetMemoryLocation = new QAction(SpimView);
        action_Sim_SetMemoryLocation->setObjectName(QString::fromUtf8("action_Sim_SetMemoryLocation"));
        action_Sim_DisplaySymbols = new QAction(SpimView);
        action_Sim_DisplaySymbols->setObjectName(QString::fromUtf8("action_Sim_DisplaySymbols"));
        action_Sim_Settings = new QAction(SpimView);
        action_Sim_Settings->setObjectName(QString::fromUtf8("action_Sim_Settings"));
        action_Reg_DisplayBinary = new QAction(SpimView);
        action_Reg_DisplayBinary->setObjectName(QString::fromUtf8("action_Reg_DisplayBinary"));
        action_Reg_DisplayBinary->setCheckable(true);
        action_Reg_DisplayOctal = new QAction(SpimView);
        action_Reg_DisplayOctal->setObjectName(QString::fromUtf8("action_Reg_DisplayOctal"));
        action_Reg_DisplayOctal->setCheckable(true);
        action_Reg_DisplayHex = new QAction(SpimView);
        action_Reg_DisplayHex->setObjectName(QString::fromUtf8("action_Reg_DisplayHex"));
        action_Reg_DisplayHex->setCheckable(true);
        action_Reg_DisplayHex->setChecked(true);
        action_Reg_DisplayDecimal = new QAction(SpimView);
        action_Reg_DisplayDecimal->setObjectName(QString::fromUtf8("action_Reg_DisplayDecimal"));
        action_Reg_DisplayDecimal->setCheckable(true);
        action_Reg_DisplayChar = new QAction(SpimView);
        action_Reg_DisplayChar->setObjectName(QString::fromUtf8("action_Reg_DisplayChar"));
        action_Reg_DisplayChar->setCheckable(true);
        action_Text_DisplayUserText = new QAction(SpimView);
        action_Text_DisplayUserText->setObjectName(QString::fromUtf8("action_Text_DisplayUserText"));
        action_Text_DisplayUserText->setCheckable(true);
        action_Text_DisplayUserText->setChecked(true);
        action_Text_DisplayKernelText = new QAction(SpimView);
        action_Text_DisplayKernelText->setObjectName(QString::fromUtf8("action_Text_DisplayKernelText"));
        action_Text_DisplayKernelText->setCheckable(true);
        action_Text_DisplayKernelText->setChecked(true);
        action_Text_NarrowRange = new QAction(SpimView);
        action_Text_NarrowRange->setObjectName(QString::fromUtf8("action_Text_NarrowRange"));
        action_Text_DisplayComments = new QAction(SpimView);
        action_Text_DisplayComments->setObjectName(QString::fromUtf8("action_Text_DisplayComments"));
        action_Text_DisplayComments->setCheckable(true);
        action_Text_DisplayComments->setChecked(true);
        action_Text_DisplayInstructionValue = new QAction(SpimView);
        action_Text_DisplayInstructionValue->setObjectName(QString::fromUtf8("action_Text_DisplayInstructionValue"));
        action_Text_DisplayInstructionValue->setCheckable(true);
        action_Text_DisplayInstructionValue->setChecked(true);
        action_Data_DisplayUserData = new QAction(SpimView);
        action_Data_DisplayUserData->setObjectName(QString::fromUtf8("action_Data_DisplayUserData"));
        action_Data_DisplayUserData->setCheckable(true);
        action_Data_DisplayUserData->setChecked(true);
        action_Data_DisplayUserStack = new QAction(SpimView);
        action_Data_DisplayUserStack->setObjectName(QString::fromUtf8("action_Data_DisplayUserStack"));
        action_Data_DisplayUserStack->setCheckable(true);
        action_Data_DisplayUserStack->setChecked(true);
        action_Data_DisplayKernelData = new QAction(SpimView);
        action_Data_DisplayKernelData->setObjectName(QString::fromUtf8("action_Data_DisplayKernelData"));
        action_Data_DisplayKernelData->setCheckable(true);
        action_Data_DisplayKernelData->setChecked(true);
        action_Data_NarrowDisplay = new QAction(SpimView);
        action_Data_NarrowDisplay->setObjectName(QString::fromUtf8("action_Data_NarrowDisplay"));
        action_Data_DisplayBinary = new QAction(SpimView);
        action_Data_DisplayBinary->setObjectName(QString::fromUtf8("action_Data_DisplayBinary"));
        action_Data_DisplayBinary->setCheckable(true);
        action_Data_DisplayOctal = new QAction(SpimView);
        action_Data_DisplayOctal->setObjectName(QString::fromUtf8("action_Data_DisplayOctal"));
        action_Data_DisplayOctal->setCheckable(true);
        action_Data_DisplayHex = new QAction(SpimView);
        action_Data_DisplayHex->setObjectName(QString::fromUtf8("action_Data_DisplayHex"));
        action_Data_DisplayHex->setCheckable(true);
        action_Data_DisplayHex->setChecked(true);
        action_Data_DisplayDecimal = new QAction(SpimView);
        action_Data_DisplayDecimal->setObjectName(QString::fromUtf8("action_Data_DisplayDecimal"));
        action_Data_DisplayDecimal->setCheckable(true);
        actionString = new QAction(SpimView);
        actionString->setObjectName(QString::fromUtf8("actionString"));
        actionString->setCheckable(true);
        action_Win_IntRegisters = new QAction(SpimView);
        action_Win_IntRegisters->setObjectName(QString::fromUtf8("action_Win_IntRegisters"));
        action_Win_IntRegisters->setCheckable(true);
        action_Win_IntRegisters->setChecked(true);
        action_Win_FPRegisters = new QAction(SpimView);
        action_Win_FPRegisters->setObjectName(QString::fromUtf8("action_Win_FPRegisters"));
        action_Win_FPRegisters->setCheckable(true);
        action_Win_FPRegisters->setChecked(true);
        action_Win_TextSegment = new QAction(SpimView);
        action_Win_TextSegment->setObjectName(QString::fromUtf8("action_Win_TextSegment"));
        action_Win_TextSegment->setCheckable(true);
        action_Win_TextSegment->setChecked(true);
        action_Win_Data_Segment = new QAction(SpimView);
        action_Win_Data_Segment->setObjectName(QString::fromUtf8("action_Win_Data_Segment"));
        action_Win_Data_Segment->setCheckable(true);
        action_Win_Data_Segment->setChecked(true);
        action_Win_Console = new QAction(SpimView);
        action_Win_Console->setObjectName(QString::fromUtf8("action_Win_Console"));
        action_Win_Console->setCheckable(true);
        action_Win_Console->setChecked(true);
        action_Win_Messages = new QAction(SpimView);
        action_Win_Messages->setObjectName(QString::fromUtf8("action_Win_Messages"));
        action_Win_Messages->setCheckable(true);
        action_Win_Messages->setChecked(true);
        action_Win_ClearConsole = new QAction(SpimView);
        action_Win_ClearConsole->setObjectName(QString::fromUtf8("action_Win_ClearConsole"));
        action_Win_Toolbar = new QAction(SpimView);
        action_Win_Toolbar->setObjectName(QString::fromUtf8("action_Win_Toolbar"));
        action_Win_Toolbar->setCheckable(true);
        action_Win_Toolbar->setChecked(true);
        actionStatus_Bar = new QAction(SpimView);
        actionStatus_Bar->setObjectName(QString::fromUtf8("actionStatus_Bar"));
        action_Help_ViewHelp = new QAction(SpimView);
        action_Help_ViewHelp->setObjectName(QString::fromUtf8("action_Help_ViewHelp"));
        action_Help_AboutSPIM = new QAction(SpimView);
        action_Help_AboutSPIM->setObjectName(QString::fromUtf8("action_Help_AboutSPIM"));
        centralWidget = new QTextEdit(SpimView);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        centralWidget->setUndoRedoEnabled(false);
        centralWidget->setReadOnly(true);
        SpimView->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(SpimView);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1024, 21));
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
        main_Win_ToolBar = new QToolBar(SpimView);
        main_Win_ToolBar->setObjectName(QString::fromUtf8("main_Win_ToolBar"));
        SpimView->addToolBar(Qt::TopToolBarArea, main_Win_ToolBar);
        statusBar = new QStatusBar(SpimView);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        SpimView->setStatusBar(statusBar);
        IntRegDockWidget = new QDockWidget(SpimView);
        IntRegDockWidget->setObjectName(QString::fromUtf8("IntRegDockWidget"));
        IntRegDockWidget->setAllowedAreas(Qt::TopDockWidgetArea);
        IntRegTextEdit = new QTextEdit();
        IntRegTextEdit->setObjectName(QString::fromUtf8("IntRegTextEdit"));
        IntRegTextEdit->setMinimumSize(QSize(250, 600));
        IntRegTextEdit->setUndoRedoEnabled(false);
        IntRegTextEdit->setReadOnly(true);
        IntRegDockWidget->setWidget(IntRegTextEdit);
        SpimView->addDockWidget(static_cast<Qt::DockWidgetArea>(4), IntRegDockWidget);
        FPRegDockWidget = new QDockWidget(SpimView);
        FPRegDockWidget->setObjectName(QString::fromUtf8("FPRegDockWidget"));
        FPRegDockWidget->setAllowedAreas(Qt::TopDockWidgetArea);
        FPRegTextEdit = new QTextEdit();
        FPRegTextEdit->setObjectName(QString::fromUtf8("FPRegTextEdit"));
        FPRegTextEdit->setUndoRedoEnabled(false);
        FPRegTextEdit->setReadOnly(true);
        FPRegDockWidget->setWidget(FPRegTextEdit);
        SpimView->addDockWidget(static_cast<Qt::DockWidgetArea>(4), FPRegDockWidget);
        TextSegDockWidget = new QDockWidget(SpimView);
        TextSegDockWidget->setObjectName(QString::fromUtf8("TextSegDockWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(TextSegDockWidget->sizePolicy().hasHeightForWidth());
        TextSegDockWidget->setSizePolicy(sizePolicy);
        TextSegDockWidget->setAllowedAreas(Qt::BottomDockWidgetArea|Qt::TopDockWidgetArea);
        TextSegmentTextEdit = new QTextEdit();
        TextSegmentTextEdit->setObjectName(QString::fromUtf8("TextSegmentTextEdit"));
        TextSegmentTextEdit->setMinimumSize(QSize(700, 600));
        TextSegmentTextEdit->setUndoRedoEnabled(false);
        TextSegmentTextEdit->setReadOnly(true);
        TextSegDockWidget->setWidget(TextSegmentTextEdit);
        SpimView->addDockWidget(static_cast<Qt::DockWidgetArea>(4), TextSegDockWidget);
        DataSegDockWidget = new QDockWidget(SpimView);
        DataSegDockWidget->setObjectName(QString::fromUtf8("DataSegDockWidget"));
        DataSegDockWidget->setAllowedAreas(Qt::TopDockWidgetArea);
        DataSegTextEdit = new QTextEdit();
        DataSegTextEdit->setObjectName(QString::fromUtf8("DataSegTextEdit"));
        DataSegTextEdit->setUndoRedoEnabled(false);
        DataSegTextEdit->setReadOnly(true);
        DataSegDockWidget->setWidget(DataSegTextEdit);
        SpimView->addDockWidget(static_cast<Qt::DockWidgetArea>(4), DataSegDockWidget);

        menuBar->addAction(menu_File->menuAction());
        menuBar->addAction(menu_Simulator->menuAction());
        menuBar->addAction(menu_Registers->menuAction());
        menuBar->addAction(menu_Text_Segment->menuAction());
        menuBar->addAction(menu_Data_Segment->menuAction());
        menuBar->addAction(menu_Window->menuAction());
        menuBar->addAction(menu_Help->menuAction());
        menu_File->addAction(action_File_Load);
        menu_File->addAction(action_File_Reload);
        menu_File->addSeparator();
        menu_File->addAction(action_File_SaveLog);
        menu_File->addSeparator();
        menu_File->addAction(action_File_Exit);
        menu_Simulator->addAction(action_Sim_ClearRegisters);
        menu_Simulator->addAction(action_Sim_Reinitialize);
        menu_Simulator->addSeparator();
        menu_Simulator->addAction(action_Sim_Run);
        menu_Simulator->addAction(action_Sim_SingleStep);
        menu_Simulator->addAction(action_Sim_MultipleStep);
        menu_Simulator->addSeparator();
        menu_Simulator->addAction(action_Sim_SetBreakpoint);
        menu_Simulator->addAction(action_Sim_ListBreakpoints);
        menu_Simulator->addSeparator();
        menu_Simulator->addAction(action_Sim_SetMemoryLocation);
        menu_Simulator->addSeparator();
        menu_Simulator->addAction(action_Sim_DisplaySymbols);
        menu_Simulator->addSeparator();
        menu_Simulator->addAction(action_Sim_Settings);
        menu_Registers->addAction(action_Reg_DisplayBinary);
        menu_Registers->addAction(action_Reg_DisplayOctal);
        menu_Registers->addAction(action_Reg_DisplayHex);
        menu_Registers->addAction(action_Reg_DisplayDecimal);
        menu_Registers->addAction(action_Reg_DisplayChar);
        menu_Text_Segment->addAction(action_Text_DisplayUserText);
        menu_Text_Segment->addAction(action_Text_DisplayKernelText);
        menu_Text_Segment->addSeparator();
        menu_Text_Segment->addAction(action_Text_NarrowRange);
        menu_Text_Segment->addAction(action_Text_DisplayComments);
        menu_Text_Segment->addAction(action_Text_DisplayInstructionValue);
        menu_Data_Segment->addAction(action_Data_DisplayUserData);
        menu_Data_Segment->addAction(action_Data_DisplayUserStack);
        menu_Data_Segment->addAction(action_Data_DisplayKernelData);
        menu_Data_Segment->addSeparator();
        menu_Data_Segment->addSeparator();
        menu_Data_Segment->addAction(action_Data_DisplayBinary);
        menu_Data_Segment->addAction(action_Data_DisplayOctal);
        menu_Data_Segment->addAction(action_Data_DisplayHex);
        menu_Data_Segment->addAction(action_Data_DisplayDecimal);
        menu_Window->addAction(action_Win_IntRegisters);
        menu_Window->addAction(action_Win_FPRegisters);
        menu_Window->addAction(action_Win_TextSegment);
        menu_Window->addAction(action_Win_Data_Segment);
        menu_Window->addAction(action_Win_Console);
        menu_Window->addAction(action_Win_Messages);
        menu_Window->addSeparator();
        menu_Window->addAction(action_Win_ClearConsole);
        menu_Window->addAction(action_Win_Toolbar);
        menu_Help->addAction(action_Help_ViewHelp);
        menu_Help->addAction(action_Help_AboutSPIM);

        retranslateUi(SpimView);

        QMetaObject::connectSlotsByName(SpimView);
    } // setupUi

    void retranslateUi(QMainWindow *SpimView)
    {
        SpimView->setWindowTitle(QApplication::translate("SpimView", "SpimView", 0, QApplication::UnicodeUTF8));
        action_File_Load->setText(QApplication::translate("SpimView", "&Load File", 0, QApplication::UnicodeUTF8));
        action_File_SaveLog->setText(QApplication::translate("SpimView", "&Save Log File", 0, QApplication::UnicodeUTF8));
        action_File_Exit->setText(QApplication::translate("SpimView", "&Exit", 0, QApplication::UnicodeUTF8));
        action_Sim_ClearRegisters->setText(QApplication::translate("SpimView", "&Clear Registers", 0, QApplication::UnicodeUTF8));
        action_Sim_Reinitialize->setText(QApplication::translate("SpimView", "Re&initialize Simulator", 0, QApplication::UnicodeUTF8));
        action_File_Reload->setText(QApplication::translate("SpimView", "Re&intialize and Load File", 0, QApplication::UnicodeUTF8));
        action_Sim_Run->setText(QApplication::translate("SpimView", "&Run", 0, QApplication::UnicodeUTF8));
        action_Sim_SingleStep->setText(QApplication::translate("SpimView", "&Single Step", 0, QApplication::UnicodeUTF8));
        action_Sim_MultipleStep->setText(QApplication::translate("SpimView", "&Multiple Step", 0, QApplication::UnicodeUTF8));
        action_Sim_SetBreakpoint->setText(QApplication::translate("SpimView", "Set&Breakpoint", 0, QApplication::UnicodeUTF8));
        action_Sim_ListBreakpoints->setText(QApplication::translate("SpimView", "&List Breakpoints", 0, QApplication::UnicodeUTF8));
        action_Sim_SetMemoryLocation->setText(QApplication::translate("SpimView", "Change &Memory Location", 0, QApplication::UnicodeUTF8));
        action_Sim_DisplaySymbols->setText(QApplication::translate("SpimView", "&Display Symbols", 0, QApplication::UnicodeUTF8));
        action_Sim_Settings->setText(QApplication::translate("SpimView", "Settings", 0, QApplication::UnicodeUTF8));
        action_Reg_DisplayBinary->setText(QApplication::translate("SpimView", "Binary", 0, QApplication::UnicodeUTF8));
        action_Reg_DisplayOctal->setText(QApplication::translate("SpimView", "Octal", 0, QApplication::UnicodeUTF8));
        action_Reg_DisplayHex->setText(QApplication::translate("SpimView", "Hex", 0, QApplication::UnicodeUTF8));
        action_Reg_DisplayDecimal->setText(QApplication::translate("SpimView", "Decimal", 0, QApplication::UnicodeUTF8));
        action_Reg_DisplayChar->setText(QApplication::translate("SpimView", "Char", 0, QApplication::UnicodeUTF8));
        action_Text_DisplayUserText->setText(QApplication::translate("SpimView", "User Text", 0, QApplication::UnicodeUTF8));
        action_Text_DisplayKernelText->setText(QApplication::translate("SpimView", "Kernel Text", 0, QApplication::UnicodeUTF8));
        action_Text_NarrowRange->setText(QApplication::translate("SpimView", "Narrow Display", 0, QApplication::UnicodeUTF8));
        action_Text_DisplayComments->setText(QApplication::translate("SpimView", "Comments", 0, QApplication::UnicodeUTF8));
        action_Text_DisplayInstructionValue->setText(QApplication::translate("SpimView", "Instruction Value", 0, QApplication::UnicodeUTF8));
        action_Data_DisplayUserData->setText(QApplication::translate("SpimView", "User Data", 0, QApplication::UnicodeUTF8));
        action_Data_DisplayUserStack->setText(QApplication::translate("SpimView", "User Stack", 0, QApplication::UnicodeUTF8));
        action_Data_DisplayKernelData->setText(QApplication::translate("SpimView", "Kernel Data", 0, QApplication::UnicodeUTF8));
        action_Data_NarrowDisplay->setText(QApplication::translate("SpimView", "Narrow Display", 0, QApplication::UnicodeUTF8));
        action_Data_DisplayBinary->setText(QApplication::translate("SpimView", "Binary", 0, QApplication::UnicodeUTF8));
        action_Data_DisplayOctal->setText(QApplication::translate("SpimView", "Octal", 0, QApplication::UnicodeUTF8));
        action_Data_DisplayHex->setText(QApplication::translate("SpimView", "Hex", 0, QApplication::UnicodeUTF8));
        action_Data_DisplayDecimal->setText(QApplication::translate("SpimView", "Decimal", 0, QApplication::UnicodeUTF8));
        actionString->setText(QApplication::translate("SpimView", "String", 0, QApplication::UnicodeUTF8));
        action_Win_IntRegisters->setText(QApplication::translate("SpimView", "Integer Registers", 0, QApplication::UnicodeUTF8));
        action_Win_FPRegisters->setText(QApplication::translate("SpimView", "FP Registers", 0, QApplication::UnicodeUTF8));
        action_Win_TextSegment->setText(QApplication::translate("SpimView", "Text Segment", 0, QApplication::UnicodeUTF8));
        action_Win_Data_Segment->setText(QApplication::translate("SpimView", "Data Segment", 0, QApplication::UnicodeUTF8));
        action_Win_Console->setText(QApplication::translate("SpimView", "Console", 0, QApplication::UnicodeUTF8));
        action_Win_Messages->setText(QApplication::translate("SpimView", "SPIM Messages", 0, QApplication::UnicodeUTF8));
        action_Win_ClearConsole->setText(QApplication::translate("SpimView", "Clear Console", 0, QApplication::UnicodeUTF8));
        action_Win_Toolbar->setText(QApplication::translate("SpimView", "Toolbar", 0, QApplication::UnicodeUTF8));
        actionStatus_Bar->setText(QApplication::translate("SpimView", "Status Bar", 0, QApplication::UnicodeUTF8));
        action_Help_ViewHelp->setText(QApplication::translate("SpimView", "View Help", 0, QApplication::UnicodeUTF8));
        action_Help_AboutSPIM->setText(QApplication::translate("SpimView", "About SPIM", 0, QApplication::UnicodeUTF8));
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
    } // retranslateUi

};

namespace Ui {
    class SpimView: public Ui_SpimView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SPIMVIEW_H
