#include "mainwindow.h"
#include "ui_mainwindow.h"

/**************************************************************************
 *  MainWindow - Constructor
 *************************************************************************/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->setFixedSize(800, 750);
    ui->setupUi(this);

    Validate();
    Initialize();
}

/**************************************************************************
 *  ~MainWindow - Destructor
 *************************************************************************/
MainWindow::~MainWindow()
{
    delete ui;
}

/**************************************************************************
 *  on_actionGoodBye_triggered - Quits Simple Computer Program
 *************************************************************************/
void MainWindow::on_actionGoodBye_triggered()
{
    QApplication::quit();
}

/**************************************************************************
 *  on_actionLoad_triggered - Load Menu bar
 *************************************************************************/
void MainWindow::on_actionLoad_triggered()
{
    on_loadBtn_clicked();
}

/**************************************************************************
 *  on_actionSave_triggered - Save Menu Bar
 *************************************************************************/
void MainWindow::on_actionSave_triggered()
{
    on_saveBtn_clicked();
}

/**************************************************************************
 *  on_actionHelp_triggered - Help Menu bar
 *************************************************************************/
void MainWindow::on_actionHelp_triggered()
{
    on_helpBtn_clicked();
}

/**************************************************************************
 *  on_helpBtn_clicked - Popup help dialog box
 *************************************************************************/
void MainWindow::on_helpBtn_clicked()
{
    HelpDialog *helpDialog = new HelpDialog();
    helpDialog->exec();
}

/**************************************************************************
 *  on_loadBtn_clicked - Popup load dialog box & load file
 *************************************************************************/
void MainWindow::on_loadBtn_clicked()
{
    LoadDialog *ldaDialog = new LoadDialog();
    ldaDialog->exec();
    QString     fileName  = ldaDialog->GetFileName();
    if(fileName != "")
        LoadProgramFromFile(fileName);
}

/**************************************************************************
 *  on_saveBtn_clicked - Popup dialog box to save file & call to save file
 *************************************************************************/
void MainWindow::on_saveBtn_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                    "C://", "Text File (*.txt);;");
    if(fileName != "")
        SaveProgramToFile(fileName);
}

/**************************************************************************
 *  SaveProgramToFile - Save file
 *************************************************************************/
void MainWindow::SaveProgramToFile(QString path) {
    QFile outFile(path);

    // Check if file exists
    if(!outFile.open(QFile::WriteOnly | QFile::Text))
    {
         QMessageBox::warning(this, "Load File", "File chosen is invalid");
    }
    else
    {
        // Write to File
        QTextStream outStream(&outFile);
        QString     address;

        outStream << "Program Counter:" << endl;
        outStream << "PC: "             << ui->pcLineEdit->text() << endl << endl;
        outStream << "Memory:"          << endl;

        for(int i = 0; i < 100; i++) {
            i < 10 ? address = "0" + QString::number(i) : address = QString::number(i);
            memLine = ui->MemoryBox->findChild<QLineEdit*>("memLineEdit" + address);
            outStream << address << ": " << memLine->text() << endl;
        }

        outStream << endl << "Input:" << endl;
        for(int i = 1; i <= 15; i++) {
            i < 10 ? address = "0" + QString::number(i) : address = QString::number(i);
            inputLine = ui->InputCards->findChild<QLineEdit*>("inputLineEdit" + address);
            outStream << address << ": " << inputLine->text() << endl;
        }
        outFile.close();
    }
}

/**************************************************************************
 *  LoadProgramFromFile - Load file
 *************************************************************************/
void MainWindow::LoadProgramFromFile(QString path) {
    on_clearAllBtn_clicked();
    Initialize();

    // Check if file exists
    QFile inFile(path);
    if(!inFile.open(QFile::ReadOnly | QFile::Text))
    {
         QMessageBox::warning(this, "Load File", "File chosen is invalid");
    }
    else
    {
        // Get info from file
        QString     line;
        QTextStream inStream(&inFile);

        while (!inStream.atEnd()) {
            line = inStream.readLine();

            if(line == "Program Counter:")
                LoadPCFile(inStream);
            else if(line == "Memory:")
                LoadMemoryFile(inStream);
            else if(line == "Input:")
                LoadInputFile(inStream);
        }
    }
}

/**************************************************************************
 *  LoadInputFile - Load Input from file
 *************************************************************************/
