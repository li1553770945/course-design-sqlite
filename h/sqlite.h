/*sqlite.h
	1.声明了数据库相关的操作：打开，关闭，创建表，自检等
	2.定义了图书的一些操作，插入，删除等，因为主要是读写数据库，因此放在了这里，没有放在global.h
*/
#pragma once
#include <QSqlDatabase>
#include "../h/library.h"
#include <QSqlError>
#include <QSqlQuery>
class Sqlite {//数据库的一些操作
public:
	static QSqlDatabase _database;//数据库
	static bool Open();//打开或创建链接
	static bool CreateBooksTable();//创建books数据表
	static bool Close();//关闭连接
	static void LoadDataBase();//控制打开和检查的函数
};
class BookOpe {//书的一些操作
public:
	enum class Result { Success, Fail, Exist };//用于标识插入/删除的结果
	static Result Insert(BookData&);//插入一本书，如果存在返回Result::Exit，未知错误失败返回Result::Fail
	static Result Delete(string& isbn);//根据传入的isbn，删除一本书
	static int QueryRow(string& isbn);//查询一本书所在的行数，若不存在返回-1。主要是为了判断是否存在
	static QSqlRecord Query(string& isbn);//根据传入的isbn，查找一本书的信息，返回QSqlRecord，如果不存在，返回结果的isValid()为false，需要调用端判断
};