#include <QObject>
#include <QTextEdit>

class dataTextEdit : public QTextEdit
{
 Q_OBJECT

public:
    dataTextEdit();
    void contextMenuEvent(QContextMenuEvent* event);
    QAction* action_Context_ChangeValue;

private:
    QPoint contextGlobalPos;

public slots:
    void changeValue();
    int addrFromPos(QTextCursor* cursor);
};