void MainWindow::LoadInputFile(QTextStream &inStream) {
    QString     line;
    QStringList list;
    QString     address;

    // Get Input 1 to 15
    for(int i = 1; i <= 15; i++) {
        i < 10 ? address = "0" + QString::number(i) : address = QString::number(i);
        inputLine = ui->InputCards->findChild<QLineEdit*>("inputLineEdit" + address);
        line = inStream.readLine();
        list = line.split(":");

        if(list[1].trimmed() != "")
            inputLine->setText(list[1].trimmed());
    }
}

/**************************************************************************
 *  LoadMemoryFile - Load Memory from file
 *************************************************************************/
void MainWindow::LoadMemoryFile(QTextStream &inStream) {
    QString     line;
    QStringList list;
    QString     address;

    // Get Memory
    for(int i = 0; i <= 99; i++) {
        i < 10 ? address = "0" + QString::number(i) : address = QString::number(i);
        memLine = ui->MemoryBox->findChild<QLineEdit*>("memLineEdit" + address);
        line = inStream.readLine();
        list = line.split(":");

        if(list[1].trimmed() != "")
            memLine->setText(list[1].trimmed());
    }
    ui->memLineEdit00->setText("001");
}

/**************************************************************************
 *  LoadPCFile - Load Program Counter from file
 *************************************************************************/
void MainWindow::LoadPCFile(QTextStream &inStream) {
    QString line = inStream.readLine();
    QString pc = line.right(2);

    pc = ValidatePC(pc);
    ui->pcLineEdit->setText(pc);
    startPC = pc;
}

/**************************************************************************
 *  Validate - Validates all line edits
 *************************************************************************/
void MainWindow::Validate() {
    QRegExp rx("-?\\d{0,3}");
    QRegExp pcRx("\\d{0,2}");

    QValidator *validator   = new QRegExpValidator(rx, this);
    QValidator *pcValidator = new QRegExpValidator(pcRx, this);

    foreach(QLineEdit* le, findChildren<QLineEdit*>()) {
        le->setValidator(validator);

        if(le->text() != "") {
            if(le->text().toInt() > 0) {
                QString number = QString("%1").arg(le->text().toInt(), 3, 10, QChar('0'));
                le->setText(number);
            }
            else {
                QString number = QString("%1").arg(le->text().toInt(), 4, 10, QChar('0'));
                le->setText(number);
            }
        }
    }
    ui->pcLineEdit->setValidator(pcValidator);

    if(ui->pcLineEdit->text().toInt() < 10) {
        QString num = QString("%1").arg(ui->pcLineEdit->text().toInt(), 2, 10, QChar('0'));
        ui->pcLineEdit->setText(num);
    }
}

/**************************************************************************
 *  ValidateAcc - Carry digit (0 or 1) & accumulator (### - 3 digit)
 *************************************************************************/
QString MainWindow::ValidateAcc(QString checkAcc) {
    QRegExp     rx("-?\\d{0,3}");
    QValidator *validator   = new QRegExpValidator(rx, this);
    QString     number      = checkAcc;
    QLineEdit  *temp        = new QLineEdit();
    temp->setText(checkAcc);
    temp->setValidator(validator);

    // Check if acc is empty, then check if it is neg
    if(temp->text() != "") {
        if(temp->text().toInt() >= 0) {
            number = QString("%1").arg(temp->text().toInt(), 3, 10, QChar('0'));
        }
        else {
            number = QString("%1").arg(temp->text().toInt(), 4, 10, QChar('0'));
        }
    }
    return number;
}

/**************************************************************************
 *  ValidateMemory - Validate Memory (-#### to ### -> 3 digit #)
 *************************************************************************/
void MainWindow::ValidateMemory(QString addr) {
    QRegExp     rx("-?\\d{0,3}");
    QValidator *validator   = new QRegExpValidator(rx, this);

    memLine = ui->MemoryBox->findChild<QLineEdit*>("memLineEdit" + addr);
    memLine->setValidator(validator);

    if(memLine->text() != "") {
        if(memLine->text().toInt() > 0) {
            QString number = QString("%1").arg(memLine->text().toInt(), 3, 10, QChar('0'));
            memLine->setText(number);
        }
        else {
            QString number = QString("%1").arg(memLine->text().toInt(), 4, 10, QChar('0'));
            memLine->setText(number);
        }
    }
}

/**************************************************************************
 *  ValidateInput - Validate Input (-#### to ### -> 3 digit #)
 *************************************************************************/
