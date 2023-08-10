#ifndef LOADDIALOG_H
#define LOADDIALOG_H

#include <QDialog>

namespace Ui {
class LoadDialog;
}

class LoadDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoadDialog(QWidget *parent = 0);
    QString GetFileName() const;
    ~LoadDialog();

private slots:
    void on_cancelBtn_clicked();
    void on_okBtn_clicked();
    void on_chooseFileBtn_clicked();

private:
    Ui::LoadDialog *ui;
    QString fileName;
};

#endif // LOADDIALOG_H
