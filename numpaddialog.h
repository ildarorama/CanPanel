#ifndef NUMPADDIALOG_H
#define NUMPADDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <functional>

namespace Ui {
class NumpadDialog;
}

class NumpadDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NumpadDialog(QWidget *parent = 0);
    void setLineEdit(std::function<void (QString)>);
    ~NumpadDialog();
private slots:
    void on_number_push();
private:
    std::function<void (QString)> _listener;
    Ui::NumpadDialog *ui;
};

#endif // NUMPADDIALOG_H
