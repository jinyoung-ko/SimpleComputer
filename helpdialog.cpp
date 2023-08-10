#include "helpdialog.h"
#include "ui_helpdialog.h"

// Help Dialog Box
HelpDialog::HelpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HelpDialog)
{
    ui->setupUi(this);
}

// Destroy Help Dialog Box
HelpDialog::~HelpDialog()
{
    delete ui;
}

// Ok btn - Close Help Dialog Box
void HelpDialog::on_okBtn_clicked()
{
    close();
}
