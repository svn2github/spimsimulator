#include "spimview.h"
#include "ui_savelogfile.h"
#include "ui_printwindows.h"

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
  QString file = QFileDialog::getOpenFileName(this,
                                              "Open Assembly Code",
                                              st_programFileName,
                                              "Assembly (*.s *.asm);;Text files (*.txt)");
  if (!file.isNull())
    {
      st_programFileName = file;
      st_commandLine = st_programFileName;
      read_assembly_file(st_programFileName.toLocal8Bit().data());

      DisplayTextSegments();
      DisplayDataSegments();
    }
}


void SpimView::file_ReloadFile()
{
    write_output(message_out, "<hr>Memory and registers cleared");
    initialize_world(ExceptionFileOrNull());
    write_startup_message();

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
    st_intRegBase = 2;
    setCheckedReg(st_intRegBase);
    DisplayIntRegisters();
}


void SpimView::reg_DisplayOctal()
{
    st_intRegBase = 8;
    setCheckedReg(st_intRegBase);
    DisplayIntRegisters();
}


void SpimView::reg_DisplayDecimal()
{
    st_intRegBase = 10;
    setCheckedReg(st_intRegBase);
    DisplayIntRegisters();
}


void SpimView::reg_DisplayHex()
{
    st_intRegBase = 16;
    setCheckedReg(st_intRegBase);
    DisplayIntRegisters();
}


int SpimView::setCheckedReg(int base)
{
    ui->action_Reg_DisplayBinary->setChecked(false);
    ui->action_Reg_DisplayOctal->setChecked(false);
    ui->action_Reg_DisplayDecimal->setChecked(false);
    ui->action_Reg_DisplayHex->setChecked(false);

    switch (base)
    {
    case 2: 
        ui->action_Reg_DisplayBinary->setChecked(true);
        return base;

    case 8: 
        ui->action_Reg_DisplayOctal->setChecked(true);
        return base;

    case 10: 
        ui->action_Reg_DisplayDecimal->setChecked(true);
        return base;

    case 16: 
        ui->action_Reg_DisplayHex->setChecked(true);
        return base;

    default:
        ui->action_Reg_DisplayHex->setChecked(true);
        return 16;
    }
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
