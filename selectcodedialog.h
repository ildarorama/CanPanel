#ifndef SELECTCODEDIALOG_H
#define SELECTCODEDIALOG_H

#include "codeitem.h"
#include <vector>
#include <QDialog>
#include <QListWidgetItem>

namespace Ui {
class SelectCodeDialog;
}

class SelectCodeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SelectCodeDialog(std::vector<CodeItem> * codes,QWidget *parent = 0);
    ~SelectCodeDialog();
    int selectedCode();

private slots:
    void on_lstCodeList_itemChanged(QListWidgetItem *item);

private:
    Ui::SelectCodeDialog *ui;
    std::vector<CodeItem> * _codes;
    int _selectedCode=-1;
};

#endif // SELECTCODEDIALOG_H
