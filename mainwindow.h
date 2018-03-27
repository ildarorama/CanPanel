#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
private slots:
    void on_setupThree_clicked(const QModelIndex &index);

    void on_pushButton_15_clicked();

    void on_deviceTypeTree_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    void fillTestPanel();
};

#endif // MAINWINDOW_H
