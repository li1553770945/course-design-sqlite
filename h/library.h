/*
	library.h
	之所以有这个，是因为原来写的没有用数据库，写了好多有效性检查，改为用数据库后，保留了这些内容
	可以用来检查输入的有效性，同时传递一本书的信息
*/
#pragma once
#include <bits/stdc++.h>
using namespace std;

class TitleInfo {//书的基本信息，固定
protected:
	char _isbn[13], _name[51], _author[31], _publisher[31];//都是英语，顾名思义
public:
	void SetName(const char* const& name);//设置书名，如果无效会throw一个const char *的错误，并包含错误原因
	void SetISBN(const char* const& isbn);//设置ISBN，如果无效会throw一个const char *的错误，并包含错误原因
	void SetAuthor(const char* const& author);//设置作者，如果无效会throw一个const char *的错误，并包含错误原因
	void SetPub(const char* const& publisher);//设置出版社，如果无效会throw一个const char *的错误，并包含错误原因
	const char* GetISBN()const;
	const char* GetName()const;
	const char* GetAuth()const;
	const char* GetPub()const;
};
class BookData :public TitleInfo {//书的所有信息，可变的，数量等
protected:

	char _date_added[15];//进货日期
	int _qty;//库存
	double _whosale, _retail;//批发价、零售价
public:
	void SetDateAdded(const char* const&);//设置进货日期，如果无效会throw一个const char *的错误，并包含错误原因
	void SetQty(int);//设置库存，如果无效会throw一个const char *的错误，并包含错误原因
	void SetWholesale(double);//设置批发价，如果无效会throw一个const char *的错误，并包含错误原因
	void SetRetail(double);//设置零售价，如果无效会throw一个const char *的错误，并包含错误原因
	const char* GetDateAdded()const;
	double GetWholesale()const;
	double GetRetail()const;
	int GetQty()const;
};