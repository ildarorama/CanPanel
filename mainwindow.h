#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "message.pb.h"
#include "codeitem.h"
#include "zmqworkerthread.h"
#include "telemetrybean.h"
#include <QMainWindow>
#include <QtNetwork/QNetworkReply>
#include <boost/thread.hpp>
#include <boost/lockfree/queue.hpp>
#include <vector>
#include <string>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    bool eventFilter(QObject *,QEvent*);
    ~MainWindow();
    int zmq_routine();
private slots:
    void on_setupThree_clicked(const QModelIndex &index);
    void sendButtonSlot(bool);
    void showSelectCodeDialog();

    void on_deviceTypeTree_clicked(const QModelIndex &index);

    void on_pushButton_19_clicked();
    void onRefreshTelemetry(TelemetryBean state);
    void on_tabWidget_currentChanged(int index);
    void on_pushButton_15_clicked();
    void onConfigRefreshed(std::string config);

private:
    Ui::MainWindow *ui;    
    std::vector<CodeItem> codes;
    void fillTestPanel();
    ZmqWorkerThread worker;
signals:
    void callSelectCodeDialog();
};

#endif // MAINWINDOW_H
