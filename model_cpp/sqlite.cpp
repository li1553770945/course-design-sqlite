#include <QApplication>
#include <qdebug.h>
#include <QSqlError>
#include <QSqlQuery>
#include "../model_h/sqlite.h"
#pragma execution_character_set("utf-8")
QSqlDatabase Sqlite::_database;
bool Sqlite::Open()
{
    
    _database = QSqlDatabase::addDatabase("QSQLITE");
    _database.setDatabaseName("library.db");
    if (!_database.open())
    {
        qDebug() << "�������ݿ����";
        qDebug()<< _database.lastError();
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
    if (!sql_query.exec("create table books(id int primary key  , name text, isbn text , author text,publisher text,date_added text,qty integer,retail real,wholesale real)"))
    {
        qDebug() << "�������ݱ����";
        qDebug() << _database.lastError();
        return false;
    }
    if (!sql_query.exec("CREATE UNIQUE INDEX books_isbn_IDX ON books (isbn);"))
    {
        qDebug() << "������������";
        qDebug() << _database.lastError();
        return false;
    }
    Sqlite::Close();
    return true;
}
bool Sqlite::Close()
{//�ر����ݿ�
    _database.close();
    return true;
}