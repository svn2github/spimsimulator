#include "spimview.h"
#include "ui_spimview.h"

#include <QStringBuilder>
#define QT_USE_FAST_CONCATENATION
#include <QMessageBox>


SpimView::SpimView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SpimView),
    settings("Larus-Stone", "QtSpim")
{
    // Open windows
    //
    ui->setupUi(this);

    // Set style parameters for docking widgets
    //
    setCorner(Qt::TopLeftCorner, Qt::LeftDockWidgetArea);
    setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
    setCorner(Qt::TopRightCorner, Qt::RightDockWidgetArea);
    setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);
    tabifyDockWidget(ui->FPRegDockWidget, ui->IntRegDockWidget);
    tabifyDockWidget(ui->DataSegDockWidget, ui->TextSegDockWidget);


    // Wire up the menu commands
    //
    wireMenuCommands();


    // Restore program settings and window positions
    //
    readSettings();
}


SpimView::~SpimView()
{
    writeSettings();
    delete ui;
}


void SpimView::wireMenuCommands()
{
    QObject::connect(ui->action_File_Load, SIGNAL(triggered(bool)), this, SLOT(file_LoadFile()));
    QObject::connect(ui->action_File_Reload, SIGNAL(triggered(bool)), this, SLOT(file_ReloadFile()));
    QObject::connect(ui->action_File_SaveLog, SIGNAL(triggered(bool)), this, SLOT(file_SaveLogFile()));
    QObject::connect(ui->action_File_Exit, SIGNAL(triggered(bool)), this, SLOT(file_Exit()));

    QObject::connect(ui->action_Sim_ClearRegisters, SIGNAL(triggered(bool)), this, SLOT(sim_ClearRegisters()));
    QObject::connect(ui->action_Sim_Reinitialize, SIGNAL(triggered(bool)), this, SLOT(sim_ReinitializeSimulator()));
    QObject::connect(ui->action_Sim_Run, SIGNAL(triggered(bool)), this, SLOT(sim_Run()));
    QObject::connect(ui->action_Sim_SingleStep, SIGNAL(triggered(bool)), this, SLOT(sim_SingleStep()));
    QObject::connect(ui->action_Sim_MultipleStep, SIGNAL(triggered(bool)), this, SLOT(sim_MultipleStep()));
    QObject::connect(ui->action_Sim_SetBreakpoint, SIGNAL(triggered(bool)), this, SLOT(sim_SetBreakpoint()));
    QObject::connect(ui->action_Sim_ListBreakpoints, SIGNAL(triggered(bool)), this, SLOT(sim_ListBreakpoints()));
    QObject::connect(ui->action_Sim_SetMemoryLocation, SIGNAL(triggered(bool)), this, SLOT(sim_SetMemoryLocation()));
    QObject::connect(ui->action_Sim_DisplaySymbols, SIGNAL(triggered(bool)), this, SLOT(sim_DisplaySymbols()));
    QObject::connect(ui->action_Sim_Settings, SIGNAL(triggered(bool)), this, SLOT(sim_Settings()));

    QObject::connect(ui->action_Reg_DisplayBinary, SIGNAL(triggered(bool)), this, SLOT(reg_DisplayBinary()));
    QObject::connect(ui->action_Reg_DisplayOctal, SIGNAL(triggered(bool)), this, SLOT(reg_DisplayOctal()));
    QObject::connect(ui->action_Reg_DisplayHex, SIGNAL(triggered(bool)), this, SLOT(reg_DisplayHex()));
    QObject::connect(ui->action_Reg_DisplayDecimal, SIGNAL(triggered(bool)), this, SLOT(reg_DisplayDecimal()));
    QObject::connect(ui->action_Reg_DisplayChar, SIGNAL(triggered(bool)), this, SLOT(reg_DisplayChar()));

    QObject::connect(ui->action_Text_DisplayUserText, SIGNAL(triggered(bool)), this, SLOT(text_DisplayUserText()));
    QObject::connect(ui->action_Text_DisplayKernelText, SIGNAL(triggered(bool)), this, SLOT(text_DisplayKernelText()));
    QObject::connect(ui->action_Text_NarrowRange, SIGNAL(triggered(bool)), this, SLOT(text_NarrowRange()));
    QObject::connect(ui->action_Text_DisplayComments, SIGNAL(triggered(bool)), this, SLOT(text_DisplayComments()));
    QObject::connect(ui->action_Text_DisplayInstructionValue, SIGNAL(triggered(bool)), this, SLOT(text_DisplayInstructionValue()));

    QObject::connect(ui->action_Data_DisplayUserData, SIGNAL(triggered(bool)), this, SLOT(data_DisplayUserData()));
    QObject::connect(ui->action_Data_DisplayUserStack, SIGNAL(triggered(bool)), this, SLOT(data_DisplayUserStack()));
    QObject::connect(ui->action_Data_DisplayKernelData, SIGNAL(triggered(bool)), this, SLOT(data_DisplayKernelData()));
    QObject::connect(ui->action_Data_NarrowDisplay, SIGNAL(triggered(bool)), this, SLOT(data_NarrowDisplay()));
    QObject::connect(ui->action_Data_DisplayBinary, SIGNAL(triggered(bool)), this, SLOT(data_DisplayBinary()));
    QObject::connect(ui->action_Data_DisplayOctal, SIGNAL(triggered(bool)), this, SLOT(data_DisplayOctal()));
    QObject::connect(ui->action_Data_DisplayHex, SIGNAL(triggered(bool)), this, SLOT(data_DisplayHex()));
    QObject::connect(ui->action_Data_DisplayDecimal, SIGNAL(triggered(bool)), this, SLOT(data_DisplayDecimal()));

    QObject::connect(ui->action_Win_IntRegisters, SIGNAL(triggered(bool)), this, SLOT(win_IntRegisters()));
    QObject::connect(ui->action_Win_FPRegisters, SIGNAL(triggered(bool)), this, SLOT(win_FPRegisters()));
    QObject::connect(ui->action_Win_TextSegment, SIGNAL(triggered(bool)), this, SLOT(win_TextSegment()));
    QObject::connect(ui->action_Win_Data_Segment, SIGNAL(triggered(bool)), this, SLOT(win_DataSegment()));
    QObject::connect(ui->action_Win_Console, SIGNAL(triggered(bool)), this, SLOT(win_Console()));
    QObject::connect(ui->action_Win_Messages, SIGNAL(triggered(bool)), this, SLOT(win_Messages()));
    QObject::connect(ui->action_Win_ClearConsole, SIGNAL(triggered(bool)), this, SLOT(win_ClearConsole()));

    QObject::connect(ui->action_Help_ViewHelp, SIGNAL(triggered(bool)), this, SLOT(help_ViewHelp()));
    QObject::connect(ui->action_Help_AboutSPIM, SIGNAL(triggered(bool)), this, SLOT(help_AboutSPIM()));
}


