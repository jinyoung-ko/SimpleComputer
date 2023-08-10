#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "helpdialog.h"
#include "ui_helpdialog.h"
#include "loaddialog.h"
#include "ui_loaddialog.h"
#include <QMainWindow>
#include <QtWidgets>
#include <QtCore>
#include <QtDebug>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QFileDialog>

namespace Ui {
class MainWindow;
}

enum OpCodes {
    INP,
    OUT,
    ADD,
    SUB,
    LDA,
    STA,
    JMP,
    TAC,
    SHF,
    HLT
};

class MainWindow : public QMainWindow
{
   Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_clearInputBtn_clicked();
    void on_clearAllBtn_clicked();
    void on_clearCpuBtn_clicked();
    void on_clearOutputBtn_clicked();
    void on_runBtn_clicked();
    void on_clearMemBtn_clicked();
    void on_stepBtn_clicked();
    void on_resetInputBtn_clicked();
    void on_helpBtn_clicked();
    void on_saveBtn_clicked();

    void on_actionLoad_triggered();
    void on_actionSave_triggered();
    void on_actionHelp_triggered();

    void LoadProgramFromFile(QString path);
    void LoadPCFile(QTextStream &inStream);
    void LoadMemoryFile(QTextStream &inStream);
    void LoadInputFile(QTextStream &inStream);
    void SaveProgramToFile(QString path);

    bool OneStep();
    void Validate();
    void ValidateMemory(QString addr);
    void ValidateInput(QString addr);
    QString ValidateAcc(QString checkAcc);
    QString ValidateOutput(QString checkOut);
    bool IsMemEmpty();
    bool IsInputEmpty();
    QString ValidatePC(QString pc);
    void Initialize();
    void Reset();
    bool SignExecute();

    bool Inp(QString address);
    bool Out(QString address);
    void Add(QString address);
    void Sub(QString address);
    void Lda(QString address);
    void Sta(QString address);
    void Jmp(QString address);
    void Tac(QString address);
    void Shf(QString xyShift);
    void Hlt(QString address);

