#include "spimview.h"
#include "ui_spimview.h"

#include <QStringBuilder>
#define QT_USE_FAST_CONCATENATION
#include <QMessageBox>
#include <QFileDialog>



//
// Menu functions
//



// File menu
//

void SpimView::file_OpenFile()
{
  QString file = QFileDialog::getOpenFileName(this,
                                              tr("Open Assembly Code"),
                                              st_programFileName,
                                              tr("Assembly (*.s *.asm);;Text files (*.txt)"));
  if (!file.isNull())
    {
      st_programFileName = file;
      st_commandLine = st_programFileName;
      read_assembly_file(st_programFileName.toLocal8Bit().data());

      displayTextSegments();
      displayDataSegments();
    }
}


void SpimView::file_ReloadFile()
{
}


void SpimView::file_CloseFile()
{
}


void SpimView::file_SaveLogFile()
{
}


void SpimView::file_Exit()
{
    QMessageBox msgBox(QMessageBox::Question, "Exit", "Exit?", QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    if (msgBox.exec())
    {
        this->SaveStateAndExit(0);
    }
}



// Simulator menu
//

void SpimView::sim_ClearRegisters()
{
}


void SpimView::sim_ReinitializeSimulator()
{
}


void SpimView::sim_Run()
{
}


void SpimView::sim_SingleStep()
{
}


void SpimView::sim_MultipleStep()
{
}


void SpimView::sim_SetBreakpoint()
{
}


void SpimView::sim_ListBreakpoints()
{
}


void SpimView::sim_SetMemoryLocation()
{
}


void SpimView::sim_DisplaySymbols()
{
}


void SpimView::sim_Settings()
{
}



// Registers menu
//

void SpimView::reg_DisplayBinary()
{
}


void SpimView::reg_DisplayOctal()
{
}


void SpimView::reg_DisplayHex()
{
}


void SpimView::reg_DisplayDecimal()
{
}


void SpimView::reg_DisplayChar()
{
}



// Text menu
//

void SpimView::text_DisplayUserText()
{
}


void SpimView::text_DisplayKernelText()
{
}


void SpimView::text_NarrowRange()
{
}


void SpimView::text_DisplayComments()
{
}


void SpimView::text_DisplayInstructionValue()
{
}



// Data menu
//

void SpimView::data_DisplayUserData()
{
}


void SpimView::data_DisplayUserStack()
{
}


void SpimView::data_DisplayKernelData()
{
}


void SpimView::data_NarrowDisplay()
{
}


void SpimView::data_DisplayBinary()
{
}


void SpimView::data_DisplayOctal()
{
}


void SpimView::data_DisplayHex()
{
}


void SpimView::data_DisplayDecimal()
{
}



// Window menu
//

void SpimView::win_IntRegisters()
{
}


void SpimView::win_FPRegisters()
{
}


void SpimView::win_TextSegment()
{
}


void SpimView::win_DataSegment()
{
}


void SpimView::win_Console()
{
}


void SpimView::win_Messages()
{
}


void SpimView::win_ClearConsole()
{
}



// Help menu
//

void SpimView::help_ViewHelp()
{
}


void SpimView::help_AboutSPIM()
{
}
