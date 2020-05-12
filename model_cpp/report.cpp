#include "../model_h/report.h"
#include "../h/global.h"
#include <qsqlrecord.h>
#include <qdebug.h>
#include "../h/sqlite.h"
#pragma execution_character_set("utf-8")
BookModelNotSort::BookModelNotSort(QObject* parent=(QObject*)nullptr):QSqlTableModel(parent)
{
    this->setTable("books");
    this->setHeaderData(1, Qt::Horizontal, "书名");
    this->setHeaderData(2, Qt::Horizontal, "ISBN");
    this->setHeaderData(3, Qt::Horizontal, "作者");
    this->setHeaderData(4, Qt::Horizontal, "出版社");
    this->setHeaderData(5, Qt::Horizontal, "进货日期");
    this->setHeaderData(6, Qt::Horizontal, "库存");
    this->setHeaderData(7, Qt::Horizontal, "零售价");
    this->setHeaderData(8, Qt::Horizontal, "批发价");
}
ReportModel::ReportModel(QObject* parent=(QObject*)nullptr,BookModelNotSort *book_model=NULL):QSortFilterProxyModel(parent)
{
   
    this->setSourceModel(book_model);
}
bool ReportModel::lessThan(const QModelIndex& source_left, const QModelIndex& source_right) const
{
    if (!source_left.isValid() || !source_right.isValid())
        return false;
    int column = source_left.column();
    QVariant leftData = sourceModel()->data(source_left);
    QVariant rightData = sourceModel()->data(source_right);
    //qDebug() << leftData.toString().toStdString().data() << " "<< rightData.toString().toStdString().data() <<endl;
   // qDebug() << strcmp(leftData.toString().toStdString().data() , rightData.toString().toStdString().data());
    if (column == 1 || column == 5)
        return strcmp(leftData.toString().toLocal8Bit().data(), rightData.toString().toLocal8Bit().data()) < 0;
    else if (column == 6)
        return leftData.toInt() < rightData.toInt();
    else if (column == 7 || column == 8)
        return leftData.toDouble() < rightData.toDouble();
}
QVariant BookModelNotSort::data(const QModelIndex& item, int role) const
{
    QVariant value = QSqlQueryModel::data(item, role);
    if (role == Qt::TextAlignmentRole)
    {
        value = (Qt::AlignCenter);
        return value;
    }
    return value;
}