void MainWindow::ValidateInput(QString addr) {
    QRegExp     rx("-?\\d{0,3}");
    QValidator *validator   = new QRegExpValidator(rx, this);

    inputLine = ui->InputCards->findChild<QLineEdit*>("inputLineEdit" + addr);
    inputLine->setValidator(validator);

    if(inputLine->text() != "") {
        if(inputLine->text().toInt() > 0) {
            QString number = QString("%1").arg(inputLine->text().toInt(), 3, 10, QChar('0'));
            inputLine->setText(number);
        }
        else {
            QString number = QString("%1").arg(inputLine->text().toInt(), 4, 10, QChar('0'));
            inputLine->setText(number);
        }
    }
}

/**************************************************************************
 *  ValidateOutput - Checks is output # is formatted properly
 *  Return: QString
 *************************************************************************/
QString MainWindow::ValidateOutput(QString checkOut) {
    QString number = checkOut;
    if(checkOut != "") {
        if(checkOut.toInt() > 0)
            number = QString("%1").arg(checkOut.toInt(), 3, 10, QChar('0'));
        else
            number = QString("%1").arg(checkOut.toInt(), 4, 10, QChar('0'));
    }
    return number;
}

/**************************************************************************
 *  ValidatePC - Validate Program Counter (00 - 20)
 *************************************************************************/
QString MainWindow::ValidatePC(QString pc) {
    QRegExp     pcRx("\\d{0,2}");
    QValidator *pcValidator = new QRegExpValidator(pcRx, this);

    ui->pcLineEdit->setText(pc);
    ui->pcLineEdit->setValidator(pcValidator);

    if(ui->pcLineEdit->text().toInt() < 10) {
        QString num = QString("%1").arg(ui->pcLineEdit->text().toInt(), 2, 10, QChar('0'));
        ui->pcLineEdit->setText(num);
    }

    return ui->pcLineEdit->text();
}

/**************************************************************************
 *  on_clearInputBtn_clicked - Clear all input line edits
 *************************************************************************/
void MainWindow::on_clearInputBtn_clicked()
{
    foreach(QLineEdit* le, ui->InputCards->findChildren<QLineEdit*>())
        le->clear();
    inpCardNum = "01";
}

/**************************************************************************
 *  on_clearOutputBtn_clicked - Clear Output line edits
 *************************************************************************/
void MainWindow::on_clearOutputBtn_clicked()
{
    foreach(QLineEdit* le, ui->OutputCards->findChildren<QLineEdit*>())
        le->clear();
    outCardNum = "01";
}

/**************************************************************************
 *  on_clearAllBtn_clicked - Clear all line edits
 *************************************************************************/
void MainWindow::on_clearAllBtn_clicked()
{
    foreach(QLineEdit* le, findChildren<QLineEdit*>())
       le->clear();
    ui->memLineEdit00->setText("001");
    ui->pcLineEdit->setText("00");
    inpCardNum = "01";
    outCardNum = "01";
    startPC = ui->pcLineEdit->text();
}

/**************************************************************************
 *  on_clearCpuBtn_clicked - Clear CPU & set pc to 00
 *************************************************************************/
void MainWindow::on_clearCpuBtn_clicked()
{
    foreach(QLineEdit* le, ui->CPU->findChildren<QLineEdit*>())
        le->clear();
    ui->pcLineEdit->setText("00");
    startPC = ui->pcLineEdit->text();
}

/**************************************************************************
 *  on_clearMemBtn_clicked - Clear all memory edit lines
 *************************************************************************/
void MainWindow::on_clearMemBtn_clicked()
{
    foreach(QLineEdit* le, ui->MemoryBox->findChildren<QLineEdit*>())
        le->clear();
    ui->memLineEdit00->setText("001");
}

/**************************************************************************
 *  Initialize - Initialize pc, input card, and output card
 *************************************************************************/
void MainWindow::Initialize() {
    startPC    = ui->pcLineEdit->text();
    inpCardNum = "01";
    outCardNum = "01";
}

/**************************************************************************
 *  Reset - Reset the input and pc
 *************************************************************************/
void MainWindow::Reset() {
    startPC    = ui->pcLineEdit->text();
    inpCardNum = "01";
}

/**************************************************************************
 *  on_resetInputBtn_clicked - Reset the input and pc when btn clicked
 *************************************************************************/
void MainWindow::on_resetInputBtn_clicked()
{
    Reset();
}

/**************************************************************************
 *  on_runBtn_clicked - Run entire program
 *************************************************************************/
