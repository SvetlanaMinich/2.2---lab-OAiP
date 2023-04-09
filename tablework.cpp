#include "tablework.h"

TableWork::TableWork(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void TableWork::TableCreate(Receipt a)
{
    ui->listOfReceipts->setColumnCount(3);
    ui->listOfReceipts->setRowCount(1);
    ui->listOfReceipts->setHorizontalHeaderLabels(QStringList()<<"Наименование"<<"Марка"<<
                                               "Дата приемки");
    QTableWidgetItem* name = new QTableWidgetItem(a.GetName());
    QTableWidgetItem* mark = new QTableWidgetItem(a.GetMark());
    QTableWidgetItem* date = new QTableWidgetItem(a.GetDate());
    ui->listOfReceipts->setItem(0,0,name);
    ui->listOfReceipts->setItem(0,1,mark);
    ui->listOfReceipts->setItem(0,2,date);
}

void TableWork::on_pushButton_clicked()
{
    p = QFileDialog::getOpenFileName(this, "Выбор файла", QDir::cleanPath("C:\\qtprog\\lab1"), "*.txt");

}

