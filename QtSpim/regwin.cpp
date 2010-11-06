/* SPIM S20 MIPS simulator.
   Terminal interface for SPIM simulator.

   Copyright (c) 1990-2010, James R. Larus.
   All rights reserved.

   Redistribution and use in source and binary forms, with or without modification,
   are permitted provided that the following conditions are met:

   Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.

   Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation and/or
   other materials provided with the distribution.

   Neither the name of the James R. Larus nor the names of its contributors may be
   used to endorse or promote products derived from this software without specific
   prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
   GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
   HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
   LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
   OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


#include "spimview.h"
#include "ui_spimview.h"

#include <QRegExp>
#include <QStringBuilder>
#define QT_USE_FAST_CONCATENATION
#include <QInputDialog>


//
// Integer registers window
//

void SpimView::DisplayIntRegisters()
{
    regTextEdit* te = ui->IntRegDockWidget->findChild<regTextEdit *>("IntRegTextEdit");
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
    te->appendHtml(windowContents);
    ui->IntRegDockWidget->setWindowTitle(QString("Int Regs [")
                                         + QString::number(st_intRegBase)
                                         + QString("] "));
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
    regTextEdit* te = ui->FPRegDockWidget->findChild<regTextEdit *>("FPRegTextEdit");
    te->clear();
    te->appendHtml(windowFormattingStart(st_regWinFont, st_regWinFontColor, st_regWinBackgroundColor)
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
    return formatReg(QString("<b>FG") % QString::number(regNum, 10) % (regNum < 10 ? "&nbsp;</b>" : "</b>"),
                     QString::number(value, 'f', 6),
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
                     QString::number(value, 'f', 6),
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
        % QString("<br>")
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


//
// Change register value
//

regTextEdit::regTextEdit()
{
    action_Context_ChangeValue = new QAction(this);
    action_Context_ChangeValue->setObjectName("action_ChangeValue");
    action_Context_ChangeValue->setText("Change Register Contents");
}


void regTextEdit::contextMenuEvent(QContextMenuEvent* event)
{
    QMenu *menu = createStandardContextMenu();
    menu->addSeparator();
    menu->addAction(action_Context_ChangeValue);
    contextGlobalPos = event->globalPos();

    menu->exec(event->globalPos());
}


void regTextEdit::changeValue()
{
    int reg = regAtPos("R");
    if (reg != -1)
    {
        bool ok;
        int value = QInputDialog::getInt(this,
                                         "Change Register Contents",
                                         "New Contents for R" + QString::number(reg, 10),
                                         0, -2147483647, 2147483647, 1, &ok);
        if (ok)
        {
            R[reg] = value;
        }
    }
    else
    {
        int reg = regAtPos("FG");
        if (reg != -1)
        {
            bool ok;
            double value = QInputDialog::getDouble(this,
                                                   "Change Register Contents",
                                                   "New Contents for FG" + QString::number(reg, 10),
                                                   0, -2147483647, 2147483647, 1, &ok);
            if (ok)
            {
                FGR[reg] = (float)value;
            }
        }
        else
        {
            int reg = regAtPos("FP");
            if (reg != -1)
            {
                bool ok;
                double value = QInputDialog::getDouble(this,
                                                       "Change Register Contents",
                                                       "New Contents for FP" + QString::number(reg, 10),
                                                       0, -2147483647, 2147483647, 1, &ok);
                if (ok)
                {
                    FGR[reg] = value;
                }
            }
            else
            {
                QString reg = strAtPos("([A-Za-z]+)");
                if (reg != "")
                {
                    bool ok;
                    int value = QInputDialog::getInt(this,
                                                     "Change Register Contents",
                                                     "New Contents for " + reg,
                                                     0, -2147483647, 2147483647, 1, &ok);
                    if (ok)
                    {
                        if (reg == "PC")
                        {
                            PC = value;
                        }
                        else if (reg == "EPC")
                        {
                            CP0_EPC = value;
                        }
                        else if (reg == "Cause")
                        {
                            CP0_Cause = value;
                        }
                        else if (reg == "BadVAddr")
                        {
                            CP0_BadVAddr = value;
                        }
                        else if (reg == "Status")
                        {
                            CP0_Status = value;
                        }
                        else if (reg == "HI")
                        {
                            HI = value;
                        }
                        else if (reg == "LO")
                        {
                            LO = value;
                        }
                        else if (reg == "FIR")
                        {
                            FIR = value;
                        }
                        else if (reg == "FCSR")
                        {
                            FCSR = value;
                        }
                        else if (reg == "FCCR")
                        {
                            FCCR = value;
                        }
                        else if (reg == "FEXR")
                        {
                            FEXR = value;
                        }
                    }
                }
            }
        }
    }
    Window->DisplayIntRegisters();
    Window->DisplayFPRegisters();
}


int regTextEdit::regAtPos(QString prefix)
{
    QString regStr = strAtPos(prefix + "([0-9]+)");    // Register name
    if (regStr != "")
    {
        return regStr.toInt();
    }
    else
    {
        return -1;
    }
}


QString regTextEdit::strAtPos(QString pattern)
{
    // Position of context menu is location user right-click. Find the line at this point
    // and compute the address of the memory location the user clicked on.
    //
    QPoint mouseViewportPos = this->viewport()->mapFromGlobal(contextGlobalPos);
    QTextCursor mouseCursor = this->cursorForPosition(mouseViewportPos);

    mouseCursor.select(QTextCursor::LineUnderCursor);
    QString line = mouseCursor.selectedText();

    QRegExp rx(pattern);

    rx.indexIn(line);
    return rx.cap(1);
}