void MainWindow::on_runBtn_clicked()
{
    bool running   = true;
    bool validStep = true;

    // Keep running while steps are valid & memory isn't empty
    while(running && validStep) {
        if(IsMemEmpty()) {
            running = false;
        }
        else {
            validStep = OneStep();
            ui->irLineEdit->text().at(0) == '9' ? running = false : running = true;
        }
    }
}

/**************************************************************************
 *  IsMemEmpty - Check if memory is empty
 *  Return: bool
 *************************************************************************/
bool MainWindow::IsMemEmpty() {
    memLine = ui->MemoryBox->findChild<QLineEdit*>("memLineEdit" + startPC);
    if(memLine->text() == "") {
        QMessageBox::critical(this, "Execution Halted", "Execution Halted:\n Memory location being fetched is empty");
        return true;
    }
    return false;
}

/**************************************************************************
 *  IsInputEmpty - Check if input is empty
 *  Return: bool
 *************************************************************************/
bool MainWindow::IsInputEmpty() {
    inputLine = ui->InputCards->findChild<QLineEdit*>("inputLineEdit" + inpCardNum);
    if(inputLine->text() == "") {
        QMessageBox::warning(this, "Input Cards", "Input card empty!");
        return true;
    }
    return false;
}

/**************************************************************************
 *  on_stepBtn_clicked() - When Step btn clicked run one step
 *************************************************************************/
void MainWindow::on_stepBtn_clicked()
{
    OneStep();
}

/**************************************************************************
 *  OneStep - Executes one step of the program
 *  Return: valid (bool - Did the one step run properly or not)
 *************************************************************************/
bool MainWindow::OneStep() {
    bool valid = false;
    if(!IsMemEmpty()) {
        inReg = memLine->text();
        ui->irLineEdit->setText(inReg);

        // Update Program Counter
        startPC = ValidatePC(QString::number(startPC.toInt() + 1));

        // Execute the Instruction
        valid = SignExecute();
    }
    return valid;
}

/**************************************************************************
 *  SignExecute - Switch to appropriate opcode.
 *  Return: valid (bool - Executed properly or not)
 *************************************************************************/
bool MainWindow::SignExecute() {
    QString opcode  = inReg.at(0);
    QString address = inReg.right(2);
    bool valid = true;

    switch(opcode.toInt()) {
        case INP :  valid = Inp(address);
                    break;

        case OUT :  valid = Out(address);
                    break;

        case ADD :  Add(address);
                    break;

        case SUB :  Sub(address);
                    break;

        case LDA :  Lda(address);
                    break;

        case STA :  Sta(address);
                    break;

        case JMP :  Jmp(address);
                    break;

        case TAC :  Tac(address);
                    break;

        case SHF :  Shf(address);
                    break;

        case HLT :  Hlt(address);
                    break;

        default  :  break;
    }
    return valid;
}

/**************************************************************************
 *  Inp - Get input and store into appropriate memory cell
 *  Return: validInp (bool - valid input or not)
 *************************************************************************/
bool MainWindow::Inp(QString address) {
    bool validInp;
    if(inpCardNum.toInt() <= 15) {
        if(IsInputEmpty()) {
            validInp = false;
        }
        else {
            inputLine = ui->InputCards->findChild<QLineEdit*>("inputLineEdit" + inpCardNum);
            memLine = ui->MemoryBox->findChild<QLineEdit*>("memLineEdit" + address);
            memLine->setText(inputLine->text());
            inpCardNum = QString("%1").arg(inpCardNum.toInt() + 1, 2, 10, QChar('0'));
            validInp = true;
        }
    }
    else {
        QMessageBox::warning(this, "Input Cards", "No more input cards available!");
        validInp = false;
    }

    return validInp;
}

/**************************************************************************
 *  Out - Output number from memory cell desired
 *  Return: validOut (bool - valid output or not)
 *************************************************************************/
bool MainWindow::Out(QString address) {
    bool validOut;
    if(outCardNum.toInt() <= 15) {
          memLine = ui->MemoryBox->findChild<QLineEdit*>("memLineEdit" + address);
          outputLine = ui->OutputCards->findChild<QLineEdit*>("outputLineEdit" + outCardNum);
          QString outputStr = ValidateOutput(memLine->text());
          outputLine->setText(outputStr);
          outCardNum = QString("%1").arg(outCardNum.toInt() + 1, 2, 10, QChar('0'));
          validOut = true;
    }
    else {
        QMessageBox::warning(this, "Output Cards", "No more output cards available!");
        validOut = false;
    }
    return validOut;
}

