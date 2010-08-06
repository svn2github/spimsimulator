#include "spimview.h"
#include "ui_spimview.h"

#include <QStringBuilder>
#define QT_USE_FAST_CONCATENATION


//
// Data segment window
//

void SpimView::displayDataSegments()
{
    QTextEdit* te = ui->DataSegDockWidget->findChild<QTextEdit *>("DataSegTextEdit");

    te->clear();
    te->setHtml(windowFormattingStart()
                % formatUserDataSeg()
                % formatUserStack()
                % formatKernelDataSeg()
                % windowFormattingEnd());
}


QString SpimView::formatUserDataSeg()
{
    if (showUserDataSegment)
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
    if (showUserStackSegment)
    {
        return formatSegLabel("<br>User Stack", ROUND_DOWN(R[29], BYTES_PER_WORD), STACK_TOP - 4096)
            % formatMemoryContents(ROUND_DOWN(R[29], BYTES_PER_WORD), STACK_TOP - 4096);
    }
    else
    {
        return QString("");
    }
}


QString SpimView::formatKernelDataSeg()
{
    if (showKernelDataSegment)
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
    mem_addr i = ROUND_UP (from, BYTES_PER_WORD);
    QString windowContents = formatPartialQuadWord (i);
    i = ROUND_UP(i, BYTES_PER_LINE); // Next quadword

    for ( ; i < to; )
    {
        mem_word val;

        /* Count consecutive zero words */
        int j;
        for (j = 0; (i + (uint32) j * BYTES_PER_WORD) < to; j += 1)
	{
            val = read_mem_word (i + (uint32) j * BYTES_PER_WORD);
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
            windowContents += formatPartialQuadWord (i);
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
                windowContents += nnbsp(2) % formatWord(val, dataSegmentBase);
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


QString SpimView::formatPartialQuadWord (mem_addr addr)
{
    QString windowContents = "";

    if ((addr % BYTES_PER_LINE) != 0)
    {
        windowContents += QString("[") % formatAddress(addr) % QString("]") % nnbsp(2);

        for (; (addr % BYTES_PER_LINE) != 0; addr += BYTES_PER_WORD)
	{
            mem_word val = read_mem_word (addr);
            windowContents += nnbsp(2) % formatWord(val, dataSegmentBase);
	}

        windowContents += "<br>";
    }

    return windowContents;
}



//
// Utility functions
//

QString SpimView::formatAddress(mem_addr addr)
{
    return QString::number(addr, 16).rightJustified(8, '0');
}


QString SpimView::formatWord(mem_word word, int base)
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


QString SpimView::formatChar(int chr)
{
    return QString(QChar(chr));
}

QString SpimView::formatSegLabel(QString segName, mem_addr low, mem_addr high)
{
    return QString("<center><b>") % segName
        % QString(" [") % formatAddress(low) % QString("]..[") % formatAddress(high)
        % QString("]</b></center>");
}
