/*
	library.h
	֮���������������Ϊԭ��д��û�������ݿ⣬д�˺ö���Ч�Լ�飬��Ϊ�����ݿ�󣬱�������Щ����
	������������������Ч�ԣ�ͬʱ����һ�������Ϣ
*/
#pragma once
#include <bits/stdc++.h>
using namespace std;

class TitleInfo {//��Ļ�����Ϣ���̶�
protected:
	char _isbn[13], _name[51], _author[31], _publisher[31];//����Ӣ�����˼��
public:
	void SetName(const char* const& name);//���������������Ч��throwһ��const char *�Ĵ��󣬲���������ԭ��
	void SetISBN(const char* const& isbn);//����ISBN�������Ч��throwһ��const char *�Ĵ��󣬲���������ԭ��
	void SetAuthor(const char* const& author);//�������ߣ������Ч��throwһ��const char *�Ĵ��󣬲���������ԭ��
	void SetPub(const char* const& publisher);//���ó����磬�����Ч��throwһ��const char *�Ĵ��󣬲���������ԭ��
	const char* GetISBN()const;
	const char* GetName()const;
	const char* GetAuth()const;
	const char* GetPub()const;
};
class BookData :public TitleInfo {//���������Ϣ���ɱ�ģ�������
protected:

	char _date_added[15];//��������
	int _qty;//���
	double _whosale, _retail;//�����ۡ����ۼ�
public:
	void SetDateAdded(const char* const&);//���ý������ڣ������Ч��throwһ��const char *�Ĵ��󣬲���������ԭ��
	void SetQty(int);//���ÿ�棬�����Ч��throwһ��const char *�Ĵ��󣬲���������ԭ��
	void SetWholesale(double);//���������ۣ������Ч��throwһ��const char *�Ĵ��󣬲���������ԭ��
	void SetRetail(double);//�������ۼۣ������Ч��throwһ��const char *�Ĵ��󣬲���������ԭ��
	const char* GetDateAdded()const;
	double GetWholesale()const;
	double GetRetail()const;
	int GetQty()const;
};