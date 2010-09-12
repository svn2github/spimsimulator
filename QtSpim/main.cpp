#include <QtGui/QApplication>
#include "spimview.h"

SpimView* Window;
QApplication* App;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    App = &a;
    SpimView win;
    Window = &win;

    // Initialize Spim
    //
    message_out.i = 1;
    console_out.i = 2;

    win.sim_ReinitializeSimulator();

    win.show();

    a.setStyleSheet(
"  QTabWidget::pane { /* The tab widget frame */"
"         border-top: 2px solid #C2C7CB;"
"     }"
""
"     QTabWidget::tab-bar {"
"         left: 5px; /* move to the right by 5px */"
"     }"
""
"     /* Style the tab using the tab sub-control. Note that"
"         it reads QTabBar _not_ QTabWidget */"
"     QTabBar::tab {"
"         background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
"                                     stop: 0 #E1E1E1, stop: 0.4 #DDDDDD,"
"                                     stop: 0.5 #D8D8D8, stop: 1.0 #D3D3D3);"
"         border: 2px solid #C4C4C3;"
"         border-bottom-color: #C2C7CB; /* same as the pane color */"
"         border-top-left-radius: 4px;"
"         border-top-right-radius: 4px;"
"         min-width: 8ex;"
"         padding: 2px; padding-left:10px; padding-right:10px;"
"         font: bold 12px"
"     }"
""
"     QTabBar::tab:selected, QTabBar::tab:hover {"
"         background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
"                                     stop: 0 #fafafa, stop: 0.4 #f4f4f4,"
"                                     stop: 0.5 #e7e7e7, stop: 1.0 #fafafa);"
"     }"
""
"     QTabBar::tab:selected {"
"         border: 2px solid #FF9933;"
"         border-bottom-color: #C2C7CB; /* same as pane color */"
"     }"
""
"     QTabBar::tab:!selected {"
"         margin-top: 2px; /* make non-selected tabs look smaller */"
"     }"
                    );

    return a.exec();
}