    void on_memLineEdit00_editingFinished();
    void on_memLineEdit01_editingFinished();
    void on_memLineEdit02_editingFinished();
    void on_memLineEdit03_editingFinished();
    void on_memLineEdit04_editingFinished();
    void on_memLineEdit05_editingFinished();
    void on_memLineEdit06_editingFinished();
    void on_memLineEdit07_editingFinished();
    void on_memLineEdit08_editingFinished();
    void on_memLineEdit09_editingFinished();
    void on_memLineEdit10_editingFinished();
    void on_memLineEdit11_editingFinished();
    void on_memLineEdit12_editingFinished();
    void on_memLineEdit13_editingFinished();
    void on_memLineEdit14_editingFinished();
    void on_memLineEdit15_editingFinished();
    void on_memLineEdit16_editingFinished();
    void on_memLineEdit17_editingFinished();
    void on_memLineEdit18_editingFinished();
    void on_memLineEdit19_editingFinished();
    void on_memLineEdit20_editingFinished();
    void on_memLineEdit21_editingFinished();
    void on_memLineEdit22_editingFinished();
    void on_memLineEdit23_editingFinished();
    void on_memLineEdit24_editingFinished();
    void on_memLineEdit25_editingFinished();
    void on_memLineEdit26_editingFinished();
    void on_memLineEdit27_editingFinished();
    void on_memLineEdit28_editingFinished();
    void on_memLineEdit29_editingFinished();
    void on_memLineEdit30_editingFinished();
    void on_memLineEdit31_editingFinished();
    void on_memLineEdit32_editingFinished();
    void on_memLineEdit33_editingFinished();
    void on_memLineEdit34_editingFinished();
    void on_memLineEdit35_editingFinished();
    void on_memLineEdit36_editingFinished();
    void on_memLineEdit37_editingFinished();
    void on_memLineEdit38_editingFinished();
    void on_memLineEdit39_editingFinished();
    void on_memLineEdit40_editingFinished();
    void on_memLineEdit41_editingFinished();
    void on_memLineEdit42_editingFinished();
    void on_memLineEdit43_editingFinished();
    void on_memLineEdit44_editingFinished();
    void on_memLineEdit45_editingFinished();
    void on_memLineEdit46_editingFinished();
    void on_memLineEdit47_editingFinished();
    void on_memLineEdit48_editingFinished();
    void on_memLineEdit49_editingFinished();
    void on_memLineEdit50_editingFinished();
    void on_memLineEdit51_editingFinished();
    void on_memLineEdit52_editingFinished();
    void on_memLineEdit53_editingFinished();
    void on_memLineEdit54_editingFinished();
    void on_memLineEdit55_editingFinished();
    void on_memLineEdit56_editingFinished();
    void on_memLineEdit57_editingFinished();
    void on_memLineEdit58_editingFinished();
    void on_memLineEdit59_editingFinished();
    void on_memLineEdit60_editingFinished();
    void on_memLineEdit61_editingFinished();
    void on_memLineEdit62_editingFinished();
    void on_memLineEdit63_editingFinished();
    void on_memLineEdit64_editingFinished();
    void on_memLineEdit65_editingFinished();
    void on_memLineEdit66_editingFinished();
    void on_memLineEdit67_editingFinished();
    void on_memLineEdit68_editingFinished();
    void on_memLineEdit69_editingFinished();
    void on_memLineEdit70_editingFinished();
    void on_memLineEdit71_editingFinished();
    void on_memLineEdit72_editingFinished();
    void on_memLineEdit73_editingFinished();
    void on_memLineEdit74_editingFinished();
    void on_memLineEdit75_editingFinished();
    void on_memLineEdit76_editingFinished();
    void on_memLineEdit77_editingFinished();
    void on_memLineEdit78_editingFinished();
    void on_memLineEdit79_editingFinished();
    void on_memLineEdit80_editingFinished();
    void on_memLineEdit81_editingFinished();
    void on_memLineEdit82_editingFinished();
    void on_memLineEdit83_editingFinished();
    void on_memLineEdit84_editingFinished();
    void on_memLineEdit85_editingFinished();
    void on_memLineEdit86_editingFinished();
    void on_memLineEdit87_editingFinished();
    void on_memLineEdit88_editingFinished();
    void on_memLineEdit89_editingFinished();
    void on_memLineEdit90_editingFinished();
    void on_memLineEdit91_editingFinished();
    void on_memLineEdit92_editingFinished();
    void on_memLineEdit93_editingFinished();
    void on_memLineEdit94_editingFinished();
    void on_memLineEdit95_editingFinished();
    void on_memLineEdit96_editingFinished();
    void on_memLineEdit97_editingFinished();
    void on_memLineEdit98_editingFinished();
    void on_memLineEdit99_editingFinished();
    void on_pcLineEdit_textEdited(const QString &arg1);

    void on_loadBtn_clicked();

    void on_inputLineEdit01_editingFinished();
    void on_inputLineEdit02_editingFinished();
    void on_inputLineEdit03_editingFinished();
    void on_inputLineEdit04_editingFinished();
    void on_inputLineEdit05_editingFinished();
    void on_inputLineEdit06_editingFinished();
    void on_inputLineEdit07_editingFinished();
    void on_inputLineEdit08_editingFinished();
    void on_inputLineEdit09_editingFinished();
    void on_inputLineEdit10_editingFinished();
    void on_inputLineEdit11_editingFinished();
    void on_inputLineEdit12_editingFinished();
    void on_inputLineEdit13_editingFinished();
    void on_inputLineEdit14_editingFinished();
    void on_inputLineEdit15_editingFinished();

    void on_actionGoodBye_triggered();

private:
    Ui::MainWindow *ui;
    QString inpCardNum;
    QString outCardNum;
    QString startPC;
    QString inReg;
    QLineEdit *memLine;
    QLineEdit *inputLine;
    QLineEdit *outputLine;
};

#endif // MAINWINDOW_H

