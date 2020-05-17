#pragma once
#include <qstandarditemmodel.h>
#include <qsqlrecord.h>
class SaleModel:public QStandardItemModel
{
	Q_OBJECT;
private:
	static double _fax_;//˰��
	double _sum_;//���ﳵ��������ܽ��
	std::vector <int> _num_;//���ڴ洢ÿ����Ĺ������������û�ֱ��������������������Ϲ涨���򰴴�����ָ�
	
	
public:
	void ItemChange(QStandardItem* item);//�޸�һ����Ŀ������ʱ
	static void SetFax(double fax);//����˰��	
	static double GetFax();//�õ�˰��
	SaleModel(QObject *parent);
	QVariant data(const QModelIndex& item, int role) const;//���ݾ���
	void AddItem(const QSqlRecord & record, int & num,bool &status,int &row);/*ʹ��status�����ã����Ϊtrue��������ӣ�����row������Ҫ��ӵ���������У�����Ѵ��ڣ�����������
	��Ϊ�����û���ӵ��鳬���˿�棬Ҫ�����û�����һ�У�*/
	void clear();//���������Ŀ�������ܽ��
	double GetSum();//�����ܽ��
	double GetSumFaxed();//����˰���ܽ��
	bool Sattle();//���㣬�۵���沢���
	void Delete(int row);//ɾ��һ����Ŀ�������¼����ܽ��
};