/**************************************************************************
 *  Add - Add num to accumlator
 *************************************************************************/
void MainWindow::Add(QString address) {
    memLine = ui->MemoryBox->findChild<QLineEdit*>("memLineEdit" + address);
    QString sum = QString::number(memLine->text().toInt() + ui->acc->text().toInt());

    if(sum.toInt() > 999) {
        ui->acCarry->setText("1");
        sum = QString::number(sum.right(3).toInt() - 999);
        sum = ValidateAcc(sum);
        ui->acc->setText(sum);
    }
    else {
        if(sum.toInt() < -999) {
            ui->acCarry->setText("1");
            sum = QString::number(999 - sum.right(3).toInt());
            sum = ValidateAcc(sum);
            ui->acc->setText(sum);
        }
        else {
            ui->acCarry->setText("0");
            sum = ValidateAcc(sum);
            ui->acc->setText(sum);
        }
    }
}

/**************************************************************************
 *  Sub - Subtract num from acc and store back in accumulator
 *************************************************************************/
void MainWindow::Sub(QString address) {
    memLine = ui->MemoryBox->findChild<QLineEdit*>("memLineEdit" + address);
    QString diff = QString::number(ui->acc->text().toInt() - memLine->text().toInt());

    if(diff.toInt() > 999) {
        ui->acCarry->setText("1");
        diff = QString::number(diff.right(3).toInt() - 999);
        diff = ValidateAcc(diff);
        ui->acc->setText(diff);
    }
    else {
        if(diff.toInt() < -999) {
            ui->acCarry->setText("1");
            diff = QString::number(999 - diff.right(3).toInt());
            diff = ValidateAcc(diff);
            ui->acc->setText(diff);
        }
        else {
            ui->acCarry->setText("0");
            diff = ValidateAcc(diff);
            ui->acc->setText(diff);
        }
    }
}

/**************************************************************************
 *  Lda - Load accumulator from a memory cell
 *************************************************************************/
void MainWindow::Lda(QString address) {
    memLine = ui->MemoryBox->findChild<QLineEdit*>("memLineEdit" + address);
    memLine->text() = ValidateAcc(memLine->text());
    ui->acc->setText(memLine->text());

    if(memLine->text().toInt() >= -999 && memLine->text().toInt() <= 999) {
        ui->acCarry->setText("0");
    }
    else {
        ui->acCarry->setText("1");
    }
}

/**************************************************************************
 *  Sta - Store number in accumulator into memory cell
 *************************************************************************/
void MainWindow::Sta(QString address) {
    memLine = ui->MemoryBox->findChild<QLineEdit*>("memLineEdit" + address);
    memLine->setText(ui->acc->text());
}

/**************************************************************************
 *  Jmp - Jmp to address provided. Store old address in cell 99
 *************************************************************************/
void MainWindow::Jmp(QString address) {
    QString jmpAddr = QString("%1").arg(startPC.toInt(), 3, 10, QChar('0'));
    ui->memLineEdit99->setText(jmpAddr);
    startPC = address;
    ui->pcLineEdit->setText(address);
}

/**************************************************************************
 *  Tac - Tests accumulator if neg
 *************************************************************************/
void MainWindow::Tac(QString address) {
    if(ui->acc->text().toInt() < 0) {
        startPC = address;
        ui->pcLineEdit->setText(address);
    }
}

/**************************************************************************
 *  Shf - Shifts number in accumulator
 *************************************************************************/
