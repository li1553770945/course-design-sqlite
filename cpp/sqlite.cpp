#include <QApplication>
#include <qdebug.h>
#include <QSqlError>
#include <QSqlQuery>
#include "../h/sqlite.h"
#include <io.h>
#pragma execution_character_set("utf-8")
QSqlDatabase Sqlite::_database;
bool Sqlite::Open()
{

	_database = QSqlDatabase::addDatabase("QSQLITE");
	_database.setDatabaseName("library.db");
	if (!_database.open())
	{
		qDebug() << "�������ݿ����";
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
		"wholesale REAL)"))

	{
		qDebug() << "�������ݱ����";
		qDebug() << _database.lastError();
		throw _database.lastError();
		return false;
	}
	if (!sql_query.exec("CREATE UNIQUE INDEX books_isbn_IDX ON books (isbn);"))
	{
		qDebug() << "������������";
		qDebug() << _database.lastError();
		throw _database.lastError();
	}
	return true;
}
bool Sqlite::Close()
{//�ر����ݿ�
	_database.close();
	return true;
}
void Sqlite::LoadDataBase()
{
	if (_access("library.db", 0) == -1)//����Ƿ����
	{
		try
		{
			Sqlite::Open();
		}
		catch (QSqlError err)
		{
			throw QString("�������ݿ����") + err.text();
		}
		try
		{
			Sqlite::CreateBooksTable();
		}
		catch (QSqlError err)
		{
			throw QString("�������ݱ����") + err.text();;
			qDebug() << err.text();
		}
		Close();//����ֻ��Ϊ�˴�����������Ҫ�رգ�
	}
	if (_access("library.db", 6) == -1)
	{
		Close();
		throw QString("���ݿ��Ѵ��ڣ�����Ȩ��д!");
	}
	try//���ݿ���ڣ�����Ȩ�� ��ʽ��
	{
		Sqlite::Open();
	}
	catch (QSqlError err)
	{
		throw QString("�޷������ݿ⣡") + err.text();
	}
	QSqlQuery query;
	query.exec("select * from sys.tables where name = 'books'");
	if (query.next())//���û�����ݱ����Դ���
	{
		try
		{
			Sqlite::CreateBooksTable();
		}
		catch (QSqlError err)
		{
			throw QString("�������ݱ����") + err.text();;
		}
	}
}