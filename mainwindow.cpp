#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "numpaddialog.h"
#include "numpaddialog.h"
#include "passworddialog.h"
#include "selectcodedialog.h"
#include <iostream>
#include <QDebug>
#include <boost/property_tree/ptree.hpp>

#include <zmq/zmq.hpp>
#include "message.pb.h"
#include "zmqworkerthread.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->btnProg1,SIGNAL(clicked(bool)),this,SLOT(sendButtonSlot(bool)));
    connect(ui->btnProg2,SIGNAL(clicked(bool)),this,SLOT(sendButtonSlot(bool)));
    connect(ui->btnProg3,SIGNAL(clicked(bool)),this,SLOT(sendButtonSlot(bool)));
    connect(ui->btnProg4,SIGNAL(clicked(bool)),this,SLOT(sendButtonSlot(bool)));
    connect(ui->btnProg5,SIGNAL(clicked(bool)),this,SLOT(sendButtonSlot(bool)));
    connect(ui->btnProg6,SIGNAL(clicked(bool)),this,SLOT(sendButtonSlot(bool)));
    connect(ui->btnRelX,SIGNAL(clicked(bool)),this,SLOT(sendButtonSlot(bool)));
    connect(ui->btnRelY,SIGNAL(clicked(bool)),this,SLOT(sendButtonSlot(bool)));
    connect(ui->btnRelZ,SIGNAL(clicked(bool)),this,SLOT(sendButtonSlot(bool)));
    connect(ui->btnRelA,SIGNAL(clicked(bool)),this,SLOT(sendButtonSlot(bool)));
    connect(ui->btnRelB,SIGNAL(clicked(bool)),this,SLOT(sendButtonSlot(bool)));
    connect(ui->btnRelC,SIGNAL(clicked(bool)),this,SLOT(sendButtonSlot(bool)));
    connect(ui->btnResetX,SIGNAL(clicked(bool)),this,SLOT(sendButtonSlot(bool)));
    connect(ui->btnResetY,SIGNAL(clicked(bool)),this,SLOT(sendButtonSlot(bool)));
    connect(ui->btnResetZ,SIGNAL(clicked(bool)),this,SLOT(sendButtonSlot(bool)));
    connect(ui->btnResetA,SIGNAL(clicked(bool)),this,SLOT(sendButtonSlot(bool)));
    connect(ui->btnResetB,SIGNAL(clicked(bool)),this,SLOT(sendButtonSlot(bool)));
    connect(ui->btnResetC,SIGNAL(clicked(bool)),this,SLOT(sendButtonSlot(bool)));

    connect(ui->btnRotationOn,SIGNAL(clicked(bool)),this,SLOT(sendButtonSlot(bool)));
    connect(ui->btnRotationCW,SIGNAL(clicked(bool)),this,SLOT(sendButtonSlot(bool)));
    connect(ui->btnRotationCCW,SIGNAL(clicked(bool)),this,SLOT(sendButtonSlot(bool)));

    connect(ui->btnUnits,SIGNAL(clicked(bool)),this,SLOT(sendButtonSlot(bool)));
    connect(ui->btnRelation,SIGNAL(clicked(bool)),this,SLOT(sendButtonSlot(bool)));
    connect(ui->btnFuctures,SIGNAL(clicked(bool)),this,SLOT(sendButtonSlot(bool)));
    connect(ui->btnStopFeed,SIGNAL(clicked(bool)),this,SLOT(sendButtonSlot(bool)));
    connect(ui->btnSimulation,SIGNAL(clicked(bool)),this,SLOT(sendButtonSlot(bool)));
    connect(ui->btnRestart,SIGNAL(clicked(bool)),this,SLOT(sendButtonSlot(bool)));
    connect(ui->btnPause,SIGNAL(clicked(bool)),this,SLOT(sendButtonSlot(bool)));
    connect(ui->btnOneStep,SIGNAL(clicked(bool)),this,SLOT(sendButtonSlot(bool)));
    connect(ui->btnCicle,SIGNAL(clicked(bool)),this,SLOT(sendButtonSlot(bool)));

    connect(ui->btnIgnoreComment,SIGNAL(clicked(bool)),this,SLOT(sendButtonSlot(bool)));


    connect(&worker,SIGNAL(refreshConfig(std::string config)),this,SLOT(onConfigRefreshed(std::string)));
    connect(&worker,SIGNAL(refreshTelemetry(TelemetryBean)),this,SLOT(onRefreshTelemetry(TelemetryBean)));

    //connect(this,SIGNAL(callSelectCodeDialog()),this,SLOT(showSelectCodeDialog()));



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
    qDebug() << "Starting zmq thread ";
    worker.start();
}

void MainWindow::onConfigRefreshed(std::string config) {
    std::cout << "Received new config: " << config << std::endl;
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
    return true;
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

void MainWindow::on_pushButton_15_clicked() {
    PasswordDialog* dialog=new PasswordDialog(this);
    dialog->setAttribute(Qt::WA_DeleteOnClose,true);
    dialog->show();
}

void MainWindow::on_deviceTypeTree_clicked(const QModelIndex &index) {
    ui->deviceTypeTree->expand(index);
}

void MainWindow::showSelectCodeDialog() {
    SelectCodeDialog* dialog=new SelectCodeDialog(&codes,this);
    dialog->setAttribute(Qt::WA_DeleteOnClose,true);
    dialog->show();
    if ( dialog->result() == QDialog::DialogCode::Accepted) {
        qDebug() << "Code index " << dialog->selectedCode();
    }
}

void MainWindow::sendButtonSlot(bool state) {
     QObject * sender=QObject::sender();
     Telemetry *t=new Telemetry();
     t->set_type(RequestType::PushButtonRequest);
     t->mutable_pushbutton()->set_name(sender->objectName().toStdString());
     t->mutable_pushbutton()->set_state(state);
     worker.sendPacket(t);

     if ( sender->objectName() == "btnUnits" ) {
         QPushButton *b=(QPushButton *) sender;
         b->setText(state?"mm":"inch");
     }

     if ( sender->objectName() == "btnRelation" ) {
         QPushButton *b=(QPushButton *) sender;
         b->setText(state?"rel":"abs");
     }
}

void MainWindow::onRefreshTelemetry(TelemetryBean state) {
    qDebug() << "update value";
    ui->lcdCoordX->display(state.x());
    ui->lcdCoordY->display(state.y());
    ui->lcdCoordZ->display(state.z());
    ui->lcdCoordA->display(state.a());
    ui->lcdCoordB->display(state.b());
    ui->lcdCoordC->display(state.c());
}

void MainWindow::on_pushButton_19_clicked()
{
    Telemetry *t=new Telemetry();
    t->set_type(RequestType::CodeListRequest);
    worker.sendPacket(t);
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    if ( index == 1 ) {
        Telemetry *t=new Telemetry();
        t->set_type(RequestType::ConfigRequest);
        worker.sendPacket(t);
    }
}
