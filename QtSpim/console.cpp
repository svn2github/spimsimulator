#include "spimview.h"

Console::Console(QWidget *parent)
    : QPlainTextEdit(parent)
{
    setWindowTitle("Console");
    resize(800, 600);

    setUndoRedoEnabled(false);
    appendPlainText(QString(""));
}


void Console::WriteOutput(QString out)
{
    moveCursor(QTextCursor::End);
    insertPlainText(out);
}


QString Console::ReadChar(int len)
{
    raise();
    while (1)
    {
        if (inputBuffer.length() > 0)
        {
            QString chars = inputBuffer.left(len);
            inputBuffer.remove(0, chars.length());
            return chars;
        }
        // This is a bit tricky and I hope it works on all platforms. If there aren't any
        // characters in the buffer, start a new event loop to wait for keystrokes and block on
        // it. Cannot use semaphores or busy-wait since both actions are on the same thread.
        //
        l.exec();
    }
}


void Console::Clear()
{
    setPlainText("");
}


void Console::keyPressEvent(QKeyEvent* e)
{
    // Ignore
}

void Console::keyReleaseEvent(QKeyEvent* e)
{
    QString key = e->text();

    if (key != "")
    {
        inputBuffer.append(key);
        WriteOutput(key);

        // Release the call on ReadChar (if any) that is blocked waiting for input.
        //
        l.exit();
    }
}

void Console::mouseMoveEvent(QMouseEvent* e)
{
    // Ignore
}

void Console::mousePressEvent(QMouseEvent* e)
{
    // Ignore
}

