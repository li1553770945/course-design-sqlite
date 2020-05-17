/*sqlite.h
	1.���������ݿ���صĲ������򿪣��رգ��������Լ��
	2.������ͼ���һЩ���������룬ɾ���ȣ���Ϊ��Ҫ�Ƕ�д���ݿ⣬��˷��������û�з���global.h
*/
#pragma once
#include <QSqlDatabase>
#include "../h/library.h"
#include <QSqlError>
#include <QSqlQuery>
class Sqlite {//���ݿ��һЩ����
public:
	static QSqlDatabase _database;//���ݿ�
	static bool Open();//�򿪻򴴽�����
	static bool CreateBooksTable();//����books���ݱ�
	static bool Close();//�ر�����
	static void LoadDataBase();//���ƴ򿪺ͼ��ĺ���
};
class BookOpe {//���һЩ����
public:
	enum class Result { Success, Fail, Exist };//���ڱ�ʶ����/ɾ���Ľ��
	static Result Insert(BookData&);//����һ���飬������ڷ���Result::Exit��δ֪����ʧ�ܷ���Result::Fail
	static Result Delete(string& isbn);//���ݴ����isbn��ɾ��һ����
	static int QueryRow(string& isbn);//��ѯһ�������ڵ��������������ڷ���-1����Ҫ��Ϊ���ж��Ƿ����
	static QSqlRecord Query(string& isbn);//���ݴ����isbn������һ�������Ϣ������QSqlRecord����������ڣ����ؽ����isValid()Ϊfalse����Ҫ���ö��ж�
};