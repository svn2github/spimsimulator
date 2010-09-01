#include "spimview.h"
#include "ui_spimview.h"

//
// Restore program settings and window positions
//

void SpimView::readSettings()
{
    settings.beginGroup("MainWin");
    bool b1 = restoreGeometry(settings.value("Geometry").toByteArray());
    bool b2 = restoreState(settings.value("WindowState").toByteArray(), 1);
    settings.endGroup();

    settings.beginGroup("RegWin");
    st_colorChangedRegisters = settings.value("ColorChangedRegs", true).toBool();
    st_changedRegisterColor = settings.value("ChangedRegColor", "red").toString();
    st_intRegBase = settings.value("IntRegisterBase", 16).toInt();
    st_intRegBase = setCheckedRegBase(st_intRegBase);

    st_regWinFont = settings.value("Font", QFont("Courier", 10)).value<QFont>();
    st_regWinFontColor = settings.value("FontColor", QColor("black")).value<QColor>();
    st_regWinBackgroundColor = settings.value("BackgroundColor", QColor("white")).value<QColor>();

    //    ui->IntRegDockWidget->restoreGeometry(settings.value("Int Geometry").toByteArray());
    //    ui->FPRegDockWidget->restoreGeometry(settings.value("FP Geometry").toByteArray());

    ui->action_Win_IntRegisters->setChecked(!ui->IntRegDockWidget->isHidden());
    ui->action_Win_FPRegisters->setChecked(!ui->FPRegDockWidget->isHidden());
    settings.endGroup();


    settings.beginGroup("TextWin");
    st_showUserTextSegment = settings.value("ShowUserTextSeg", true).toBool();
    ui->action_Text_DisplayUserText->setChecked(st_showUserTextSegment);
    st_showKernelTextSegment = settings.value("ShowKernelTextSeg", true).toBool();
    ui->action_Text_DisplayKernelText->setChecked(st_showKernelTextSegment);
    st_showTextComments =  settings.value("ShowTextComments", true).toBool();
    ui->action_Text_DisplayComments->setChecked(st_showTextComments);
    st_showTextDisassembly =  settings.value("ShowInstDisassembly", true).toBool();
    ui->action_Text_DisplayInstructionValue->setChecked(st_showTextDisassembly);

    st_textWinFont = settings.value("Font", QFont("Courier", 10)).value<QFont>();
    st_textWinFontColor = settings.value("FontColor", QColor("black")).value<QColor>();
    st_textWinBackgroundColor = settings.value("BackgroundColor", QColor("white")).value<QColor>();

    //    ui->TextSegDockWidget->restoreGeometry(settings.value("Geometry").toByteArray());
    ui->action_Win_TextSegment->setChecked(!ui->TextSegDockWidget->isHidden());
    settings.endGroup();


    settings.beginGroup("DataWin");
    st_showUserDataSegment = settings.value("ShowUserDataSeg", true).toBool();
    ui->action_Data_DisplayUserData->setChecked(st_showUserDataSegment);
    st_showUserStackSegment = settings.value("ShowUserStackSeg", true).toBool();
    ui->action_Data_DisplayUserStack->setChecked(st_showUserStackSegment);
    st_showKernelDataSegment = settings.value("ShowKernelDataSeg", true).toBool();
    ui->action_Data_DisplayKernelData->setChecked(st_showKernelDataSegment);
    st_dataSegmentBase = settings.value("DataSegmentBase", 16).toInt();
    st_dataSegmentBase = setCheckedDataSegmentBase(st_dataSegmentBase);

    //    ui->DataSegDockWidget->restoreGeometry(settings.value("Geometry").toByteArray());
    ui->action_Win_DataSegment->setChecked(!ui->DataSegDockWidget->isHidden());
    settings.endGroup();


    settings.beginGroup("FileMenu");
    st_recentFilesLength = settings.value("RecentFilesLength", 4).toInt();
    st_recentFiles.clear();
    int i;
    for (i = 0; i < st_recentFilesLength; i++)
    {
        QString file = settings.value("RecentFile" + QString(i), "").toString();
        st_recentFiles.append(file);
    }
    rebuildRecentFilesMenu();
    settings.endGroup();


    settings.beginGroup("Spim");
    bare_machine = settings.value("BareMachine", 0).toInt();
    accept_pseudo_insts = settings.value("AcceptPseudoInsts", 1).toInt();
    delayed_branches = settings.value("DelayedBranches", 0).toInt();
    delayed_loads = settings.value("DelayedLoads", 0).toInt();
    mapped_io = settings.value("MappedIO", 0).toInt();

    st_loadExceptionHandler = settings.value("LoadExceptionHandler", true).toBool();
    st_ExceptionHandlerFileName = settings.value("ExceptionHandlerFileName", "../CPU/exceptions.s").toString();
    st_startAddress = settings.value("StartingAddress", starting_address()).toInt();
    st_commandLine = settings.value("CommandLineArguments", "").toString();
    settings.endGroup();
}


void SpimView::writeSettings()
{
    settings.beginGroup("MainWin");
    settings.setValue("Geometry", saveGeometry());
    settings.setValue("WindowState", saveState(1));
    settings.endGroup();


    settings.beginGroup("RegWin");
    settings.setValue("ColorChangedRegs", st_colorChangedRegisters);
    settings.setValue("ChangedRegColor", st_changedRegisterColor);
    settings.setValue("IntRegisterBase", st_intRegBase);

    settings.setValue("Font", st_regWinFont);
    settings.setValue("FontColor", st_regWinFontColor);
    settings.setValue("BackgroundColor", st_regWinBackgroundColor);

    settings.setValue("Int Geometry", ui->IntRegDockWidget->saveGeometry());
    settings.setValue("FP Geometry", ui->FPRegDockWidget->saveGeometry());
    settings.endGroup();


    settings.beginGroup("TextWin");
    settings.setValue("ShowUserTextSeg", st_showUserTextSegment);
    settings.setValue("ShowKernelTextSeg", st_showKernelTextSegment);
    settings.setValue("ShowTextComments", st_showTextComments);
    settings.setValue("ShowInstDisassembly", st_showTextDisassembly);

    settings.setValue("Font", st_textWinFont);
    settings.setValue("FontColor", st_textWinFontColor);
    settings.setValue("BackgroundColor", st_textWinBackgroundColor);

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
    settings.setValue("RecentFilesLength", st_recentFilesLength);
    int i;
    for (i = 0; i < st_recentFilesLength; i++)
    {
        if (i < st_recentFiles.length())
        {
            settings.setValue("RecentFile" + QString(i), st_recentFiles[i]);
        }
        else
        {
            settings.setValue("RecentFile" + QString(i), "");
        }
    }
    settings.endGroup();


    settings.beginGroup("Spim");
    settings.setValue("BareMachine", bare_machine);
    settings.setValue("AcceptPseudoInsts", accept_pseudo_insts);
    settings.setValue("DelayedBranches", delayed_branches);
    settings.setValue("DelayedLoads", delayed_loads);
    settings.setValue("MappedIO", mapped_io);

    settings.setValue("LoadExceptionHandler", st_loadExceptionHandler);
    settings.setValue("ExceptionHandlerFileName", st_ExceptionHandlerFileName);
    settings.setValue("StartingAddress", st_startAddress);
    settings.setValue("CommandLine", st_commandLine);
    settings.endGroup();

    settings.sync();
}
