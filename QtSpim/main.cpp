#include <QtGui/QApplication>
#include "spimview.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SpimView w;
    w.show();

    return a.exec();
}
