#include "../model_h/find.h"
#include <qdebug.h>
# pragma execution_character_set("utf-8")
FindModel::FindModel(QObject *parent):QSqlQueryModel::QSqlQueryModel(parent)
{
	
}
bool FindModel::Query(QString& key, std::vector <QString>& find_fields, QString& find_method)
{
	QString sql = "select * from books where";
	if (find_method == "fuzzy")
	{
		int i = 1;
		for (auto field : find_fields)
		{
			if (i != 1)
				sql += " or";
			sql = sql+ " " + field + " like '%" + key+"%'";;
			i++;
		}
	}
	else if (find_method == "accurate")
	{
		int i = 1;
		for (auto field : find_fields)
		{
			if (i != 1)
				sql += " or";
			sql =sql +" "+ field + "='"+ key+"'";
			i++;
		}
	}
	setQuery(sql);
	this->setHeaderData(1, Qt::Horizontal, "����");
	this->setHeaderData(2, Qt::Horizontal, "ISBN");
	this->setHeaderData(3, Qt::Horizontal, "����");
	this->setHeaderData(4, Qt::Horizontal, "������");
	this->setHeaderData(5, Qt::Horizontal, "��������");
	this->setHeaderData(6, Qt::Horizontal, "���");
	this->setHeaderData(7, Qt::Horizontal, "���ۼ�");
	this->setHeaderData(8, Qt::Horizontal, "������");
	qDebug() << sql;
	return true;
}
QVariant FindModel::data(const QModelIndex& item, int role) const
{
	QVariant value = QSqlQueryModel::data(item, role);
	if (role == Qt::TextAlignmentRole)
	{
		value = (Qt::AlignCenter);
		return value;
	}
	return value;
}