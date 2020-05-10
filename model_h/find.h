#pragma once
#include <qsqlquerymodel.h>
#include <vector>
class FindModel: public QSqlQueryModel
{
public:
	QVariant data(const QModelIndex& item, int role) const;
	FindModel(QObject *parent);
	bool Query(QString &key,std::vector <QString> &find_fields,QString &find_method);
};