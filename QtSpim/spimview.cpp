#include "spimview.h"
#include "ui_spimview.h"
#include "reg.h"

#include <QStringBuilder>
#define QT_USE_FAST_CONCATENATION

SpimView::SpimView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SpimView),
    settings("Larus-Stone", "QtSpim")
{
    initialize_world("../CPU/exceptions.s");
    //initialize_run_stack(program_argc, program_argv);

    ui->setupUi(this);
    setCorner(Qt::TopLeftCorner, Qt::LeftDockWidgetArea);
    setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
    setCorner(Qt::TopRightCorner, Qt::RightDockWidgetArea);
    setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);
    tabifyDockWidget(ui->FPRegDockWidget, ui->IntRegDockWidget);
    tabifyDockWidget(ui->DataSegDockWidget, ui->TextSegDockWidget);

    colorChangedRegisters = settings.value("RegWin/ColorChangedRegs", 1).toInt();
    changedRegisterColor = settings.value("RegWin/ChangedRegColor", "red").toString();
    intRegBase = settings.value("RegWin/IntRegisterBase", 16).toInt();

    showUserTextSegment = settings.value("TextWin/ShowUserTextSeg", 1).toInt();
    showKernelTextSegment = settings.value("TextWin/ShowKernelTextSeg", 1).toInt();
    showTextComments =  settings.value("TextWin/ShowTextComments", 1).toInt();
    showTextDisassembly =  settings.value("TextWin/ShowInstDisassembly", 1).toInt();

    showUserDataSegment = settings.value("DataWin/ShowUserDataSeg", 1).toInt();
    showUserStackSegment = settings.value("DataWin/ShowUserStackSeg", 1).toInt();
    showKernelDataSegment = settings.value("DataWin/ShowKernelDataSeg", 1).toInt();
    dataSegmentBase = settings.value("DataWin/DataSegmentBase", 16).toInt();

    captureIntRegisters();
    captureSFPRegisters();
    captureDFPRegisters();

    displayIntRegisters();
    displayFPRegisters();

    displayTextSegments();
    displayDataSegments();
}


SpimView::~SpimView()
{
    delete ui;
}


QString SpimView::windowFormattingStart()
{
    return "<span style='font-size:10pt;font-family:courier;color:black'>";
}


QString SpimView::windowFormattingEnd()
{
    return "</span>";
}