void MainWindow::Shf(QString xyShift) {
    QString xLeft  = xyShift.at(0);
    QString yRight = xyShift.at(1);
    QString acc1;
    QString acc2;
    QString acc3;
    QString index;
    QString shiftedNum;
    bool    neg;

    if(xLeft.toInt() != 0) {
        index = xLeft;
        if(ui->acc->text().toInt() < 0) {
            ui->acc->setText(ui->acc->text().right(3));
            neg = true;
        }
        else {
            neg = false;
        }

        if(xLeft.toInt() < 4)
            ui->acCarry->setText(ui->acc->text().at(index.toInt() - 1));
        else
            ui->acCarry->setText("0");

        xLeft.toInt() < 3 ? acc1 = ui->acc->text().at(index.toInt()) : acc1 = "0";
        xLeft.toInt() < 2 ? acc2 = ui->acc->text().at(index.toInt() + 1) : acc2 = "0";
        acc3 = "0";

        shiftedNum = acc1 + acc2 + acc3;

        if(neg && shiftedNum != "000")
            shiftedNum = "-" + acc1 + acc2 + acc3;

        ui->acc->setText(shiftedNum);
    }

    if(yRight.toInt() != 0) {
        index = QString::number(3 - yRight.toInt());

        if(ui->acc->text().toInt() < 0) {
            ui->acc->setText(ui->acc->text().right(3));
            neg = true;
        }
        else {
            neg = false;
        }

        yRight.toInt() < 3 ? acc3 = ui->acc->text().at(index.toInt() -1)
                : (yRight.toInt() == 3 ? acc3 = ui->acCarry->text() : acc3 = "0");
        yRight.toInt() < 2 ? acc2 = ui->acc->text().at(index.toInt() - 2)
                : (yRight.toInt() == 2 ? acc2 = ui->acCarry->text() : acc2 = "0");
        yRight.toInt() < 2 ? acc1 = ui->acCarry->text() : acc1 = "0";
        ui->acCarry->setText("0");

        shiftedNum = acc1 + acc2 + acc3;

        if(neg && shiftedNum != "000")
            shiftedNum = "-" + acc1 + acc2 + acc3;

        ui->acc->setText(shiftedNum);
    }
}

/**************************************************************************
 *  Hlt - Halts Program
 *************************************************************************/
void MainWindow::Hlt(QString address) {
    ui->pcLineEdit->setText(address.right(2));
    Reset();
    QMessageBox::information(this, "Program", "Program terminated normally");
}

/**************************************************************************
 *  Validate Memory/Input/PC after line edit finished
 *************************************************************************/
void MainWindow::on_memLineEdit00_editingFinished()
{
    ValidateMemory("00");
}

void MainWindow::on_memLineEdit01_editingFinished()
{
    ValidateMemory("01");
}

void MainWindow::on_memLineEdit02_editingFinished()
{
    ValidateMemory("02");
}

void MainWindow::on_memLineEdit03_editingFinished()
{
    ValidateMemory("03");
}

void MainWindow::on_memLineEdit04_editingFinished()
{
    ValidateMemory("04");
}

void MainWindow::on_memLineEdit05_editingFinished()
{
    ValidateMemory("05");
}

void MainWindow::on_memLineEdit06_editingFinished()
{
    ValidateMemory("06");
}

void MainWindow::on_memLineEdit07_editingFinished()
{
    ValidateMemory("07");
}

void MainWindow::on_memLineEdit08_editingFinished()
{
    ValidateMemory("08");
}

void MainWindow::on_memLineEdit09_editingFinished()
{
    ValidateMemory("09");
}

void MainWindow::on_memLineEdit10_editingFinished()
{
    ValidateMemory("10");
}

void MainWindow::on_memLineEdit11_editingFinished()
{
    ValidateMemory("11");
}

void MainWindow::on_memLineEdit12_editingFinished()
{
    ValidateMemory("12");
}

void MainWindow::on_memLineEdit13_editingFinished()
{
    ValidateMemory("13");
}

void MainWindow::on_memLineEdit14_editingFinished()
{
    ValidateMemory("14");
}

void MainWindow::on_memLineEdit15_editingFinished()
{
    ValidateMemory("15");
}

void MainWindow::on_memLineEdit16_editingFinished()
{
    ValidateMemory("16");
}

void MainWindow::on_memLineEdit17_editingFinished()
{
    ValidateMemory("17");
}

void MainWindow::on_memLineEdit18_editingFinished()
{
    ValidateMemory("18");
}

void MainWindow::on_memLineEdit19_editingFinished()
{
    ValidateMemory("19");
}

void MainWindow::on_memLineEdit20_editingFinished()
{
    ValidateMemory("20");
}

void MainWindow::on_memLineEdit21_editingFinished()
{
    ValidateMemory("21");
}

void MainWindow::on_memLineEdit22_editingFinished()
{
    ValidateMemory("22");
}

void MainWindow::on_memLineEdit23_editingFinished()
{
    ValidateMemory("23");
}

void MainWindow::on_memLineEdit24_editingFinished()
{
    ValidateMemory("24");
}

void MainWindow::on_memLineEdit25_editingFinished()
{
    ValidateMemory("25");
}

void MainWindow::on_memLineEdit26_editingFinished()
{
    ValidateMemory("26");
}

void MainWindow::on_memLineEdit27_editingFinished()
{
    ValidateMemory("27");
}

