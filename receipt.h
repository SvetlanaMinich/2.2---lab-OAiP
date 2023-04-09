#ifndef RECEIPT_H
#define RECEIPT_H
#include <string>
#include <QDate>

class Receipt
{
private:
    std::string name;
    int mark;
    QDate date;
    bool is_done;
public:
    Receipt();
    Receipt(std::string n, int m, QDate d);
    QString GetName();
    QString GetMark();
    QString GetDate();
};

#endif // RECEIPT_H
