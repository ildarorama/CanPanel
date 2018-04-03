#ifndef SELECTCODEDIALOG_H
#define SELECTCODEDIALOG_H

#include <QDialog>

namespace Ui {
class SelectCodeDialog;
}

class SelectCodeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SelectCodeDialog(QWidget *parent = 0);
    ~SelectCodeDialog();

private:
    Ui::SelectCodeDialog *ui;
};

#endif // SELECTCODEDIALOG_H