//
// Restore program settings and window positions
//

void SpimView::readSettings()
{
    settings.beginGroup("Mainin");
    restoreGeometry(settings.value("Geometry").toByteArray());
    restoreState(settings.value("WindowState").toByteArray());
    settings.endGroup();

    settings.beginGroup("RegWin");
    st_colorChangedRegisters = settings.value("ColorChangedRegs", true).toBool();
    st_changedRegisterColor = settings.value("ChangedRegColor", "red").toString();
    st_intRegBase = settings.value("IntRegisterBase", 16).toInt();

    ui->IntRegDockWidget->restoreGeometry(settings.value("Geometry").toByteArray());
    settings.endGroup();

    settings.beginGroup("TextWin");
    st_showUserTextSegment = settings.value("ShowUserTextSeg", true).toBool();
    st_showKernelTextSegment = settings.value("ShowKernelTextSeg", true).toBool();
    st_showTextComments =  settings.value("ShowTextComments", true).toBool();
    st_showTextDisassembly =  settings.value("ShowInstDisassembly", true).toBool();

    ui->TextSegDockWidget->restoreGeometry(settings.value("Geometry").toByteArray());
    settings.endGroup();

    settings.beginGroup("DataWin");
    st_showUserDataSegment = settings.value("ShowUserDataSeg", true).toBool();
    st_showUserStackSegment = settings.value("ShowUserStackSeg", true).toBool();
    st_showKernelDataSegment = settings.value("ShowKernelDataSeg", true).toBool();
    st_dataSegmentBase = settings.value("DataSegmentBase", 16).toInt();

    ui->DataSegDockWidget->restoreGeometry(settings.value("Geometry").toByteArray());
    settings.endGroup();

    settings.beginGroup("FileMenu");
    st_programFileName = settings.value("ProgramFileName", "").toString();
    st_commandLine = settings.value("CommandLine", "").toString();
    settings.endGroup();

    settings.beginGroup("Spim");
    bare_machine = settings.value("BareMachine", 0).toInt();
    accept_pseudo_insts = settings.value("AcceptPseudoInsts", 1).toInt();
    delayed_branches = settings.value("DelayedBranches", 0).toInt();
    quiet = settings.value("Quiet", 0).toInt();
    st_loadExceptionHandler = settings.value("LoadExceptionHandler", true).toBool();
    st_ExceptionHandlerFileName = settings.value("ExceptionHandlerFileName", "../CPU/exceptions.s").toString();
    settings.endGroup();
}


