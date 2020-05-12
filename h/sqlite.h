#pragma once
#include <QSqlDatabase>
class Sqlite {
public:
	static QSqlDatabase _database;
	static bool Open();
	static bool CreateBooksTable();
	static bool Close();
	static void LoadDataBase();
};