#ifndef TABLEWORK_H
#define TABLEWORK_H

#include <QMainWindow>
#include <QTableWidget>
#include "./ui_mainwindow.h"
#include "receipt.h"

class TableWork : public QMainWindow
{
    Q_OBJECT
public:
    TableWork(QWidget *parent = nullptr);
    void TableCreate(Receipt a);
private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // TABLEWORK_H
