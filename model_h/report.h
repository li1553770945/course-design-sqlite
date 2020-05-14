#pragma once
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <qsortfilterproxymodel.h>
class ReportModel :public QSqlTableModel
{
public:
	ReportModel(QObject *parent);
	QVariant data(const QModelIndex& index, int role) const;
	
};