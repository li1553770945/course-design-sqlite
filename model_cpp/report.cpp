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
    this->setHeaderData(0, Qt::Horizontal, "����");
    this->setHeaderData(1, Qt::Horizontal, "ISBN");
    this->setHeaderData(2, Qt::Horizontal, "����");
    this->setHeaderData(3, Qt::Horizontal, "������");
    this->setHeaderData(4, Qt::Horizontal, "��������");
    this->setHeaderData(5, Qt::Horizontal, "���");
    this->setHeaderData(6, Qt::Horizontal, "���ۼ�");
    this->setHeaderData(7, Qt::Horizontal, "������");
}

