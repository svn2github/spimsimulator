#include "spimview.h"
#include "ui_spimview.h"

#include <QStringBuilder>
#define QT_USE_FAST_CONCATENATION


//
// Integer registers window
//

void SpimView::DisplayIntRegisters()
{
    QTextEdit* te = ui->IntRegDockWidget->findChild<QTextEdit *>("IntRegTextEdit");
    QString windowContents = windowFormattingStart(st_regWinFont, st_regWinFontColor, st_regWinBackgroundColor);

    windowContents += formatSpecialIntRegister(PC, "PC", PC != oldPC);
    windowContents += formatSpecialIntRegister(CP0_EPC, "EPC", CP0_EPC != oldEPC);
    windowContents += formatSpecialIntRegister(CP0_Cause, "Cause", CP0_Cause != oldCause);
    windowContents += formatSpecialIntRegister(CP0_BadVAddr, "BadVAddr", CP0_BadVAddr != oldBadVAddr);
    windowContents += formatSpecialIntRegister(CP0_Status, "Status", CP0_Status != oldStatus);
    windowContents += "<br />";
    windowContents += formatSpecialIntRegister(HI, "HI", HI != oldHI);
    windowContents += formatSpecialIntRegister(LO, "LO", LO != oldLO);

    windowContents += "<br /><br />";

    int i;
    for (i = 0; i < 32; i++) {
        windowContents += formatIntRegister(i, R[i], int_reg_names[i], R[i] != oldR[i]);
    }
    windowContents += windowFormattingEnd();

    te->clear();
    te->setHtml(windowContents);
    ui->IntRegDockWidget->setWindowTitle(QString("Integer Registers [")
                                         + QString::number(st_intRegBase)
                                         + QString("]"));
    CaptureIntRegisters();
}


QString SpimView::formatSpecialIntRegister(int value, char* name, bool changed)
{
    return formatReg(QString("<b>") % QString(name) % nnbsp(8 - strlen(name)) % QString("</b>"),
                     formatInt(value),
                     changed);
}


QString SpimView::formatIntRegister(int regNum, int value, char* name, bool changed)
{
    return formatReg(QString("<b>R") % QString::number(regNum, 10) % (regNum < 10 ? "&nbsp;" : "")
                     % QString("&nbsp;[") % QString(name) % QString("]</b>"),
                     formatInt(value),
                     changed);
}


void SpimView::CaptureIntRegisters()
{
    int i;
    for (i = 0; i < R_LENGTH; i++)
    {
        oldR[i] = R[i];
    }
    oldPC = PC;
    oldEPC = CP0_EPC;
    oldCause = CP0_Cause;
    oldBadVAddr = CP0_BadVAddr;
    oldStatus = CP0_Status;
    oldHI = HI;
    oldLO = LO;
}



//
// Floating point registers
//
void SpimView::DisplayFPRegisters()
{
    QTextEdit* te = ui->FPRegDockWidget->findChild<QTextEdit *>("FPRegTextEdit");
    te->clear();
    te->setHtml(windowFormattingStart(st_regWinFont, st_regWinFontColor, st_regWinBackgroundColor)
                % formatSFPRegisters()
                % formatDFPRegisters()
                % windowFormattingEnd());
}


//
// Single precision floating point registers window
//

QString SpimView::formatSFPRegisters()
{
    QString windowContents = "";

    windowContents += formatSpecialSFPRegister(FIR_REG, "FIR", FIR_REG != oldFIR);
    windowContents += formatSpecialSFPRegister(FCSR_REG, "FCSR", FCSR_REG != oldFCSR);
    windowContents += formatSpecialSFPRegister(FCCR_REG, "FCCR", FCCR_REG != oldFCCR);
    windowContents += formatSpecialSFPRegister(FEXR_REG, "FEXR", FEXR_REG != oldFEXR);

    windowContents += "<br /><center><b>Single Precision</b></center>";

    int i;
    for (i = 0; i < FGR_LENGTH; i++) {
        windowContents += formatSFPRegister(i, FPR_S(i), FPR_S(i) != oldFPR_S[i]);
    }

    CaptureSFPRegisters();

    return windowContents;
}


void SpimView::CaptureSFPRegisters()
{
    int i;
    for (i = 0; i < FGR_LENGTH; i++)
    {
        oldFPR_S[i] = FPR_S(i);
    }
    oldFIR = FIR_REG;
    oldFCSR = FCSR_REG;
    oldFCCR = FCCR_REG;
    oldFEXR = FEXR_REG;
}


QString SpimView::formatSpecialSFPRegister(int value, char* name, bool changed)
{
    return formatReg(QString("<b>") % QString(name) % nnbsp(7 - strlen(name)) % QString("</b>"),
                     formatInt(value),
                     changed);
}


QString SpimView::formatSFPRegister(int regNum, float value, bool changed)
{
    return formatReg(QString("<b>FP") % QString::number(regNum, 10) % (regNum < 10 ? "&nbsp;</b>" : "</b>"),
                     QString::number(value, 'g', 6).leftJustified(10, '0'),
                     changed);
}


//
// Double precision floating point registers window
//

QString SpimView::formatDFPRegisters()
{
    QString windowContents = QString("<br /><center><b>Double Precision</b></center>");

    int i;
    for (i = 0; i < FPR_LENGTH; i += 2) {
        windowContents += formatDFPRegister(2 * i, FPR_D(i), FPR_D(i) != oldFPR_D[i]);
    }

    CaptureDFPRegisters();

    return windowContents;
}


void SpimView::CaptureDFPRegisters()
{
    int i;
    for (i = 0; i < FPR_LENGTH; i += 2)
    {
        oldFPR_D[i] = FPR_D(i);
    }
}


QString SpimView::formatDFPRegister(int regNum, double value, bool changed)
{
    return formatReg(QString("<b>FP") % QString::number(regNum, 10) % (regNum < 10 ? "&nbsp;</b>" : "</b>"),
                     QString::number(value, 'g', 6),
                     changed);
}


//
// Common register functionality
//

QString SpimView::formatInt(int value)
{
    return formatWord(value, st_intRegBase);
}


QString SpimView::formatReg(QString name, QString value, bool changed)
{
    return registerBefore(changed)
        % name
        % QString("&nbsp;=&nbsp;")
        % value
        % QString("&nbsp;&nbsp; ")
        % registerAfter(changed);
}


QString SpimView::registerBefore(bool changed)
{
    return QString(changed && st_colorChangedRegisters
                   ? QString("<font color='") % QString(st_changedRegisterColor) % QString("'>")
                   : QString(""));
}


QString SpimView::registerAfter(bool changed)
{
    return QString(changed && st_colorChangedRegisters ? "</font>" : "");
}


QString SpimView::nnbsp(int n)
{
    QString str = "";
    int i;
    for (i = 0; i < n; i++)
    {
        str += "&nbsp;";
    }
    return str;
}


