#include "spimview.h"
#include "ui_savelogfile.h"
#include "ui_printwindows.h"
#include "ui_runparams.h"

#include <QStringBuilder>
#define QT_USE_FAST_CONCATENATION
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QPrinter>
#include <QPrintDialog>


//
// Menu functions
//



// File menu
//

void SpimView::file_LoadFile()
{
    QString defaultFile(st_recentFiles[0]);
    if (sender() != 0)
    {
        defaultFile = ((QAction*)sender())->text(); // File name is text associated with action
    }

    QString file = QFileDialog::getOpenFileName(this,
                                                "Open Assembly Code",
                                                defaultFile,
                                                "Assembly (*.s *.asm);;Text files (*.txt)");
    if (!file.isNull())
    {
        read_assembly_file(file.toLocal8Bit().data());
        st_recentFiles.removeAll(file);
        st_recentFiles.prepend(file);
        rebuildRecentFilesMenu();

        DisplayTextSegments();
        DisplayDataSegments();
    }
}


void SpimView::file_ReloadFile()
{
    sim_ReinitializeSimulator();
    file_LoadFile();
}


static QString
pickFormat(QTextEdit* te, bool toHTML)
{
    if (toHTML)
    {
        return te->toHtml();
    }
    else
    {
        return te->toPlainText();
    }
}


void SpimView::file_SaveLogFile()
{
    QDialog d;
    Ui::SaveLogFileDialog slf;
    slf.setupUi(&d);

    // If user clicks on browser button, open a file browser and grab the file name.
    //
    QFileDialog browser(0, "Open Log File", "", "Text files (*.txt);; HTML files (*.html *.htm);;All (*)");
    QObject::connect(slf.BrowsePushButton, SIGNAL(clicked()), &browser, SLOT(exec()));
    QObject::connect(&browser, SIGNAL(fileSelected(QString)), slf.SaveLineEdit, SLOT(setText(QString)));


    if (d.exec() == QDialog::Accepted)
    {
        if (!slf.SaveLineEdit->text().isNull())
        {
            QFile file(slf.SaveLineEdit->text());
            file.open(QIODevice::WriteOnly | QIODevice::Truncate);
            QTextStream outFile(&file);

            bool toHtml = slf.HTMLRadioButton->isChecked();

            if (slf.RegsCheckBox->isChecked())
            {
                outFile << pickFormat(ui->IntRegDockWidget->findChild<QTextEdit *>("IntRegTextEdit"), toHtml);
                outFile << "\n\n";
            }
            if (slf.TextCheckBox->isChecked())
            {
                outFile << pickFormat(ui->TextSegDockWidget->findChild<QTextEdit *>("TextSegmentTextEdit"), toHtml);
                outFile << "\n\n";
            }
            if (slf.DataCheckBox->isChecked())
            {
                outFile << pickFormat(ui->DataSegDockWidget->findChild<QTextEdit *>("DataSegTextEdit"), toHtml);
                outFile << "\n\n";
            }
#if 0                           // FIXME
            if (slf.ConsoleCheckBox->isChecked())
            {
                outFile << pickFormat(ui->IntRegDockWidget->findChild<QTextEdit *>("IntRegTextEdit"), toHtml);
            }
#endif
        }
    }
}


void SpimView::file_Print()
{
    QDialog d;
    Ui::PrintWindowsDialog pwd;
    pwd.setupUi(&d);

    if (d.exec() == QDialog::Accepted)
    {
        QPrinter printer;
        QPrintDialog printDialog(&printer, this);
        printDialog.setWindowTitle("Print Windows");

        if (printDialog.exec() == QDialog::Accepted)
        {

            if (pwd.RegsCheckBox->isChecked())
            {
                ui->IntRegDockWidget->findChild<QTextEdit *>("IntRegTextEdit")->print(&printer);
            }
            if (pwd.TextCheckBox->isChecked())
            {
                ui->TextSegDockWidget->findChild<QTextEdit *>("TextSegmentTextEdit")->print(&printer);
            }
            if (pwd.DataCheckBox->isChecked())
            {
                ui->DataSegDockWidget->findChild<QTextEdit *>("DataSegTextEdit")->print(&printer);
            }
#if 0                           // FIXME
            if (pwd.ConsoleCheckBox->isChecked())
            {
                ui->IntRegDockWidget->findChild<QTextEdit *>("IntRegTextEdit")->print(&printer);
            }
#endif
        }
    }
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
    initialize_registers();
}


void SpimView::sim_ReinitializeSimulator()
{
    write_output(message_out, "<hr>Memory and registers cleared");
    initialize_world(ExceptionFileOrNull());
    initStack();
    write_startup_message();

    add_breakpoint(0x400010);

    DisplayTextSegments();
    DisplayDataSegments();

    CaptureIntRegisters();
    CaptureSFPRegisters();
    CaptureDFPRegisters();

    DisplayIntRegisters();
    DisplayFPRegisters();
}


void SpimView::sim_SetRunParameters()
{
    QDialog d;
    Ui::SetRunParametersDialog srp;
    srp.setupUi(&d);

    // Default values:
    //
    srp.addressLineEdit->setText(QString("0x") + formatAddress(st_startAddress));
    srp.argsLineEdit->setText(st_commandLine);

    if (d.exec() == QDialog::Accepted)
    {
        if (!srp.addressLineEdit->text().isNull())
        {
            bool ok;
            st_startAddress = srp.addressLineEdit->text().toInt(&ok, 0);
        }
        if (!srp.argsLineEdit->text().isNull())
        {
            st_commandLine = srp.argsLineEdit->text();
        }
    }
}


