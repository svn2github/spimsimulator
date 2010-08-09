#include <QtGui/QApplication>
#include "spimview.h"

SpimView* Window;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SpimView win;
    Window = &win;

    // Initialize Spim
    //
    message_out.i = 1;
    console_out.i = 2;

    initialize_world(win.ExceptionFileOrNull());
    //initialize_run_stack(program_argc, program_argv);
    write_startup_message();

    // Initialize the contents of the windows
    //
    win.CaptureIntRegisters();
    win.CaptureSFPRegisters();
    win.CaptureDFPRegisters();

    win.DisplayIntRegisters();
    win.DisplayFPRegisters();

    win.DisplayTextSegments();
    win.DisplayDataSegments();


    win.show();

    return a.exec();
}
