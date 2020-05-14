#pragma once
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <qsortfilterproxymodel.h>
class ReportModel :public QSqlQueryModel
{
public:
	ReportModel(QObject *parent);
	QVariant data(const QModelIndex& index, int role) const;
	void SetHeader();
};