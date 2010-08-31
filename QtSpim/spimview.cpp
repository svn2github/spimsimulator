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
    SpimConsole = new Console(0);


    // Set style parameters for docking widgets
    //
    setCorner(Qt::TopLeftCorner, Qt::LeftDockWidgetArea);
    setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
    setCorner(Qt::TopRightCorner, Qt::RightDockWidgetArea);
    setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);
    tabifyDockWidget(ui->FPRegDockWidget, ui->IntRegDockWidget);
    tabifyDockWidget(ui->DataSegDockWidget, ui->TextSegDockWidget);


    // Wire up the menu and context menu commands
    //
    wireCommands();


    // Restore program settings and window positions
    //
    readSettings();


    // Create a console
    //
    SpimConsole->show();
    ui->action_Win_Console->setChecked(true);
}


SpimView::~SpimView()
{
    writeSettings();
    SpimConsole->close();
    delete SpimConsole;
    delete ui;
}


void SpimView::wireCommands()
{
    QObject::connect(ui->action_File_Load, SIGNAL(triggered(bool)), this, SLOT(file_LoadFile()));
    QObject::connect(ui->action_File_Reload, SIGNAL(triggered(bool)), this, SLOT(file_ReloadFile()));
    QObject::connect(ui->action_File_SaveLog, SIGNAL(triggered(bool)), this, SLOT(file_SaveLogFile()));
    QObject::connect(ui->action_File_Print, SIGNAL(triggered(bool)), this, SLOT(file_Print()));
    QObject::connect(ui->action_File_Exit, SIGNAL(triggered(bool)), this, SLOT(file_Exit()));

    QObject::connect(ui->action_Sim_ClearRegisters, SIGNAL(triggered(bool)), this, SLOT(sim_ClearRegisters()));
    QObject::connect(ui->action_Sim_Reinitialize, SIGNAL(triggered(bool)), this, SLOT(sim_ReinitializeSimulator()));
    QObject::connect(ui->action_Sim_SetRunParameters, SIGNAL(triggered(bool)), this, SLOT(sim_SetRunParameters()));
    QObject::connect(ui->action_Sim_Run, SIGNAL(triggered(bool)), this, SLOT(sim_Run()));
    QObject::connect(ui->action_Sim_SingleStep, SIGNAL(triggered(bool)), this, SLOT(sim_SingleStep()));
    QObject::connect(ui->action_Sim_DisplaySymbols, SIGNAL(triggered(bool)), this, SLOT(sim_DisplaySymbols()));
    QObject::connect(ui->action_Sim_Settings, SIGNAL(triggered(bool)), this, SLOT(sim_Settings()));

    QObject::connect(ui->action_Reg_DisplayBinary, SIGNAL(triggered(bool)), this, SLOT(reg_DisplayBinary()));
    QObject::connect(ui->action_Reg_DisplayOctal, SIGNAL(triggered(bool)), this, SLOT(reg_DisplayOctal()));
    QObject::connect(ui->action_Reg_DisplayHex, SIGNAL(triggered(bool)), this, SLOT(reg_DisplayHex()));
    QObject::connect(ui->action_Reg_DisplayDecimal, SIGNAL(triggered(bool)), this, SLOT(reg_DisplayDecimal()));

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
    QObject::connect(ui->action_Win_DataSegment, SIGNAL(triggered(bool)), this, SLOT(win_DataSegment()));
    QObject::connect(ui->action_Win_Console, SIGNAL(triggered(bool)), this, SLOT(win_Console()));
    QObject::connect(ui->action_Win_Tile, SIGNAL(triggered(bool)), this, SLOT(win_Tile()));

    QObject::connect(ui->action_Help_ViewHelp, SIGNAL(triggered(bool)), this, SLOT(help_ViewHelp()));
    QObject::connect(ui->action_Help_AboutSPIM, SIGNAL(triggered(bool)), this, SLOT(help_AboutSPIM()));

    QObject::connect(ui->TextSegmentTextEdit->action_Context_SetBreakpoint, SIGNAL(triggered(bool)),
                     ui->TextSegmentTextEdit, SLOT(setBreakpoint()));
    QObject::connect(ui->TextSegmentTextEdit->action_Context_ClearBreakpoint, SIGNAL(triggered(bool)),
                     ui->TextSegmentTextEdit, SLOT(clearBreakpoint()));


    QObject::connect(ui->DataSegmentTextEdit->action_Context_ChangeValue, SIGNAL(triggered(bool)),
                     ui->DataSegmentTextEdit, SLOT(changeValue()));
}


QString SpimView::windowFormattingStart(QFont font, QColor fontColor, QColor backgroundColor)
{
    return QString("<span style='font-family:" + font.family()
                   + "; font-size:" + QString::number(font.pointSize(), 10)
                   + "pt; color:" + fontColor.name()
                   + ";background-color:" + backgroundColor.name()
                   +"'>");
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
    Window->ui->centralWidget->ensureCursorVisible();

    return message;
}


void SpimView::Error(QString message, bool fatal)
{
    WriteOutput(message);

    if (fatal)
    {
        QMessageBox::critical(0, "Error", message, QMessageBox::Ok | QMessageBox::Abort, QMessageBox::Ok);
        SaveStateAndExit(1);
    }
    else
    {
        QMessageBox::StandardButton b = QMessageBox::information(0,
                                                                 "Error",
                                                                 message,
                                                                 QMessageBox::Ok | QMessageBox::Abort,
                                                                 QMessageBox::Ok);
        if (b == QMessageBox::Abort)
        {
            force_break = 1;
        }
    }
}
