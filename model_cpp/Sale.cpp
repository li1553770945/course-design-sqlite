#include "../model_h/Sale.h"
#include <qstandarditemmodel.h>
#include <qsqlrecord.h>
#include <qsqlquery.h>
#include "../model_h/sqlite.h"
#include <qdebug.h>
#include <QSqlError>
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
void SaleModel::AddItem(const QSqlRecord &record,const  int &num)
{
	QStandardItem* name = new QStandardItem(record.value("name").toString());
	QStandardItem* retail = new QStandardItem(QString::number(record.value("retail").toDouble(),10,2));
	QStandardItem* number = new QStandardItem(QString::number(num));
	QStandardItem* price = new QStandardItem(QString::number(record.value("retail").toDouble()*num, 10, 2));
	QStandardItem* isbn = new QStandardItem(record.value("name").toString());
	QStandardItem* qty = new QStandardItem(QString::number(record.value("qty").toInt()));
	int row = rowCount();
	setItem(row, 0, name);
	setItem(row, 1, retail);
	setItem(row, 2, number);
	setItem(row, 3, price);
	setItem(row, 4, isbn);
	setItem(row, 5, qty);
	_sum_ += record.value("retail").toDouble() * num;
	setHeaderData(0, Qt::Horizontal, "����");
	setHeaderData(1, Qt::Horizontal, "����");
	setHeaderData(2, Qt::Horizontal, "����");
	setHeaderData(3, Qt::Horizontal, "�ܼ�");
	setHeaderData(5, Qt::Horizontal, "���");
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
		qDebug() << "���ڽ����" << i << "�е���Ʒ" << endl;
		QSqlQuery query(Sqlite::_database);
		QString sql;
		qDebug() << "����ԭʼ����Ϊ��" << this->item(i, 5)->data(0).toInt()<<endl;
		int num = this->item(i, 5)->data(0).toInt() - this->item(i, 2)->data(0).toInt();
		qDebug()<<"ʣ��������������"<<num<<" ��棺"<< item(i, 5)->data(0).toInt()<<" ����������"<< item(i, 2)->data(0).toInt();
		sql = sql + "UPDATE books  SET qty="+QString::number(num)+" where isbn=" + item(i, 4)->data(0).toString();
		qDebug() << sql;
		if (!query.exec(sql))
		{
			qDebug() << query.lastError();
			return false;
		}
	}
	this->clear();
	return true;
}