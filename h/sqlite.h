#pragma once
#include <QSqlDatabase>
#include "../h/library.h"
#include <QSqlError>
#include <QSqlQuery>
class Sqlite {
public:
	static QSqlDatabase _database;//数据库
	static bool Open();//打开或创建链接
	static bool CreateBooksTable();//创建books数据表
	static bool Close();//关闭连接
	static void LoadDataBase();//控制打开和检查的函数
};
class BookOpe {
public:
	enum class Result { Success, Fail, Exist };
	static Result Insert(BookData&);
	static Result Delete(string& isbn);
	static int QueryRow(string& isbn);
	static QSqlRecord Query(string& isbn);
};