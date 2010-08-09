#include <QtGui/QApplication>
#include "spimview.h"

SpimView* Window;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SpimView win;
    Window = &win;
    win.show();

    return a.exec();
}