void SpimView::sim_Run()
{
  if (st_startAddress == 0)
    {
      st_startAddress = starting_address ();
    }
    initStack();
    executeProgram(st_startAddress, DEFAULT_RUN_STEPS, false, false);
}


void SpimView::sim_SingleStep()
{
    executeProgram(starting_address(), 1, false, false);
}


void SpimView::initStack()
{
    // Prepend file name to arg list
    //
    initialize_stack((st_recentFiles[0] + " " + st_commandLine).toLocal8Bit().data());
}


void SpimView::executeProgram(mem_addr pc, int steps, bool display, bool contBkpt)
{
    if (pc != 0)
    {
        bool breakpointEncountered = run_program(pc, steps, display, contBkpt);
        highlightInstruction(PC);
        DisplayIntRegisters();
        DisplayFPRegisters();
        DisplayDataSegments();
        
        if (breakpointEncountered)
        {
            QMessageBox msgBox(QMessageBox::Information,
                               "Execution Stopped",
                               "Execution stopped due to breakpoint",
                       QMessageBox::Close);
            msgBox.exec();
        }
    }
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
    st_intRegBase = 2;
    setCheckedRegBase(st_intRegBase);
    DisplayIntRegisters();
}


void SpimView::reg_DisplayOctal()
{
    st_intRegBase = 8;
    setCheckedRegBase(st_intRegBase);
    DisplayIntRegisters();
}


void SpimView::reg_DisplayDecimal()
{
    st_intRegBase = 10;
    setCheckedRegBase(st_intRegBase);
    DisplayIntRegisters();
}


void SpimView::reg_DisplayHex()
{
    st_intRegBase = 16;
    setCheckedRegBase(st_intRegBase);
    DisplayIntRegisters();
}


int SpimView::setCheckedRegBase(int base)
{
    return setBaseInternal(base,
                           ui->action_Reg_DisplayBinary,
                           ui->action_Reg_DisplayOctal,
                           ui->action_Reg_DisplayDecimal,
                           ui->action_Reg_DisplayHex);
}


int SpimView::setBaseInternal(int base, QAction* actionBinary, QAction* actionOctal, QAction* actionDecimal, QAction* actionHex)
{
    actionBinary->setChecked(false);
    actionOctal->setChecked(false);
    actionDecimal->setChecked(false);
    actionHex->setChecked(false);

    switch (base)
    {
    case 2: 
        actionBinary->setChecked(true);
        return base;

    case 8: 
        actionOctal->setChecked(true);
        return base;

    case 10: 
        actionDecimal->setChecked(true);
        return base;

    case 16: 
        actionHex->setChecked(true);
        return base;

    default:
        actionHex->setChecked(true);
        return 16;
    }
}


// Text menu
//

void SpimView::text_DisplayUserText()
{
    st_showUserTextSegment = ui->action_Text_DisplayUserText->isChecked();
    DisplayTextSegments();
}


void SpimView::text_DisplayKernelText()
{
    st_showKernelTextSegment = ui->action_Text_DisplayKernelText->isChecked();
    DisplayTextSegments();
}


void SpimView::text_NarrowRange()
{
    //FIXME!!
}


void SpimView::text_DisplayComments()
{
    st_showTextComments = ui->action_Text_DisplayComments->isChecked();
    DisplayTextSegments();
}


void SpimView::text_DisplayInstructionValue()
{
    st_showTextDisassembly = ui->action_Text_DisplayInstructionValue->isChecked();
    DisplayTextSegments();
}



// Data menu
//

void SpimView::data_DisplayUserData()
{
    st_showUserDataSegment = ui->action_Data_DisplayUserData->isChecked();
    DisplayDataSegments();
}


void SpimView::data_DisplayUserStack()
{
    st_showUserStackSegment = ui->action_Data_DisplayUserStack->isChecked();
    DisplayDataSegments();
}


void SpimView::data_DisplayKernelData()
{
    st_showKernelDataSegment = ui->action_Data_DisplayKernelData->isChecked();
    DisplayDataSegments();
}


void SpimView::data_NarrowDisplay()
{
    //FIXME!!
}


void SpimView::data_DisplayBinary()
{
    st_dataSegmentBase = 2;
    setCheckedDataSegmentBase(st_dataSegmentBase);
    DisplayDataSegments();
}


void SpimView::data_DisplayOctal()
{
    st_dataSegmentBase = 8;
    setCheckedDataSegmentBase(st_dataSegmentBase);
    DisplayDataSegments();
}


void SpimView::data_DisplayDecimal()
{
    st_dataSegmentBase = 10;
    setCheckedDataSegmentBase(st_dataSegmentBase);
    DisplayDataSegments();
}


void SpimView::data_DisplayHex()
{
    st_dataSegmentBase = 16;
    setCheckedDataSegmentBase(st_dataSegmentBase);
    DisplayDataSegments();
}


int SpimView::setCheckedDataSegmentBase(int base)
{
    return setBaseInternal(base,
                           ui->action_Data_DisplayBinary,
                           ui->action_Data_DisplayOctal,
                           ui->action_Data_DisplayDecimal,
                           ui->action_Data_DisplayHex);
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
