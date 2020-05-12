#pragma once
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlTableModel>
#include "../h/library.h"
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
	ReportModel(QObject * parent);
	bool lessThan(const QModelIndex& source_left, const QModelIndex& source_right);
};
class BookOpe {
public:
	enum class Result {Success,Fail,Exist};
	static Result Insert(BookData&);
	static Result Delete(string& isbn);
	static int QueryRow(string& isbn);
	static QSqlRecord Query(string& isbn);
};