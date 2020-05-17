#pragma once
#include <qsqlquerymodel.h>
#include <vector>
class FindModel: public QSqlQueryModel
{
public:
	QVariant data(const QModelIndex& item, int role) const;//使得数据能够居中
	FindModel(QObject *parent);//构造函数
	void SetHeader();//设置表头
};