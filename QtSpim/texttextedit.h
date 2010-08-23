#include <QObject>
#include <QTextEdit>

class textTextEdit : public QTextEdit
{
 Q_OBJECT

public:
    textTextEdit();
    void contextMenuEvent(QContextMenuEvent* event);
    QAction* action_Context_SetBreakpoint;
    QAction* action_Context_ClearBreakpoint;

private:
    QPoint contextGlobalPos;

public slots:
    void setBreakpoint();
    void clearBreakpoint();
    int pcFromPos(QTextCursor* cursor);
};
