#pragma once
#include <qstandarditemmodel.h>
#include <qsqlrecord.h>
class SaleModel:public QStandardItemModel
{
	Q_OBJECT;
private:
	static double _fax_;
	double _sum_;
	std::vector <int> _num_;
	
	
public:
	void ItemChange(QStandardItem* item);
	static void SetFax(double fax);
	static double GetFax();
	SaleModel(QObject *parent);
	QVariant data(const QModelIndex& item, int role) const;
	void AddItem(const QSqlRecord & record, int & num,bool &status,int &row);//·µ»Ø×´Ì¬
	void clear();
	double GetSum();
	double GetSumFaxed();
	bool Sattle();
	void Delete(int row);
};