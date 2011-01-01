/* SPIM S20 MIPS simulator.
   Terminal interface for SPIM simulator.

   Copyright (c) 1990-2010, James R. Larus.
   All rights reserved.

   Redistribution and use in source and binary forms, with or without modification,
   are permitted provided that the following conditions are met:

   Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.

   Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation and/or
   other materials provided with the distribution.

   Neither the name of the James R. Larus nor the names of its contributors may be
   used to endorse or promote products derived from this software without specific
   prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
   GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
   HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
   LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
   OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


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

    win.show();

    win.sim_ReinitializeSimulator();

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
#ifdef _WIN32
"         min-width: 32ex;"
"         padding: 2px;"
#else
"         min-width: 8ex;"
"         padding: 2px; padding-left:10px; padding-right:10px;"
#endif
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
