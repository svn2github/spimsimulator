#include "spimview.h"
#include "ui_savelogfile.h"
#include "ui_printwindows.h"
#include "ui_runparams.h"
#include "ui_settings.h"
#include "spim_settings.h"

#include <QStringBuilder>
#define QT_USE_FAST_CONCATENATION
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QPrinter>
#include <QPrintDialog>
#include <QFontDialog>
#include <QColorDialog>


//
// Menu functions
//



// File menu
//

void SpimView::file_LoadFile()
{
    QString file;
    if (((QAction*)sender())->objectName() != "action_File_Load"
        && ((QAction*)sender())->objectName() != "action_File_Reload")
    {
        file = ((QAction*)sender())->text(); // Recent file menu entry's names are file names
    }
    else
    {
        file = QFileDialog::getOpenFileName(this,
                                            "Open Assembly Code",
                                            st_recentFiles[0],
                                            "Assembly (*.s *.asm);;Text files (*.txt)");
    }
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


void SpimView::rebuildRecentFilesMenu()
{
    ui->menuRecent_Files->clear();
    int i;
    for (i = 0; i < st_recentFilesLength; i++)
    {
        QAction* action = ui->menuRecent_Files->addAction(st_recentFiles[i]);
        QObject::connect(action, SIGNAL(triggered(bool)), this, SLOT(file_LoadFile()));
    }
}


void SpimView::file_SaveLogFile()
{
    QDialog d;
    Ui::SaveLogFileDialog slf;
    slf.setupUi(&d);

    QFileDialog browser(0, "Open Log File", "", "Text files (*.txt);; HTML files (*.html *.htm);;All (*)");
    QObject::connect(slf.saveFileToolButton, SIGNAL(clicked()), &browser, SLOT(exec()));
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
                outFile << pickFormat(ui->DataSegDockWidget->findChild<QTextEdit *>("DataSegmentTextEdit"), toHtml);
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
                ui->DataSegDockWidget->findChild<QTextEdit *>("DataSegmentTextEdit")->print(&printer);
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
#if 0
    QMessageBox msgBox(QMessageBox::Question, "Exit", "Exit?", QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    if (msgBox.exec())
    {
        this->SaveStateAndExit(0);
    }
#endif
    this->SaveStateAndExit(0);
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
    SpimConsole->clear();
    initStack();
    write_startup_message();

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


void SpimView::sim_DisplaySymbols()
{
    WriteOutput("<br>");
    print_symbols();
}


void SpimView::sim_Settings()
{
    QDialog d;
    Ui::SpimSettingDialog sd;
    sd.setupUi(&d);

    sd.bareMachineCheckBox->setChecked(bare_machine);
    sd.pseudoInstCheckBox->setChecked(accept_pseudo_insts);
    sd.delayedBranchCheckBox->setChecked(delayed_branches);
    sd.delayedLoadCheckBox->setChecked(delayed_loads);
    sd.mappedIOCheckBox->setChecked(mapped_io);

    QObject::connect(sd.simplePushButton, SIGNAL(clicked()), sd.bareMachineCheckBox, SLOT(unset()));
    QObject::connect(sd.simplePushButton, SIGNAL(clicked()), sd.pseudoInstCheckBox, SLOT(set()));
    QObject::connect(sd.simplePushButton, SIGNAL(clicked()), sd.delayedBranchCheckBox, SLOT(unset()));
    QObject::connect(sd.simplePushButton, SIGNAL(clicked()), sd.delayedLoadCheckBox, SLOT(unset()));
    QObject::connect(sd.barePushButton, SIGNAL(clicked()), sd.bareMachineCheckBox, SLOT(set()));
    QObject::connect(sd.barePushButton, SIGNAL(clicked()), sd.pseudoInstCheckBox, SLOT(unset()));
    QObject::connect(sd.barePushButton, SIGNAL(clicked()), sd.delayedBranchCheckBox, SLOT(set()));
    QObject::connect(sd.barePushButton, SIGNAL(clicked()), sd.delayedLoadCheckBox, SLOT(set()));

    sd.loadExceptionHandlerCheckBox->setChecked(st_loadExceptionHandler);
    sd.exceptionHandlerLineEdit->setText(st_ExceptionHandlerFileName);
    QFileDialog exceptionFileDialog(0,
                                    "Open Exception File",
                                    st_ExceptionHandlerFileName,
                                    "Assembly (*.s *.asm);;Text files (*.txt)");
    QObject::connect(sd.exceptionHandlerToolButton, SIGNAL(clicked()), &exceptionFileDialog, SLOT(exec()));
    QObject::connect(&exceptionFileDialog, SIGNAL(fileSelected(QString)),
                     sd.exceptionHandlerLineEdit, SLOT(setText(QString)));

    sd.recentFilesLineEdit->setText(QString::number(st_recentFilesLength, 10));

    sd.regWinFontLineEdit->setText(st_regWinFont.family());
    QFontDialog* regWinFontDialog = new QFontDialog(st_regWinFont);
    QObject::connect(sd.regWinFontToolButton, SIGNAL(clicked()), regWinFontDialog, SLOT(exec()));
    QObject::connect(regWinFontDialog, SIGNAL(fontSelected(QFont)), &sd, SLOT(setRegWinFont(QFont)));

    sd.regWinFontColorLineEdit->setText(st_regWinFontColor.name());
    QColorDialog* regWinColorDialog = new QColorDialog(st_regWinFontColor);
    QObject::connect(sd.regWinFontColorToolButton, SIGNAL(clicked()), regWinColorDialog, SLOT(exec()));
    QObject::connect(regWinColorDialog, SIGNAL(colorSelected(QColor)), &sd, SLOT(setRegWinColor(QColor)));

    sd.regWinBackgroundLineEdit->setText(st_regWinBackgroundColor.name());
    QColorDialog* regWinBackgroundDialog = new QColorDialog(st_regWinBackgroundColor);
    QObject::connect(sd.regWinBackgroundToolButton, SIGNAL(clicked()), regWinBackgroundDialog, SLOT(exec()));
    QObject::connect(regWinBackgroundDialog, SIGNAL(colorSelected(QColor)), &sd, SLOT(setRegWinBackground(QColor)));

    sd.textWinFontLineEdit->setText(st_textWinFont.family());
    QFontDialog* textWinFontDialog = new QFontDialog(st_textWinFont);
    QObject::connect(sd.textWinFontToolButton, SIGNAL(clicked()), textWinFontDialog, SLOT(exec()));
    QObject::connect(textWinFontDialog, SIGNAL(fontSelected(QFont)), &sd, SLOT(setTextWinFont(QFont)));

    sd.textWinFontColorLineEdit->setText(st_textWinFontColor.name());
    QColorDialog* textWinColorDialog = new QColorDialog(st_textWinFontColor);
    QObject::connect(sd.textWinFontColorToolButton, SIGNAL(clicked()), textWinColorDialog, SLOT(exec()));
    QObject::connect(textWinColorDialog, SIGNAL(colorSelected(QColor)), &sd, SLOT(setTextWinColor(QColor)));

    sd.textWinBackgroundLineEdit->setText(st_textWinBackgroundColor.name());
    QColorDialog* textWinBackgroundDialog = new QColorDialog(st_textWinBackgroundColor);
    QObject::connect(sd.textWinBackgroundToolButton, SIGNAL(clicked()), textWinBackgroundDialog, SLOT(exec()));
    QObject::connect(textWinBackgroundDialog, SIGNAL(colorSelected(QColor)), &sd, SLOT(setTextWinBackground(QColor)));

    if (d.exec() == QDialog::Accepted)
    {
        bare_machine = sd.bareMachineCheckBox->isChecked();
        accept_pseudo_insts = sd.pseudoInstCheckBox->isChecked();
        delayed_branches = sd.delayedBranchCheckBox->isChecked();
        delayed_loads = sd.delayedLoadCheckBox->isChecked();
        mapped_io = sd.mappedIOCheckBox->isChecked();

        st_loadExceptionHandler = sd.loadExceptionHandlerCheckBox->isChecked();
        st_ExceptionHandlerFileName = sd.exceptionHandlerLineEdit->text();

        st_recentFilesLength = sd.recentFilesLineEdit->text().toInt();
        if (st_recentFilesLength <= 0 || st_recentFilesLength > 20)
        {
            st_recentFilesLength = 4;
        }

        if (sd.regWinFont != NULL)
        {
            st_regWinFont = *sd.regWinFont;
        }
        if (sd.regWinColor != NULL)
        {
            st_regWinFontColor = *sd.regWinColor;
        }
        if (sd.regWinBackground != NULL)
        {
            st_regWinBackgroundColor = *sd.regWinBackground;
        }

        if (sd.textWinFont != NULL)
        {
            st_textWinFont = *sd.textWinFont;
        }
        if (sd.textWinColor != NULL)
        {
            st_textWinFontColor = *sd.textWinColor;
        }
        if (sd.textWinBackground != NULL)
        {
            st_textWinBackgroundColor = *sd.textWinBackground;
        }

        DisplayIntRegisters();
        DisplayFPRegisters();
        DisplayTextSegments();
        DisplayDataSegments();
    }
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

void winUpDown(QObject* sender, QWidget* widget)
{
    QAction* act = (QAction*)sender;
    if (act->isChecked())
    {
        widget->show();
    }
    else
    {
        widget->hide();
    }
}


void SpimView::win_IntRegisters()
{
    winUpDown(sender(), ui->IntRegDockWidget);
}


void SpimView::win_FPRegisters()
{
    winUpDown(sender(), ui->FPRegDockWidget);
}


void SpimView::win_TextSegment()
{
    winUpDown(sender(), ui->TextSegDockWidget);
}


void SpimView::win_DataSegment()
{
    winUpDown(sender(), ui->DataSegDockWidget);
}


void SpimView::win_Console()
{
    winUpDown(sender(), SpimConsole);
}


void SpimView::win_Tile()
{
    ui->IntRegDockWidget->show();
    ui->action_Win_IntRegisters->setChecked(true);
    ui->FPRegDockWidget->show();
    ui->action_Win_FPRegisters->setChecked(true);
    ui->TextSegDockWidget->show();
    ui->action_Win_TextSegment->setChecked(true);
    ui->DataSegDockWidget->show();
    ui->action_Win_DataSegment->setChecked(true);

    ui->IntRegDockWidget->setFloating(false);
    ui->FPRegDockWidget->setFloating(false);
    tabifyDockWidget(ui->FPRegDockWidget, ui->IntRegDockWidget);
    ui->TextSegDockWidget->setFloating(false);
    ui->DataSegDockWidget->setFloating(false);
    tabifyDockWidget(ui->DataSegDockWidget, ui->TextSegDockWidget);
}


// Help menu
//

void SpimView::help_ViewHelp()
{
}


void SpimView::help_AboutSPIM()
{
}
