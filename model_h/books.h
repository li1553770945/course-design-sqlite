#pragma once
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlTableModel>
#include "../h/library.h"
class BookModel;
class BookModel :public QSqlTableModel
{
public:
	BookModel(QObject *parent);
	QVariant data(const QModelIndex& index, int role) const;
	
};
class BookOpe {
public:
	enum class Result {Success,Fail,Exist};
	static Result Insert(BookData&);
	static Result Delete(string& isbn);
	static int QueryRow(string& isbn);
	static QSqlRecord Query(string& isbn);
};