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
#include <QContextMenuEvent>
#include <QStringBuilder>
#define QT_USE_FAST_CONCATENATION
#include <QInputDialog>
#include <QScrollBar>


//
// Data segment window
//

void SpimView::DisplayDataSegments()
{
    if (data_modified)
    {
        dataTextEdit* te = ui->DataSegDockWidget->findChild<dataTextEdit *>("DataSegmentTextEdit");
        QString windowContents = windowFormattingStart(st_textWinFont, st_textWinFontColor, st_textWinBackgroundColor);
        int scrollPosition = te->verticalScrollBar()->value();

        windowContents += formatUserDataSeg() % formatUserStack() % formatKernelDataSeg() % windowFormattingEnd();

        te->clear();
        te->appendHtml(windowContents);

        te->verticalScrollBar()->setValue(scrollPosition);
    }
    data_modified = 0;
}


QString SpimView::formatUserDataSeg()
{
    if (st_showUserDataSegment)
    {
        return formatSegLabel("User data segment", DATA_BOT, data_top)
            % formatMemoryContents(DATA_BOT, data_top);
    }
    else
    {
        return QString("");
    }
}


QString SpimView::formatUserStack()
{
    if (st_showUserStackSegment)
    {
        return formatSegLabel("<br>User Stack", ROUND_DOWN(R[29], BYTES_PER_WORD), STACK_TOP)
            % formatMemoryContents(ROUND_DOWN(R[29], BYTES_PER_WORD), STACK_TOP);
    }
    else
    {
        return QString("");
    }
}


QString SpimView::formatKernelDataSeg()
{
    if (st_showKernelDataSegment)
    {
        return formatSegLabel("<br>Kernel data segment", K_DATA_BOT, k_data_top)
            % formatMemoryContents(K_DATA_BOT, k_data_top);
    }
    else
    {
        return QString("");
    }
}


#define BYTES_PER_LINE (4*BYTES_PER_WORD)


QString SpimView::formatMemoryContents(mem_addr from, mem_addr to)
{
    mem_addr i = ROUND_UP(from, BYTES_PER_WORD);
    QString windowContents = formatPartialQuadWord(i);
    i = ROUND_UP(i, BYTES_PER_LINE); // Next quadword

    for ( ; i < to; )
    {
        mem_word val;

        /* Count consecutive zero words */
        int j;
        for (j = 0; (i + (uint32) j * BYTES_PER_WORD) < to; j += 1)
	{
            val = read_mem_word(i + (uint32) j * BYTES_PER_WORD);
            if (val != 0)
	    {
                break;
	    }
	}

        if (j >= 4)
	{
            /* Block of 4 or more zero memory words: */
            windowContents += QString("[") % formatAddress(i)
                % QString("]..[") % formatAddress(i + (uint32) j * BYTES_PER_WORD)
                % QString("]") % nnbsp(2) % QString("00000000<\br>");

            i = i + (uint32) j * BYTES_PER_WORD;
            windowContents += formatPartialQuadWord(i);
            i = ROUND_UP(i, BYTES_PER_LINE); // Next quadword
	}
        else
	{
            /* Fewer than 4 zero words, print them on a single line: */
            windowContents += QString("[") % formatAddress(i) % "]" % nnbsp(2);
            mem_addr j = i;
            do
	    {
                val = read_mem_word(i);
                windowContents += nnbsp(2) % formatWord(val, st_dataSegmentBase);
                i += BYTES_PER_WORD;
	    }
            while (i % BYTES_PER_LINE != 0);

            windowContents += nnbsp(2);
            for ( ; j < i; j+= 1)
            {
                val = read_mem_byte(j);
                windowContents += formatChar(val) % " ";
            }
            windowContents += "<br>";
	}
    }
    return windowContents;
}


