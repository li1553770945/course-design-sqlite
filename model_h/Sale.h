#pragma once
#include <qstandarditemmodel.h>
#include <qsqlrecord.h>
class SaleModel:public QStandardItemModel
{
private:
	static double _fax_;
	double _sum_;
public:
	static void SetFax(double fax);
	static double GetFax();
	SaleModel(QObject *parent);
	QVariant data(const QModelIndex& item, int role) const;
	void AddItem(const QSqlRecord & record,const  int & num,bool &status,int &row);//����״̬
	void clear();
	double GetSum();
	double GetSumFaxed();
	bool Sattle();
	void Delete(int row);
};