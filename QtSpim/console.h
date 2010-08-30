#include <QObject>
#include <QPlainTextEdit>
#include <QString>
#include <QEventLoop>

class Console : public QPlainTextEdit
{
Q_OBJECT

public:
    Console(QWidget* parent);

    virtual void keyPressEvent(QKeyEvent* e);
    virtual void keyReleaseEvent(QKeyEvent* e);
    virtual void mouseMoveEvent(QMouseEvent* e);
    virtual void mousePressEvent(QMouseEvent* e);

    void WriteOutput(QString out);
    QString ReadChar(int len = 1);
    void Clear();

private:
    QString inputBuffer;
    QEventLoop l;
};
