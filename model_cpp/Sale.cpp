#include "../model_h/Sale.h"
#include <qstandarditemmodel.h>
#include <qsqlrecord.h>
#include <qsqlquery.h>
#include "../model_h/sqlite.h"
#include <qdebug.h>
#include <QSqlError>
#include "qmessagebox.h"
#include "../h/global.h"
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
	//connect(this, SIGNAL(itemChanged(QStandardItem*)), this, SLOT(ItemChange(QStandardItem*)));
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
void SaleModel::AddItem(const QSqlRecord &record,int &num, bool& status, int& row)
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
				_sum_ += record.value("retail").toDouble() * num;
				
				qDebug() << _sum_;
				num = item(i, 4)->data(0).toInt() + num;
				setData(index(i,4),QString::number(num));
				_num_[i]=num;
				setData(index(i,5),QString::number(num* record.value("retail").toDouble(),10,2));
				row = i;
				status = true;
				return;
			}
		}
	}
	_num_.push_back(num);
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
	_num_.clear();
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
	_num_.erase(_num_.begin() + row);
}
void SaleModel::ItemChange(QStandardItem* changed_item)
{
	int row = changed_item->row();
	int change_num = my_atoi(changed_item->data(0).toString().toStdString().data());
	if (changed_item->column()==4&& (change_num != _num_[changed_item->row()]))//如果修改的是单价并且是用户修改
	{
		int qty = this->item(row, 2)->data(0).toInt();
		if (change_num>0&&change_num<=qty)
		{
			qDebug() << "检测到手动修改修改" << endl;
			_sum_ += (change_num - _num_[row]) * this->item(row, 3)->data(0).toDouble();
			this->setData(index(row, 5), QString::number(changed_item->data(0).toInt() * this->item(row, 3)->data(0).toDouble(), 10, 2));
			_num_[row] = changed_item->data(0).toInt();
			
		}
		else
		{
			QMessageBox box;
			box.setIcon(QMessageBox::Information);
			box.setWindowTitle("提示");
			if (change_num >  this->item(row, 2)->data(0).toInt())
			{
				box.setText("您的购买量已经超过库存！");
			}
			else if (change_num < 0)
			{
				box.setText("购买量必须为大于0的整数！");
			}
			else if (change_num == 0)
			{
				box.setText("购买量必须大于0！如您需要取消购买，请右键点击本项-删除。");
			}
			box.exec();
			this->setData(index(row, 4), QString::number(_num_[row]));
		}

	}
}