void MainWindow::on_memLineEdit28_editingFinished()
{
    ValidateMemory("28");
}

void MainWindow::on_memLineEdit29_editingFinished()
{
    ValidateMemory("29");
}

void MainWindow::on_memLineEdit30_editingFinished()
{
    ValidateMemory("30");
}

void MainWindow::on_memLineEdit31_editingFinished()
{
    ValidateMemory("31");
}

void MainWindow::on_memLineEdit32_editingFinished()
{
    ValidateMemory("32");
}

void MainWindow::on_memLineEdit33_editingFinished()
{
    ValidateMemory("33");
}

void MainWindow::on_memLineEdit34_editingFinished()
{
    ValidateMemory("34");
}

void MainWindow::on_memLineEdit35_editingFinished()
{
    ValidateMemory("35");
}

void MainWindow::on_memLineEdit36_editingFinished()
{
    ValidateMemory("36");
}

void MainWindow::on_memLineEdit37_editingFinished()
{
    ValidateMemory("37");
}

void MainWindow::on_memLineEdit38_editingFinished()
{
    ValidateMemory("38");
}

void MainWindow::on_memLineEdit39_editingFinished()
{
    ValidateMemory("39");
}

void MainWindow::on_memLineEdit40_editingFinished()
{
    ValidateMemory("40");
}

void MainWindow::on_memLineEdit41_editingFinished()
{
    ValidateMemory("41");
}

void MainWindow::on_memLineEdit42_editingFinished()
{
    ValidateMemory("42");
}

void MainWindow::on_memLineEdit43_editingFinished()
{
    ValidateMemory("43");
}

void MainWindow::on_memLineEdit44_editingFinished()
{
    ValidateMemory("44");
}

void MainWindow::on_memLineEdit45_editingFinished()
{
    ValidateMemory("45");
}

void MainWindow::on_memLineEdit46_editingFinished()
{
    ValidateMemory("46");
}

void MainWindow::on_memLineEdit47_editingFinished()
{
    ValidateMemory("47");
}

void MainWindow::on_memLineEdit48_editingFinished()
{
    ValidateMemory("48");
}

void MainWindow::on_memLineEdit49_editingFinished()
{
    ValidateMemory("49");
}

void MainWindow::on_memLineEdit50_editingFinished()
{
    ValidateMemory("50");
}

void MainWindow::on_memLineEdit51_editingFinished()
{
    ValidateMemory("51");
}

void MainWindow::on_memLineEdit52_editingFinished()
{
    ValidateMemory("52");
}

void MainWindow::on_memLineEdit53_editingFinished()
{
    ValidateMemory("53");
}

void MainWindow::on_memLineEdit54_editingFinished()
{
    ValidateMemory("54");
}

void MainWindow::on_memLineEdit55_editingFinished()
{
    ValidateMemory("55");
}

void MainWindow::on_memLineEdit56_editingFinished()
{
    ValidateMemory("56");
}

void MainWindow::on_memLineEdit57_editingFinished()
{
    ValidateMemory("57");
}

void MainWindow::on_memLineEdit58_editingFinished()
{
    ValidateMemory("58");
}

void MainWindow::on_memLineEdit59_editingFinished()
{
    ValidateMemory("59");
}

void MainWindow::on_memLineEdit60_editingFinished()
{
    ValidateMemory("60");
}

void MainWindow::on_memLineEdit61_editingFinished()
{
    ValidateMemory("61");
}

void MainWindow::on_memLineEdit62_editingFinished()
{
    ValidateMemory("62");
}

void MainWindow::on_memLineEdit63_editingFinished()
{
    ValidateMemory("63");
}

void MainWindow::on_memLineEdit64_editingFinished()
{
    ValidateMemory("64");
}

void MainWindow::on_memLineEdit65_editingFinished()
{
    ValidateMemory("65");
}

void MainWindow::on_memLineEdit66_editingFinished()
{
    ValidateMemory("66");
}

void MainWindow::on_memLineEdit67_editingFinished()
{
    ValidateMemory("67");
}

void MainWindow::on_memLineEdit68_editingFinished()
{
    ValidateMemory("68");
}

void MainWindow::on_memLineEdit69_editingFinished()
{
    ValidateMemory("69");
}

void MainWindow::on_memLineEdit70_editingFinished()
{
    ValidateMemory("70");
}

void MainWindow::on_memLineEdit71_editingFinished()
{
    ValidateMemory("71");
}

void MainWindow::on_memLineEdit72_editingFinished()
{
    ValidateMemory("72");
}

