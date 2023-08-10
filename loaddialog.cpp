#include "loaddialog.h"
#include "ui_loaddialog.h"
#include <QDebug>
#include <QFileDialog>

// Main
LoadDialog::LoadDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoadDialog)
{
    this->setFixedSize(412, 312);
    ui->setupUi(this);
}

// Destroy
LoadDialog::~LoadDialog()
{
    delete ui;
}

// Get File Name
QString LoadDialog::GetFileName() const {
    return fileName;
}

// Cancel Load Dialog Box
void LoadDialog::on_cancelBtn_clicked()
{
    close();
}

// Ok Btn - Get file
void LoadDialog::on_okBtn_clicked()
{
    // Get file name according to radio button
    foreach(QRadioButton* le, findChildren<QRadioButton*>()) {
        if(le->isChecked()) {
            if(le->text() != "Use My Own File")
                fileName = ":/ProgramFiles/" + le->text() + ".txt";
            break;
        }
    }
    close();
}

// Choose file btn - Get own file
void LoadDialog::on_chooseFileBtn_clicked()
{
    // Get file from user
    ui->ownFileBtn->setChecked(true);
    fileName = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "C://",
                "All Files (*.*);;Text File (*.txt);;"
                );
    ui->fileNameLineEdit->setText(fileName);
}
