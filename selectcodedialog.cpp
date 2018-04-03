#include "selectcodedialog.h"
#include "ui_selectcodedialog.h"

SelectCodeDialog::SelectCodeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectCodeDialog)
{
    ui->setupUi(this);
}

SelectCodeDialog::~SelectCodeDialog()
{
    delete ui;
}
