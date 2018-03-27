#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "numpaddialog.h"
#include "numpaddialog.h"
#include "passworddialog.h"
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    const QList<QLineEdit*> lineEdits = ui->centralWidget->findChildren<QLineEdit*>();
    for (QLineEdit *lineEdit : lineEdits) {
        lineEdit->installEventFilter(this);
    }

    ui->tableFieldOffset->installEventFilter(this);

    ui->gCodeTable->setRowCount(3);
    ui->gCodeTable->model()->setData(ui->gCodeTable->model()->index(0,0),"G94");
    ui->gCodeTable->model()->setData(ui->gCodeTable->model()->index(1,0),"G2 23.2 232.43 34.232");
    ui->gCodeTable->model()->setData(ui->gCodeTable->model()->index(2,0),"M0 1");
    ui->gCodeTable->model()->setData(ui->gCodeTable->model()->index(3,0),"G34 232 232.23");
    ui->gCodeTable->model()->setData(ui->gCodeTable->model()->index(4,0),"M2 1 2");

    ui->deviceTypeTree->setExpandsOnDoubleClick(false);


    fillTestPanel();

}

void MainWindow::fillTestPanel() {
    QGridLayout * l=(QGridLayout *)ui->pnlTest->layout();

    { //Clear panel
        QLayoutItem *it;
        while( (it=l->takeAt(0)) != nullptr ) {
            l->removeWidget(it->widget());
            l->removeItem(it);
            delete it->widget();
            delete it;
        }
    }

    int col=0;
    int row=0;
    for(int i=0;i<32;i++) {

        //QWidget *w=new QPushButton("Выход "+QString::number(i));

        QWidget *w=new QCheckBox(" "+QString::number(i));


        l->addWidget(w,row,col);
        if ( ++col >4 ) { col=0; row++; }
    }


    ui->pnlTest->adjustSize();
}

bool MainWindow::eventFilter(QObject *o,QEvent*e) {

    if (o==ui->tableFieldOffset) {
        if (e->type() == QEvent::FocusAboutToChange) {
            NumpadDialog* dialog=new NumpadDialog(this);


            QTableWidgetItem *itab=new QTableWidgetItem;
            ui->tableFieldOffset->setItem(ui->tableFieldOffset->currentRow(), ui->tableFieldOffset->currentColumn(), itab);

            dialog->setLineEdit([itab](QString s) -> void {
                itab->setText(s);
            });

            dialog->setAttribute(Qt::WA_DeleteOnClose,true);
            dialog->show();
        }
        return false;
    }


    if (e->type() == QEvent::MouseButtonPress) {
        NumpadDialog* dialog=new NumpadDialog(this);
        QLineEdit* line=(QLineEdit*)o;

        dialog->setLineEdit([line](QString s) -> void { line->setText(s); });
        dialog->setAttribute(Qt::WA_DeleteOnClose,true);
        dialog->show();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_setupThree_clicked(const QModelIndex &index)
{
    if ( index.data() == "Field Offset") {
        ui->stackedWidget->setCurrentIndex(1);
    }
    if ( index.data() == "Global") {
        ui->stackedWidget->setCurrentIndex(2);
    }

    if ( index.data() == "Axis") {
        ui->setupThree->expand(index);
    }

    if ( index.data() == "Config") {
        ui->stackedWidget->setCurrentIndex(4);
    }


    if ( index.data() == "Aliases") {
        ui->stackedWidget->setCurrentIndex(3);
    }

    if ( index.parent().data() == "Axis" ) {
        ui->stackedWidget->setCurrentIndex(0);
        QString s=index.data().toString();
        ui->axisSetupGroup->setTitle("Axis Setup " + s);
    }
}

void MainWindow::on_pushButton_15_clicked()
{
    PasswordDialog* dialog=new PasswordDialog(this);
    dialog->setAttribute(Qt::WA_DeleteOnClose,true);
    dialog->show();
}

void MainWindow::on_deviceTypeTree_clicked(const QModelIndex &index)
{
    ui->deviceTypeTree->expand(index);
}
