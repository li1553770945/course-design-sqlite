#pragma once
#include <QSqlDatabase>
#include "../h/library.h"
#include <QSqlError>
#include <QSqlQuery>
class Sqlite {
public:
	static QSqlDatabase _database;//���ݿ�
	static bool Open();//�򿪻򴴽�����
	static bool CreateBooksTable();//����books���ݱ�
	static bool Close();//�ر�����
	static void LoadDataBase();//���ƴ򿪺ͼ��ĺ���
};
class BookOpe {
public:
	enum class Result { Success, Fail, Exist };
	static Result Insert(BookData&);
	static Result Delete(string& isbn);
	static int QueryRow(string& isbn);
	static QSqlRecord Query(string& isbn);
};