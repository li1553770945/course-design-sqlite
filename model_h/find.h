#pragma once
#include <qsqlquerymodel.h>
#include <vector>
class FindModel: public QSqlQueryModel
{
public:
	QVariant data(const QModelIndex& item, int role) const;//ʹ�������ܹ�����
	FindModel(QObject *parent);//���캯��
	void SetHeader();//���ñ�ͷ
};