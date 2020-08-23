#pragma once
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <qsortfilterproxymodel.h>
class ReportModel :public QSqlQueryModel
{
public:
	ReportModel(QObject *parent);//使得数据能够居中
	QVariant data(const QModelIndex& index, int role) const;//构造函数
	void SetHeader();//设置表头
};