#ifndef SPIMVIEW_H
#define SPIMVIEW_H

#include <QMainWindow>
#include <QSettings>
#include <QList>
#include <QString>

#include "ui_spimview.h"

#include "../CPU/spim.h"
#include "../CPU/string-stream.h"
#include "../CPU/spim-utils.h"
#include "../CPU/inst.h"
#include "../CPU/reg.h"
#include "../CPU/mem.h"
#include "../CPU/sym-tbl.h"

namespace Ui {
    class SpimView;
}

class SpimView : public QMainWindow
{
 Q_OBJECT

     public:
    explicit SpimView(QWidget *parent = 0);
    ~SpimView();

    QString WriteOutput(QString message);
    void Error(QString message, bool fatal);

    void SaveStateAndExit(int val);

    char* ExceptionFileOrNull();

    void CaptureIntRegisters();
    void CaptureSFPRegisters();
    void CaptureDFPRegisters();

    void DisplayIntRegisters();
    void DisplayFPRegisters();
    void DisplayTextSegments();
    void DisplayDataSegments();


 private:
    Ui::SpimView *ui;


    //
    // Program state
    //
    void writeSettings();
    void readSettings();

    QSettings settings;

    // File menu
    //
    int st_recentFilesLength;
    QList<QString> st_recentFiles;
    void rebuildRecentFilesMenu();

    // Simulator menu
    //
    bool st_loadExceptionHandler;
    QString st_ExceptionHandlerFileName;
    int st_startAddress;
    QString st_commandLine;

    // Register window
    //
    bool st_colorChangedRegisters;
    QString st_changedRegisterColor;
    int st_intRegBase;

    // Text window
    //
    bool st_showUserTextSegment;
    bool st_showKernelTextSegment;
    bool st_showTextComments;
    bool st_showTextDisassembly;

    // Data window
    //
    bool st_showUserDataSegment;
    bool st_showUserStackSegment;
    bool st_showKernelDataSegment;
    int st_dataSegmentBase;

    //
    // End of state

    //
    // Methods:
    //

    // Establish text formatting for a window
    //
    QString windowFormattingStart();
    QString windowFormattingEnd();


    // Integer registers window
    //
    QString formatSpecialIntRegister(int value, char* name, bool changed);
    QString formatIntRegister(int regNum, int value, char* name, bool changed);

    // Value in register at previous call on displayIntRegister, so changed values
    // can be highlighted.
    //
    reg_word oldR[R_LENGTH];
    reg_word oldPC;
    reg_word oldEPC;
    reg_word oldCause;
    reg_word oldBadVAddr;
    reg_word oldStatus;
    reg_word oldHI;
    reg_word oldLO;


    // Single precision FP registers window
    //
    QString formatSFPRegisters();
    QString formatSpecialSFPRegister(int value, char* name, bool changed);
    QString formatSFPRegister(int regNum, float value, bool changed);

    float oldFPR_S[FGR_LENGTH];
    reg_word oldFIR;
    reg_word oldFCSR;
    reg_word oldFCCR;
    reg_word oldFEXR;


    // Double precision FP registers window
    //
    QString formatDFPRegisters();
    QString formatDFPRegister(int regNum, double value, bool changed);

    float oldFPR_D[FPR_LENGTH];


    // Common register methods
    //
    QString formatInt(int value);
    QString formatReg(QString reg, QString value, bool changed);
    QString registerBefore(bool changed);
    QString registerAfter(bool changed);
    QString nnbsp(int n);


    // Text segment window
    //
    QString formatUserTextSeg();
    QString formatKernelTextSeg();
    QString formatInstructions(mem_addr from, mem_addr to);
    void highlightInstruction(mem_addr pc);


    // Data segment window
    //
    QString formatUserDataSeg();
    QString formatUserStack();
    QString formatKernelDataSeg();
    QString formatMemoryContents(mem_addr from, mem_addr to);
    QString formatPartialQuadWord (mem_addr addr);


    //
    // Menu functions
    //
    void wireCommands();
    void initStack();
    void executeProgram(mem_addr pc, int steps, bool display, bool contBkpt);


 public slots:
    void file_LoadFile();
    void file_ReloadFile();
    void file_SaveLogFile();
    void file_Print();
    void file_Exit();

    void sim_ClearRegisters();
    void sim_ReinitializeSimulator();
    void sim_SetRunParameters();
    void sim_Run();
    void sim_SingleStep();
    void sim_DisplaySymbols();
    void sim_Settings();

    void reg_DisplayBinary();
    void reg_DisplayOctal();
    void reg_DisplayHex();
    void reg_DisplayDecimal();
    int setCheckedRegBase(int base);
    int setBaseInternal(int base, QAction* actionBinary, QAction* actionOctal, QAction* actionDecimal, QAction* actionHex);

    void text_DisplayUserText();
    void text_DisplayKernelText();
    void text_NarrowRange();
    void text_DisplayComments();
    void text_DisplayInstructionValue();

    void data_DisplayUserData();
    void data_DisplayUserStack();
    void data_DisplayKernelData();
    void data_NarrowDisplay();
    void data_DisplayBinary();
    void data_DisplayOctal();
    void data_DisplayHex();
    void data_DisplayDecimal();
    int setCheckedDataSegmentBase(int base);

    void win_IntRegisters();
    void win_FPRegisters();
    void win_TextSegment();
    void win_DataSegment();
    void win_Console();
    void win_Messages();
    void win_ClearConsole();

    void help_ViewHelp();
    void help_AboutSPIM();
};

extern SpimView* Window;


// Format SPIM abstractions for display
//
QString formatAddress(mem_addr addr);
QString formatWord(mem_word word, int base);
QString formatChar(int chr);
QString formatSegLabel(QString segName, mem_addr low, mem_addr high);


#endif // SPIMVIEW_H
