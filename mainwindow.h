#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "receipt.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    Receipt add();
    ~MainWindow();

private slots:
    void on_addNode_clicked();

    void on_openFile_clicked();

    void on_saveToFile_clicked();

    void on_addBegin_clicked();

    void on_addEnd_clicked();

    void on_deleteBegin_clicked();

    void on_deleteEnd_clicked();

    void on_nodeSearch_clicked();

    void on_deleteByName_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
