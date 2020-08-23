#pragma once
#include <qstandarditemmodel.h>
#include <qsqlrecord.h>
class SaleModel:public QStandardItemModel
{
	Q_OBJECT;
private:
	static double _fax_;//税率
	double _sum_;//购物车所有书的总金额
	std::vector <int> _num_;//用于存储每本书的购买数量，当用户直接输入数量，如果不符合规定，则按此数组恢复
	
	
public:
	void ItemChange(QStandardItem* item);//修改一个条目的数量时
	static void SetFax(double fax);//设置税率	
	static double GetFax();//得到税率
	SaleModel(QObject *parent);
	QVariant data(const QModelIndex& item, int role) const;//数据居中
	void AddItem(const QSqlRecord & record, int & num,bool &status,int &row);/*使用status的引用，如果为true则正常添加，引用row，返回要添加的书的所在行（如果已存在，返回所在行
	因为比如用户添加的书超过了库存，要告诉用户在哪一行）*/
	void clear();//清空所有条目并置零总金额
	double GetSum();//返回总金额
	double GetSumFaxed();//返回税后总金额
	bool Sattle();//结算，扣掉库存并清空
	void Delete(int row);//删除一个条目，请重新计算总金额
};