void SpimView::writeSettings()
{
    settings.beginGroup("MainWin");
    settings.setValue("Geometry", saveGeometry());
    settings.setValue("WindowState", saveState());
    settings.endGroup();

    settings.beginGroup("RegWin");
    settings.setValue("ColorChangedRegs", st_colorChangedRegisters);
    settings.setValue("ChangedRegColor", st_changedRegisterColor);
    settings.setValue("IntRegisterBase", st_intRegBase);

    settings.setValue("Geometry", ui->IntRegDockWidget->saveGeometry());
    settings.endGroup();

    settings.beginGroup("TextWin");
    settings.setValue("ShowUserTextSeg", st_showUserTextSegment);
    settings.setValue("ShowKernelTextSeg", st_showKernelTextSegment);
    settings.setValue("ShowTextComments", st_showTextComments);
    settings.setValue("ShowInstDisassembly", st_showTextDisassembly);

    settings.setValue("Geometry", ui->TextSegDockWidget->saveGeometry());
    settings.endGroup();

    settings.beginGroup("DataWin");
    settings.setValue("ShowUserDataSeg", st_showUserDataSegment);
    settings.setValue("ShowUserStackSeg", st_showUserStackSegment);
    settings.setValue("ShowKernelDataSeg", st_showKernelDataSegment);
    settings.setValue("DataSegmentBase", st_dataSegmentBase);

    settings.setValue("Geometry", ui->DataSegDockWidget->saveGeometry());
    settings.endGroup();

    settings.beginGroup("FileMenu");
    settings.setValue("ProgramFileName", st_programFileName);
    settings.setValue("CommandLine", st_commandLine);
    settings.endGroup();

    settings.beginGroup("Spim");
    settings.setValue("BareMachine", bare_machine);
    settings.setValue("AcceptPseudoInsts", accept_pseudo_insts);
    settings.setValue("DelayedBranches", delayed_branches);
    settings.setValue("Quiet", quiet);
    settings.setValue("LoadExceptionHandler", st_loadExceptionHandler);
    settings.setValue("ExceptionHandlerFileName", st_ExceptionHandlerFileName);
    settings.endGroup();

    settings.sync();
}


QString SpimView::windowFormattingStart()
{
    return "<span style='font-size:10pt;font-family:courier;color:black'>";
}


QString SpimView::windowFormattingEnd()
{
    return "</span>";
}


char* SpimView::ExceptionFileOrNull()
{
    QByteArray ba = st_ExceptionHandlerFileName.toLocal8Bit(); // char* is deallocated when QByteArray is
    char* ef = ba.data();                                      // So, make a copy of string while BA is
    int len = strlen(ef) + 1;                                  // still alive -- tricky
    char* nef = new char[len];
    strncpy(nef, ef, len);

    return st_loadExceptionHandler ? nef : NULL;
}


void SpimView::SaveStateAndExit(int val)
{
    writeSettings();
    exit(val);
}


QString SpimView::WriteOutput(QString message)
{
    if (message.endsWith("\n"))
    {
        message.chop(1);        // Appending adds a <br>, so avoid doubling last newline
    }
    message.replace("\n", "<br>");
    message.replace(" ", "&nbsp;");

    Window->ui->centralWidget->append(QString("<span>") + message + QString("</span>"));

    return message;
}


void SpimView::Error(QString message, bool fatal)
{
    message = WriteOutput(message);

    QMessageBox msgBox(fatal ? QMessageBox::Critical : QMessageBox::Warning,
                       "Error",
                       message,
                       QMessageBox::Close);
    msgBox.exec();

    if (fatal)
    {
        SaveStateAndExit(1);
    }
}