void MainWindow::on_memLineEdit73_editingFinished()
{
    ValidateMemory("73");
}

void MainWindow::on_memLineEdit74_editingFinished()
{
    ValidateMemory("74");
}

void MainWindow::on_memLineEdit75_editingFinished()
{
    ValidateMemory("75");
}

void MainWindow::on_memLineEdit76_editingFinished()
{
    ValidateMemory("76");
}

void MainWindow::on_memLineEdit77_editingFinished()
{
    ValidateMemory("77");
}

void MainWindow::on_memLineEdit78_editingFinished()
{
    ValidateMemory("78");
}

void MainWindow::on_memLineEdit79_editingFinished()
{
    ValidateMemory("79");
}

void MainWindow::on_memLineEdit80_editingFinished()
{
    ValidateMemory("80");
}

void MainWindow::on_memLineEdit81_editingFinished()
{
    ValidateMemory("81");
}

void MainWindow::on_memLineEdit82_editingFinished()
{
    ValidateMemory("82");
}

void MainWindow::on_memLineEdit83_editingFinished()
{
    ValidateMemory("83");
}

void MainWindow::on_memLineEdit84_editingFinished()
{
    ValidateMemory("84");
}

void MainWindow::on_memLineEdit85_editingFinished()
{
    ValidateMemory("85");
}

void MainWindow::on_memLineEdit86_editingFinished()
{
    ValidateMemory("86");
}

void MainWindow::on_memLineEdit87_editingFinished()
{
    ValidateMemory("87");
}

void MainWindow::on_memLineEdit88_editingFinished()
{
    ValidateMemory("88");
}

void MainWindow::on_memLineEdit89_editingFinished()
{
    ValidateMemory("89");
}

void MainWindow::on_memLineEdit90_editingFinished()
{
    ValidateMemory("90");
}

void MainWindow::on_memLineEdit91_editingFinished()
{
    ValidateMemory("91");
}

void MainWindow::on_memLineEdit92_editingFinished()
{
    ValidateMemory("92");
}

void MainWindow::on_memLineEdit93_editingFinished()
{
    ValidateMemory("93");
}

void MainWindow::on_memLineEdit94_editingFinished()
{
    ValidateMemory("94");
}

void MainWindow::on_memLineEdit95_editingFinished()
{
    ValidateMemory("95");
}

void MainWindow::on_memLineEdit96_editingFinished()
{
    ValidateMemory("96");
}

void MainWindow::on_memLineEdit97_editingFinished()
{
    ValidateMemory("97");
}

void MainWindow::on_memLineEdit98_editingFinished()
{
    ValidateMemory("98");
}

void MainWindow::on_memLineEdit99_editingFinished()
{
    ValidateMemory("99");
}

void MainWindow::on_pcLineEdit_textEdited(const QString &arg1)
{
    ui->pcLineEdit->setText(arg1);
    startPC = ui->pcLineEdit->text();
}

void MainWindow::on_inputLineEdit01_editingFinished()
{
    ValidateInput("01");
}

void MainWindow::on_inputLineEdit02_editingFinished()
{
    ValidateInput("02");
}

void MainWindow::on_inputLineEdit03_editingFinished()
{
    ValidateInput("03");
}

void MainWindow::on_inputLineEdit04_editingFinished()
{
    ValidateInput("04");
}

void MainWindow::on_inputLineEdit05_editingFinished()
{
    ValidateInput("05");
}

void MainWindow::on_inputLineEdit06_editingFinished()
{
    ValidateInput("06");
}

void MainWindow::on_inputLineEdit07_editingFinished()
{
    ValidateInput("07");
}

void MainWindow::on_inputLineEdit08_editingFinished()
{
    ValidateInput("08");
}

void MainWindow::on_inputLineEdit09_editingFinished()
{
    ValidateInput("09");
}

void MainWindow::on_inputLineEdit10_editingFinished()
{
    ValidateInput("10");
}

void MainWindow::on_inputLineEdit11_editingFinished()
{
    ValidateInput("11");
}

void MainWindow::on_inputLineEdit12_editingFinished()
{
    ValidateInput("12");
}

void MainWindow::on_inputLineEdit13_editingFinished()
{
    ValidateInput("13");
}

void MainWindow::on_inputLineEdit14_editingFinished()
{
    ValidateInput("14");
}

void MainWindow::on_inputLineEdit15_editingFinished()
{
    ValidateInput("15");
}
