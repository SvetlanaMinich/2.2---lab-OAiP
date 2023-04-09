#include "receipt.h"

Receipt::Receipt()
{
    name = "";
    mark = 0;
    date = date.currentDate();
    is_done = 0;
}

Receipt::Receipt(std::string n, int m, QDate d)
{
    name = n;
    mark = m;
    date = d;
    is_done = 0;
}

QString Receipt::GetName()
{
    return QString::fromStdString(name);
}

QString Receipt::GetMark()
{
    return QString::number(mark);
}

QString Receipt::GetDate()
{
    return date.toString("dd.MM.yyyy");
}