QString SpimView::formatPartialQuadWord(mem_addr addr)
{
    QString windowContents = QString("");

    if ((addr % BYTES_PER_LINE) != 0)
    {
        windowContents += QString("[") % formatAddress(addr) % QString("]") % nnbsp(2);

        for (; (addr % BYTES_PER_LINE) != 0; addr += BYTES_PER_WORD)
	{
            mem_word val = read_mem_word (addr);
            windowContents += nnbsp(2) % formatWord(val, st_dataSegmentBase);
	}

        windowContents += "<br>";
    }

    return windowContents;
}


//
// Utility functions
//

QString formatAddress(mem_addr addr)
{
    return QString::number(addr, 16).rightJustified(8, '0');
}


QString formatWord(mem_word word, int base)
{
    int width = 0;
    switch (base)
    {
    case 8: width = 11; break;
    case 10: width = 10; break;
    case 16: width = 8; break;
    default: width = 32; break;
    }
    QString str = QString::number(word, base);
    str.remove(0, str.length() - width); // Negative hex number proceeded by 0xffffffff
    return str.QString::rightJustified(width, '0');
}


QString formatChar(int chr)
{
    return QString(QChar(chr));
}

QString formatSegLabel(QString segName, mem_addr low, mem_addr high)
{
    return QString("<center><b>") % segName
        % QString(" [") % formatAddress(low) % QString("]..[") % formatAddress(high)
        % QString("]</b></center>");
}


//
// Change memory value
//

dataTextEdit::dataTextEdit()
{
    action_Context_ChangeValue = new QAction(this);
    action_Context_ChangeValue->setObjectName("action_ChangeValue");
    action_Context_ChangeValue->setText("Change Memory Contents");
}


void dataTextEdit::contextMenuEvent(QContextMenuEvent* event)
{
    QMenu *menu = createStandardContextMenu();
    menu->addSeparator();
    menu->addAction(action_Context_ChangeValue);
    contextGlobalPos = event->globalPos();

    menu->exec(event->globalPos());
}


void dataTextEdit::changeValue()
{
    QTextCursor cursor;
    mem_addr addr = addrFromPos(&cursor);
    if (addr != 0)
    {
        bool ok;
        int value = QInputDialog::getInt(this,
                                         "Change Memory Contents",
                                         "New Contents for " + formatAddress(addr),
                                         0,
                                         -2147483647,
                                         2147483647,
                                         1,
                                         &ok);
        if (ok)
        {
            set_mem_word(addr, value);
        }
        Window->DisplayDataSegments();
    }
}


int dataTextEdit::addrFromPos(QTextCursor* cursor)
{
    // Position of context menu is location user right-click. Find the line at this point
    // and compute the address of the memory location the user clicked on.
    //
    QPoint mouseViewportPos = this->viewport()->mapFromGlobal(contextGlobalPos);
    QTextCursor mouseCursor = this->cursorForPosition(mouseViewportPos);
    *cursor = mouseCursor;

    cursor->select(QTextCursor::LineUnderCursor);
    QString line = cursor->selectedText();

    QRegExp rx("\\[([0-9a-fA-F]{8})\\]"); // Address of instruction

    rx.indexIn(line);
    QString addrStr = rx.cap(1);
    if (addrStr != "")
    {
        bool ok;
        mem_addr addr = addrStr.toUInt(&ok, 16);
        if (ok)
        {
            // [...]<sp><sp><sp><sp>#<sp><sp>#<sp><sp>#<sp><sp>#<sp><sp>
            //
            int offset = mouseCursor.position() - cursor->anchor(); // Start of line to mouse location
            line.truncate(offset);                                  // Remove address
            line.remove(0, 14);                                     // Remove line after mouse position

            QRegExp rx2("^([0-9a-fA-F]+\\s*)?([0-9a-fA-F]+\\s*)?([0-9a-fA-F]+\\s*)?([0-9a-fA-F]+\\s*)?");
            rx2.indexIn(line, 0);
            return addr
                + (rx2.cap(1) == "" ? 0 : 0)
                + (rx2.cap(2) == "" ? 0 : BYTES_PER_WORD)
                + (rx2.cap(3) == "" ? 0 : BYTES_PER_WORD)
                + (rx2.cap(4) == "" ? 0 : BYTES_PER_WORD);
        }
    }
    return 0;
}
