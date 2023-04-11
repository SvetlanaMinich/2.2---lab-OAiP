#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QDate>
#include "doublylinkedlist.h"
#include "receipt.h"
#include <QTableWidget>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->listOfReceipts->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->addNode->setEnabled(false);
    ui->saveToFile->setEnabled(false);
    ui->addBegin->setEnabled(false);
    ui->addEnd->setEnabled(false);
    ui->deleteBegin->setEnabled(false);
    ui->deleteEnd->setEnabled(false);
    ui->nodeSearch->setEnabled(false);
    ui->deleteByName->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

DoublyLinkedList mainList;
Node* head;
Node* tail;
QString path;

Receipt MainWindow::add()
{
    QString naming;
    QString mark;
    QString date;
    bool repeat = true;
    while(repeat)
    {
        repeat = false;
        try {
            bool ok;
            naming = QInputDialog::getText(this,tr("Наименование"),
                                               tr("Введите наименование группы изделий"),
                                               QLineEdit::Normal,"",&ok);

            if(naming.isEmpty())
            {
                repeat = true;
                throw std::invalid_argument("Введена пустая строка");
            }

            bool is_all_digital = true;
            for(QChar ch : naming)
            {
                if(!ch.isDigit())
                {
                    is_all_digital = false;
                    break;
                }
            }
            if(is_all_digital)
            {
                repeat = true;
                throw std::invalid_argument("В наименовинии группы изделий должна"
                                            " присутствовать хотя бы одна буква");
            }
        } catch(std::invalid_argument& e) {
            QMessageBox::critical(this, tr("Ошибка"), e.what());
        }
    }

    repeat = true;
    while(repeat)
    {
        repeat = false;
        try {
            bool ok;
            mark = QInputDialog::getText(this,tr("Марка изделия"),
                                                 tr("Введите марку изделия"),
                                                 QLineEdit::Normal,"",&ok);

            if(mark.isEmpty())
            {
                repeat = true;
                throw std::invalid_argument("Введена пустая строка");
            }

            bool is_all_digital = true;
            for(QChar ch : mark)
            {
                if(!ch.isDigit())
                {
                    is_all_digital = false;
                    break;
                }
            }
            if(!is_all_digital)
            {
                repeat = true;
                throw std::invalid_argument("В наименовании марки изделия должны "
                                            "присутствовать только цифры");
            }
        } catch (std::invalid_argument& e) {
            QMessageBox::critical(this, tr("Ошибка"), e.what());
        }
    }

    repeat = true;
    while(repeat)
    {
        repeat = false;
        try {
            bool ok;
            date = QInputDialog::getText(this,tr("Дата приемки в ремонт"),
                                                 tr("Введите дату"),
                                                 QLineEdit::Normal,"",&ok);

            QDate check = QDate::fromString(date,"dd.MM.yyyy");
            if(!check.isValid())
            {
                repeat = true;
                throw std::invalid_argument("Введенная строка не считается датой. "
                                            "Введите строку в формате dd.mm.yyyy");
            }
        } catch (std::invalid_argument& e) {
            QMessageBox::critical(this, tr("Ошибка"), e.what());
        }
    }

    Receipt rec(naming.toStdString(),std::stoi(mark.toStdString()),
                QDate::fromString(date, "dd.MM.yyyy"));
    return rec;
}

void MainWindow::on_openFile_clicked()
{
    path = QFileDialog::getOpenFileName(this, "Выбор файла", QDir::cleanPath("C:/QTlab2/task1/f"), "*.txt");
    FILE* file;
    std::string p = path.toStdString();
    const char* pathres = p.c_str();
    if(!fopen_s(&file,pathres,"r"))
    {
        int empty = 1;
        int c = fgetc(file);
        if (c != EOF) {
            empty = 0;
        }
        if(empty)
        {
            ui->listOfReceipts->setColumnCount(4);
            ui->listOfReceipts->setHorizontalHeaderLabels(QStringList()<<"Наименование"<<
                                                          "Марка"<<"Дата приемки"<<
                                                          "Состояние");

            ui->addNode->setEnabled(true);
            ui->openFile->setEnabled(false);
        }
        else
        {
            QMessageBox::information(this,tr("Ошибка"),
                                     tr("Файл должен быть пустым при открытии"));
        }
    }
    fclose(file);
}

