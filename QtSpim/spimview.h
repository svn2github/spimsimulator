#ifndef SPIMVIEW_H
#define SPIMVIEW_H

#include <QMainWindow>
#include <QSettings>

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

private:
    Ui::SpimView *ui;


    //
    // Program state
    //
    QSettings settings;

    // Register window
    //
    bool colorChangedRegisters;
    QString changedRegisterColor;
    int intRegBase;

    // Text window
    //
    bool showUserTextSegment;
    bool showKernelTextSegment;
    bool showTextComments;
    bool showTextDisassembly;

    // Data window
    //
    bool showUserDataSegment;
    bool showUserStackSegment;
    bool showKernelDataSegment;
    int dataSegmentBase;


    //
    // Establish text formatting for a window
    //
    QString windowFormattingStart();
    QString windowFormattingEnd();


    //
    // Integer registers window
    //
    void displayIntRegisters();
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
    void captureIntRegisters();


    //
    // Floating point registers window
    //
    void displayFPRegisters();

    //
    // Single precision FP registers window
    //
    QString formatSFPRegisters();
    QString formatSpecialSFPRegister(int value, char* name, bool changed);
    QString formatSFPRegister(int regNum, float value, bool changed);
    void captureSFPRegisters();

    float oldFPR_S[FGR_LENGTH];
    reg_word oldFIR;
    reg_word oldFCSR;
    reg_word oldFCCR;
    reg_word oldFEXR;


    //
    // Double precision FP registers window
    //
    QString formatDFPRegisters();
    QString formatDFPRegister(int regNum, double value, bool changed);
    void captureDFPRegisters();

    float oldFPR_D[FPR_LENGTH];


    //
    // Common register functions
    //
    QString formatInt(int value);
    QString formatReg(QString reg, QString value, bool changed);
    QString registerBefore(bool changed);
    QString registerAfter(bool changed);
    QString nnbsp(int n);


    //
    // Text segment window
    //
    void displayTextSegments();
    QString formatUserTextSeg();
    QString formatKernelTextSeg();
    QString formatInstructions(mem_addr from, mem_addr to);
    void highlightPC(QTextEdit *te, mem_addr pc);


    //
    // Data segment window
    //
    void displayDataSegments();
    QString formatUserDataSeg();
    QString formatUserStack();
    QString formatKernelDataSeg();
    QString formatMemoryContents(mem_addr from, mem_addr to);
    QString formatPartialQuadWord (mem_addr addr);


    //
    // Common segment functions
    //
    QString formatAddress(mem_addr addr);
    QString formatWord(mem_word word, int base);
    QString formatChar(int chr);
    QString formatSegLabel(QString segName, mem_addr low, mem_addr high);
};

#endif // SPIMVIEW_H
