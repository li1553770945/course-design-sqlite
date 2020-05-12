#pragma once
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <qsortfilterproxymodel.h>
class BookModelNotSort :public QSqlTableModel
{
public:
	BookModelNotSort(QObject *parent);
	QVariant data(const QModelIndex& index, int role) const;
	
};
class ReportModel:public QSortFilterProxyModel
{
public:
	ReportModel(QObject * parent, BookModelNotSort* book_model);
	bool lessThan(const QModelIndex& source_left, const QModelIndex& source_right) const override;
};