void MainWindow::on_addNode_clicked()
{
    Receipt res = add();
    head = tail = mainList.InitFirstNode(res);

    ui->listOfReceipts->insertRow(0);

    QString state = "Не выполнен";
    if(QDate::fromString(res.GetDate(), "dd.MM.yyyy").daysTo(QDate::currentDate())>7)
    {
        state = "Выполнен";
    }

    QTableWidgetItem* name = new QTableWidgetItem(res.GetName());
    QTableWidgetItem* markQ = new QTableWidgetItem(res.GetMark());
    QTableWidgetItem* dateQ = new QTableWidgetItem(res.GetDate());
    QTableWidgetItem* stateQ = new QTableWidgetItem(state);

    ui->listOfReceipts->setItem(0,0,name);
    ui->listOfReceipts->setItem(0,1,markQ);
    ui->listOfReceipts->setItem(0,2,dateQ);
    ui->listOfReceipts->setItem(0,3,stateQ);

    ui->saveToFile->setEnabled(true);
    ui->addNode->setEnabled(false);
    ui->addBegin->setEnabled(true);
    ui->addEnd->setEnabled(true);
    ui->deleteBegin->setEnabled(true);
    ui->deleteEnd->setEnabled(true);
    ui->nodeSearch->setEnabled(true);
    ui->deleteByName->setEnabled(true);
}

void MainWindow::on_saveToFile_clicked()
{
    FILE* file;
    std::string p = path.toStdString();
    const char* pathres = p.c_str();
    if(!fopen_s(&file,pathres,"w"))
    {
        for(int i=0; i<ui->listOfReceipts->rowCount(); i++)
        {
            for(int j=0; j<ui->listOfReceipts->columnCount()-1; j++)
            {
                for(int k=0; k<ui->listOfReceipts->item(i,j)->text().size(); k++)
                {
                    fprintf(file, "%c", ui->listOfReceipts->item(i,j)->text()[k]);
                }
                fprintf(file, "%c", '\n');
            }
        }
    }
    fclose(file);
}

void MainWindow::on_addBegin_clicked()
{
    Receipt res = add();
    mainList.InsertBegin(head,res);

    ui->listOfReceipts->insertRow(0);

    QString state = "Не выполнен";
    if(QDate::fromString(res.GetDate(), "dd.MM.yyyy").daysTo(QDate::currentDate())>7)
    {
        state = "Выполнен";
    }

    QTableWidgetItem* name = new QTableWidgetItem(res.GetName());
    QTableWidgetItem* mark = new QTableWidgetItem(res.GetMark());
    QTableWidgetItem* date = new QTableWidgetItem(res.GetDate());
    QTableWidgetItem* stateQ = new QTableWidgetItem(state);

    ui->listOfReceipts->setItem(0,0,name);
    ui->listOfReceipts->setItem(0,1,mark);
    ui->listOfReceipts->setItem(0,2,date);
    ui->listOfReceipts->setItem(0,3,stateQ);
}

void MainWindow::on_addEnd_clicked()
{
    Receipt res = add();
    mainList.InsertEnd(tail,res);

    ui->listOfReceipts->insertRow(ui->listOfReceipts->rowCount());

    QString state = "Не выполнен";
    if(QDate::fromString(res.GetDate(), "dd.MM.yyyy").daysTo(QDate::currentDate())>7)
    {
        state = "Выполнен";
    }

    QTableWidgetItem* name = new QTableWidgetItem(res.GetName());
    QTableWidgetItem* mark = new QTableWidgetItem(res.GetMark());
    QTableWidgetItem* date = new QTableWidgetItem(res.GetDate());
    QTableWidgetItem* stateQ = new QTableWidgetItem(state);

    ui->listOfReceipts->setItem(ui->listOfReceipts->rowCount()-1,0,name);
    ui->listOfReceipts->setItem(ui->listOfReceipts->rowCount()-1,1,mark);
    ui->listOfReceipts->setItem(ui->listOfReceipts->rowCount()-1,2,date);
    ui->listOfReceipts->setItem(ui->listOfReceipts->rowCount()-1,3,stateQ);
}

void MainWindow::on_deleteBegin_clicked()
{
    if(ui->listOfReceipts->rowCount()==1)
    {
        ui->addNode->setEnabled(true);
        ui->addBegin->setEnabled(false);
        ui->addEnd->setEnabled(false);
        ui->saveToFile->setEnabled(false);
        ui->deleteBegin->setEnabled(false);
        ui->deleteEnd->setEnabled(false);
        ui->nodeSearch->setEnabled(false);
        ui->deleteByName->setEnabled(false);
    }
    mainList.DeleteBegin(head);
    ui->listOfReceipts->removeRow(0);
}

