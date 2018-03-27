#include "numpaddialog.h"
#include "ui_numpaddialog.h"

NumpadDialog::NumpadDialog(QWidget *parent) :
    QDialog(parent),

    ui(new Ui::NumpadDialog)
{
    ui->setupUi(this);

    const QList<QPushButton*> items = ui->centralWidget->findChildren<QPushButton*>();
    for (QPushButton *btn : items) {
        connect(btn,SIGNAL(clicked()),this,SLOT(on_number_push()));
    }
}

void NumpadDialog::setLineEdit(std::function<void (QString)> listener) {
    _listener=listener;
}

NumpadDialog::~NumpadDialog()
{
    delete ui;
}

void NumpadDialog::on_number_push()
{
    QObject * sender=QObject::sender();

    QString str=ui->lineEdit->text();
    if (sender==ui->pushButton) str.append('1');
    if (sender==ui->pushButton_2) str.append('2');
    if (sender==ui->pushButton_3) str.append('3');
    if (sender==ui->pushButton_4) str.append('4');
    if (sender==ui->pushButton_5) str.append('5');
    if (sender==ui->pushButton_6) str.append('6');
    if (sender==ui->pushButton_7) str.append('7');
    if (sender==ui->pushButton_8) str.append('8');
    if (sender==ui->pushButton_9) str.append('9');
    if (sender==ui->pushButton_11) str.append('0');
    if (sender==ui->pushButton_17) str.clear();
    if (sender==ui->pushButton_15) {
        if (str.size() > 0 && str.indexOf('.')==-1) {
            str.append(".");
        }
    }
    if (sender==ui->pushButton_12) {
        if (str.size()>0) {
            str.remove(str.size()-1,1);
        }
    }
    if (sender==ui->pushButton_14) {
        if (str.size()>0) {
            if (str.at(0)=='-') {
                str.remove(0,1);
            } else {
                str.insert(0,'-');
            }
        }
    }
    if (sender==ui->pushButton_13 || sender==ui->pushButton_16) {
        if ( sender==ui->pushButton_13 ) _listener(str);
        this->hide();
        this->deleteLater();
    }
    ui->lineEdit->setText(str);
}
