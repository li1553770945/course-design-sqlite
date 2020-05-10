#include "../model_h/Sale.h"
#include <qstandarditemmodel.h>
#include <qsqlrecord.h>
#include <qsqlquery.h>
#include "../model_h/sqlite.h"
#include <qdebug.h>
#include <QSqlError>
#include "qmessagebox.h"
# pragma execution_character_set("utf-8")
double SaleModel::_fax_ = 0.06;
void SaleModel::SetFax(double fax)
{
	_fax_ = fax;
}
double SaleModel::GetFax()
{
	return _fax_;
}
SaleModel::SaleModel(QObject* parent=(QObject*)nullptr):QStandardItemModel(parent)
{
	_sum_ = 0;
}
QVariant SaleModel::data(const QModelIndex& item, int role) const
{
	QVariant value = QStandardItemModel::data(item, role);
	if (role == Qt::TextAlignmentRole)
	{
		value = (Qt::AlignCenter);
		return value;
	}
	return value;
}
void SaleModel::AddItem(const QSqlRecord &record,const  int &num, bool& status, int& row)
{
	QStandardItem* isbn = new QStandardItem(record.value("isbn").toString());
	for (int i = 0; i < rowCount(); i++)
	{
		if (item(i, 0)->data(0).toString() == record.value("isbn").toString())
		{
			if (num + item(i, 4)->data(0).toInt() > item(i, 2)->data(0).toInt())
			{
				status = false;
				row = i;
				return;
			}
			else
			{
				setData(index(i,4),QString::number(item(i, 4)->data(0).toInt()+num));
				setData(index(i,5),QString::number(item(i, 4)->data(0).toInt()* record.value("retail").toDouble(),10,2));
				_sum_ += record.value("retail").toDouble() * num;
				row = i;
				status = true;
				return;
			}
		}
	}
	QStandardItem* name = new QStandardItem(record.value("name").toString());
	name->setEditable(false);
	QStandardItem* retail = new QStandardItem(QString::number(record.value("retail").toDouble(),10,2));
	retail->setEditable(false);
	QStandardItem* number = new QStandardItem(QString::number(num));
	QStandardItem* price = new QStandardItem(QString::number(record.value("retail").toDouble()*num, 10, 2));
	price->setEditable(false);
	QStandardItem* qty = new QStandardItem(QString::number(record.value("qty").toInt()));
	qty->setEditable(false);
	row = rowCount();
	setItem(row, 0,isbn);
	setItem(row, 1, name);
	setItem(row, 2, qty);
	setItem(row, 3, retail);
	setItem(row, 4, number);
	setItem(row, 5, price);
	_sum_ += record.value("retail").toDouble() * num;
	setHeaderData(1, Qt::Horizontal, "书名");
	setHeaderData(2, Qt::Horizontal, "库存");
	setHeaderData(3, Qt::Horizontal, "单价");
	setHeaderData(4, Qt::Horizontal, "购买数量");
	setHeaderData(5, Qt::Horizontal, "总价");
	status = true;
	return;
}
void SaleModel::clear()
{
	QStandardItemModel::clear();
	_sum_ = 0;
}
double SaleModel::GetSum()
{
	return _sum_;
}
double SaleModel::GetSumFaxed()
{
	return _sum_ * (1+_fax_);
}
bool SaleModel::Sattle()
{
	for (int i = 0; i < rowCount(); i++)
	{
		
		QSqlQuery query(Sqlite::_database);
		QString sql;
		int num = item(i, 2)->data(0).toInt() - item(i, 4)->data(0).toInt();
		sql = sql + "UPDATE books  SET qty="+QString::number(num)+" where isbn=" + item(i, 0)->data(0).toString();
		if (!query.exec(sql))
		{
			qDebug() << "结算出错："<<query.lastError();
			return false;
		}
	}
	this->clear();
	return true;
}
void SaleModel::Delete(int row)
{
	_sum_ -= item(row, 5)->data(0).toDouble();
	removeRow(row);
}