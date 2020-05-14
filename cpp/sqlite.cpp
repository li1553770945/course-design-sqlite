#include <QApplication>
#include <qdebug.h>
#include <QSqlError>
#include <QSqlQuery>
#include "../h/sqlite.h"
#include "../h/library.h"
#include <iostream>
#include <io.h>
#include <qsqlrecord.h>
#include "../h/global.h"
#pragma execution_character_set("utf-8")
QSqlDatabase Sqlite::_database;
bool Sqlite::Open()
{

	_database = QSqlDatabase::addDatabase("QSQLITE");
	_database.setDatabaseName("library.db");
	if (!_database.open())
	{
		qDebug() << "创建数据库出错！";
		qDebug() << _database.lastError();
		throw _database.lastError();
		return false;
	}
	else
	{
		return true;
	}
}
bool Sqlite::CreateBooksTable()
{
	QSqlQuery sql_query;
	if (!sql_query.exec("CREATE TABLE books(id INTEGER PRIMARY KEY   AUTOINCREMENT,"
		"name TEXT,"
		"isbn TEXT,"
		"author TEXT,"
		"publisher TEXT,"
		"date_added TEXT,"
		"qty INT,"
		"retail REAL,"
		"wholesale REAL,"
		"name_pinyin TEXT)"))

	{
		qDebug() << "创建数据表出错！";
		qDebug() << _database.lastError();
		throw _database.lastError();
		return false;
	}
	if (!sql_query.exec("CREATE UNIQUE INDEX books_isbn_IDX ON books (isbn);"))
	{
		qDebug() << "设置索引出错！";
		qDebug() << _database.lastError();
		throw _database.lastError();
	}
	return true;
}
bool Sqlite::Close()
{//关闭数据库
	_database.close();
	return true;
}
void Sqlite::LoadDataBase()
{
	if (_access("library.db", 0) == -1)//检测是否存在
	{
		try
		{
			Sqlite::Open();
		}
		catch (QSqlError err)
		{
			throw QString("创建数据库出错！") + err.text();
		}
		try
		{
			Sqlite::CreateBooksTable();
		}
		catch (QSqlError err)
		{
			throw QString("创建数据表出错！") + err.text();;
			qDebug() << err.text();
		}
		Close();//这里只是为了创建，所以需要关闭！
	}
	if (_access("library.db", 6) == -1)
	{
		Close();
		throw QString("数据库已存在，但无权读写!");
	}
	try//数据库存在，且有权限 正式打开
	{
		Sqlite::Open();
	}
	catch (QSqlError err)
	{
		throw QString("无法打开数据库！") + err.text();
	}
	QSqlQuery query;
	query.exec("select * from sys.tables where name = 'books'");
	if (query.next())//如果没有数据表，尝试创建
	{
		try
		{
			Sqlite::CreateBooksTable();
		}
		catch (QSqlError err)
		{
			throw QString("创建数据表出错！") + err.text();;
		}
	}
}
BookOpe::Result BookOpe::Insert(BookData& book)
{
	if (QueryRow(string(book.GetISBN())) != -1)
		return Result::Exist;
	QSqlQuery query(Sqlite::_database);
	query.prepare("insert into books(name,isbn,author,publisher,date_added,qty,retail,wholesale,name_pinyin) VALUES (:name,:isbn,:author,:publisher,:date_added,:qty,:retail,:wholesale,:name_pinyin)");
	query.bindValue(":name", QString::fromLocal8Bit(book.GetName()));
	query.bindValue(":isbn", book.GetISBN());
	query.bindValue(":author", QString::fromLocal8Bit(book.GetAuth()));
	query.bindValue(":publisher", QString::fromLocal8Bit(book.GetPub()));
	query.bindValue(":date_added", book.GetDateAdded());
	query.bindValue(":qty", book.GetQty());
	query.bindValue(":retail", book.GetRetail());
	query.bindValue(":wholesale", book.GetWholesale());
	string name_pinyin;
	ChineseConvertPy(book.GetName(), name_pinyin);
	cout << name_pinyin;
	query.bindValue(":name_pinyin", name_pinyin.data());
	if (query.exec())
		return Result::Success;
	else
		return Result::Fail;
}
BookOpe::Result BookOpe::Delete(string& isbn)
{
	QSqlQuery query(Sqlite::_database);
	if (query.exec("DELETE FROM books WHERE isbn='" + QString::fromStdString(isbn) + "'"))
		return Result::Success;
	else
		return Result::Fail;
}
int  BookOpe::QueryRow(string& isbn)
{
	QSqlQuery query;
	query.exec("SELECT id FROM books WHERE isbn='" + QString::fromStdString(isbn) + "'");
	query.last();
	if (query.isValid())
	{
		return query.at();
	}
	else
	{
		return -1;
	}
}
QSqlRecord BookOpe::Query(string& isbn)
{
	QSqlQuery query(Sqlite::_database);
	QString sql = "SELECT * FROM books WHERE isbn='" + QString::fromStdString(isbn) + "'";
	query.exec(sql);
	query.first();
	return query.record();
}