void MainWindow::on_deleteEnd_clicked()
{
    if(ui->listOfReceipts->rowCount()==1)
    {
        ui->addNode->setEnabled(true);
        ui->addBegin->setEnabled(false);
        ui->addEnd->setEnabled(false);
        ui->saveToFile->setEnabled(false);
        ui->deleteBegin->setEnabled(false);
        ui->deleteEnd->setEnabled(false);
        ui->nodeSearch->setEnabled(false);
        ui->deleteByName->setEnabled(false);
    }
    mainList.DeleteEnd(tail);
    ui->listOfReceipts->removeRow(ui->listOfReceipts->rowCount()-1);
}

void MainWindow::on_nodeSearch_clicked()
{
    bool ok;
    QString naming = QInputDialog::getText(this,tr("Наименование"),
                                       tr("Введите наименование группы изделий"),
                                       QLineEdit::Normal,"",&ok);
    Receipt res = mainList.NodeSearch(naming,head);
    if(res.GetName()=="")
    {
        QMessageBox::information(this,"Ошибка","Такого элемента в списке нет");
    }
    else
    {
        QMessageBox::information(this, "Элемент " + res.GetName(),
                                 "Марка: " + res.GetMark() + '\n' +
                                 "Дата приемки: " + res.GetDate());
    }
}

void MainWindow::on_deleteByName_clicked()
{
    bool ok;
    QString naming = QInputDialog::getText(this,tr("Наименование"),
                                       tr("Введите наименование группы изделий"),
                                       QLineEdit::Normal,"",&ok);
    bool del = false;
    if(ui->listOfReceipts->item(0,0)->text()==naming)
    {
        mainList.DeleteBegin(head);
        ui->listOfReceipts->removeRow(0);
        del = true;
    }
    else if(ui->listOfReceipts->item(ui->listOfReceipts->rowCount()-1,0)->text()
            == naming)
    {
        mainList.DeleteEnd(tail);
        ui->listOfReceipts->removeRow(ui->listOfReceipts->rowCount()-1);
        del = true;
    }
    else
    {
        int row = mainList.DeleteMiddle(naming, head);
        if(row==-1)
        {
            QMessageBox::information(this, tr("Ошибка"),tr("Такого элемента в списке нет"));
        }
        else
        {
            ui->listOfReceipts->removeRow(row);
            del = true;
        }
    }
    if(del == true)
    {
        if(ui->listOfReceipts->rowCount()==0)
        {
            ui->addNode->setEnabled(true);
            ui->addBegin->setEnabled(false);
            ui->addEnd->setEnabled(false);
            ui->saveToFile->setEnabled(false);
            ui->deleteBegin->setEnabled(false);
            ui->deleteEnd->setEnabled(false);
            ui->nodeSearch->setEnabled(false);
            ui->deleteByName->setEnabled(false);
        }
    }
}

void MainWindow::on_sort_clicked()
{
    head = mainList.MergeSort(head);
    int size = ui->listOfReceipts->rowCount();
    for(int i=0;i<size;i++)
    {
        ui->listOfReceipts->removeRow(0);
    }
    Node* temp = head;
    for(int i=0;i<size;i++)
    {
        if(temp==nullptr) break;

        ui->listOfReceipts->insertRow(i);

        QString state = "Не выполнен";
        if(QDate::fromString(temp->data.GetDate(), "dd.MM.yyyy").daysTo(QDate::currentDate())>7)
        {
            state = "Выполнен";
        }

        QTableWidgetItem* name = new QTableWidgetItem(temp->data.GetName());
        QTableWidgetItem* mark = new QTableWidgetItem(temp->data.GetMark());
        QTableWidgetItem* date = new QTableWidgetItem(temp->data.GetDate());
        QTableWidgetItem* stateQ = new QTableWidgetItem(state);

        ui->listOfReceipts->setItem(i,0,name);
        ui->listOfReceipts->setItem(i,1,mark);
        ui->listOfReceipts->setItem(i,2,date);
        ui->listOfReceipts->setItem(i,3,stateQ);

        temp=temp->next;
    }
}

























