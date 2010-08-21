#include "spimview.h"
#include "ui_spimview.h"

#include <QRegExp>

#include <QStringBuilder>
#define QT_USE_FAST_CONCATENATION


//
// Text segment window
//

void SpimView::DisplayTextSegments()
{
    QTextEdit* te = ui->TextSegDockWidget->findChild<QTextEdit *>("TextSegmentTextEdit");

    te->clear();
    te->setHtml(windowFormattingStart()
                % formatUserTextSeg()
                % formatKernelTextSeg()
                % windowFormattingEnd());
    highlightInstruction(PC);
}


QString SpimView::formatUserTextSeg()
{
    if (st_showUserTextSegment) 
    {
        return formatSegLabel("User Text Segment", TEXT_BOT, text_top)
            % formatInstructions(TEXT_BOT, text_top);
    }
    else
    {
        return QString("");
    }
}


QString SpimView::formatKernelTextSeg()
{
    if (st_showKernelTextSegment)
    {
        return formatSegLabel("Kernel Text Segment", K_TEXT_BOT, k_text_top)
            % formatInstructions(K_TEXT_BOT, k_text_top);
    }
    else
    {
        return QString("");
    }
}


QString SpimView::formatInstructions(mem_addr from, mem_addr to)
{
    str_stream ss;
    mem_addr a;
    QString windowContents;

    ss_init(&ss);
    for (a = from; a < to; a += 4)
    {
        instruction *inst = read_mem_inst(a);
        if (inst != NULL)
	{
            format_an_inst(&ss, inst, a);

            char* pc = ss_to_string(&ss);
            char* binInst = pc + 14;
            char* disassembly = binInst + 11;
            char* comment = NULL;

            pc += 3;
            pc[8] = '\0';
            binInst += 1;
            binInst[8] = '\0';
            comment = strstr(disassembly, ";");
            if (comment != NULL)
            {
                char* s;
                for (s = comment - 1; *s == ' '; s--);
                *(s + 1) = '\0';
            }
            if (inst_is_breakpoint(a))
            {
                windowContents += QString("<font face='Wingdings 2' color='red'>N</font> ");
            }
            windowContents += QString("[") % QString(pc) % QString("] ")
                % (st_showTextDisassembly ? QString(binInst) : QString(""))
                % nnbsp(2) % QString("<b>") % QString(disassembly) % QString("</b>")
                % nnbsp(25 - strlen(disassembly))
                % (comment != NULL && st_showTextComments
                   ? QString("<i>") % QString(comment) % QString("</i>")
                   : QString(""))
                % QString("<br>");
            ss_clear(&ss);
	}
    }

    return windowContents;
}


void SpimView::highlightInstruction(mem_addr pc)
{
    QTextEdit* te = ui->TextSegDockWidget->findChild<QTextEdit *>("TextSegmentTextEdit");

    QString str = te->toHtml();

    QRegExp rx("\\[" + formatAddress(pc) + "\\]"); // Start of specific line
    QRegExp rx2("(\\[[0-9a-fA-F]{8}\\])|(N \\[)"); // Start of any line

    QTextCursor cursor(te->document());
    cursor = te->document()->find(rx, cursor);
    if (!cursor.isNull())
    {
        // Find end of current line by finding start of next line
        //
        QTextCursor endCursor(te->document());
        endCursor = te->document()->find(rx2, cursor);

        if (endCursor.isNull())
        {
            // Last line does not have successor
            //
            cursor.movePosition(QTextCursor::End, QTextCursor::KeepAnchor);
        }
        else
        {
            // Backup over match to end of current line
            //
            endCursor.movePosition(QTextCursor::PreviousCharacter,
                                   QTextCursor::KeepAnchor,
                                   endCursor.selectedText().length());

            cursor.setPosition(endCursor.position(), QTextCursor::KeepAnchor);
        }

        QTextCharFormat format;
        format.setBackground(QBrush(Qt::cyan));

        QTextEdit::ExtraSelection es;
        es.cursor = cursor;
        es.format = format;
        QList<QTextEdit::ExtraSelection> ess;
        ess << es;
        te->setExtraSelections(ess);
    }
}
