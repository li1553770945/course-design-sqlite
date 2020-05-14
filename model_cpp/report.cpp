#include "../model_h/report.h"
#include "../h/global.h"
#include <qsqlrecord.h>
#include <qdebug.h>
#include "../h/sqlite.h"
#pragma execution_character_set("utf-8")
ReportModel::ReportModel(QObject* parent=(QObject*)nullptr):QSqlQueryModel(parent)
{
    
}
QVariant ReportModel::data(const QModelIndex& item, int role) const
{
    QVariant value = QSqlQueryModel::data(item, role);
    if (role == Qt::TextAlignmentRole)
    {
        value = (Qt::AlignCenter);
        return value;
    }
    return value;
}
void ReportModel::SetHeader()
{
    this->setHeaderData(0, Qt::Horizontal, "书名");
    this->setHeaderData(1, Qt::Horizontal, "ISBN");
    this->setHeaderData(2, Qt::Horizontal, "作者");
    this->setHeaderData(3, Qt::Horizontal, "出版社");
    this->setHeaderData(4, Qt::Horizontal, "进货日期");
    this->setHeaderData(5, Qt::Horizontal, "库存");
    this->setHeaderData(6, Qt::Horizontal, "零售价");
    this->setHeaderData(7, Qt::Horizontal, "批发价");
}

