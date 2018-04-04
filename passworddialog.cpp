#include "passworddialog.h"
#include "numpaddialog.h"
#include "ui_passworddialog.h"

PasswordDialog::PasswordDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PasswordDialog)
{
    ui->setupUi(this);
    ui->passwordField->installEventFilter(this);
}

bool PasswordDialog::eventFilter(QObject *o,QEvent*e) {
    if (e->type() == QEvent::MouseButtonPress) {
        NumpadDialog* dialog=new NumpadDialog(this);
        QLineEdit* line=(QLineEdit*)o;

        dialog->setLineEdit([line](QString s) -> void { line->setText(s); });
        dialog->setAttribute(Qt::WA_DeleteOnClose,true);
        dialog->show();
        dialog->accept();
    }
    return true;
}

PasswordDialog::~PasswordDialog()
{
    delete ui;
}
