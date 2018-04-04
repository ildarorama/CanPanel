#include "selectcodedialog.h"
#include "ui_selectcodedialog.h"


SelectCodeDialog::SelectCodeDialog(std::vector<CodeItem> * codes, QWidget *parent) :
    QDialog(parent),    
    ui(new Ui::SelectCodeDialog),
    _codes(codes)
{
    ui->setupUi(this);

    std::vector<CodeItem>::iterator it=codes->begin();

    while( it != codes->end() ) {
        ui->lstCodeList->addItem(QString::fromStdString(it->name()));
        it++;
    }

}

SelectCodeDialog::~SelectCodeDialog()
{
    delete ui;
}

void SelectCodeDialog::on_lstCodeList_itemChanged(QListWidgetItem *item)
{
    _selectedCode = ui->lstCodeList->currentRow();
}


int SelectCodeDialog::selectedCode() {
    return _selectedCode;
}

