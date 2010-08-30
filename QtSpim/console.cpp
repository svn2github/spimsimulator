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

