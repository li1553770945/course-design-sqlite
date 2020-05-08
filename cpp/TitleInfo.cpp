#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
#include "../h/library.h"
using namespace std;
void TitleInfo::SetName(const char * const &name)
{
	if (strlen(name) > 50)
		throw "书名不能超过50个字符！";
	if (strlen(name) == 0)
		throw "请输入书名！";
	strcpy(_name, name);
}
void TitleInfo::SetISBN(const char* const&isbn)
{
	if (strlen(isbn) > 13)
		throw "ISBN编号不能超过13个字符！";
	if (strlen(isbn) == 0)
		throw "请输入ISBN";
	for (int i = 0; i < strlen(isbn); i++)
		if (!(isbn[i] >= '0' && isbn[i] <= '9'))
			throw "ISBN只能是纯数字！";

	strcpy(_isbn, isbn);
}
void TitleInfo::SetAuthor(const char * const&auth)
{
	if(strlen(auth)>30)
		throw "作者不能超过30个字符!";
	if (strlen(auth) == 0)
		throw "请输入作者！";
	strcpy(_author, auth);
	
}
void TitleInfo::SetPub(const char* const &Pub)
{
	if(strlen(Pub)>30)
		throw "出版社不能超过30个字符!";
	if (strlen(Pub) == 0)
		throw "请输入出版社！";
	strcpy(_publisher ,Pub);
}
const char* TitleInfo::GetISBN()const 
{
	return _isbn;
}
const char* TitleInfo::GetName()const
{
	return _name;
}
const char* TitleInfo::GetAuth()const
{
	return _author;
}
const char* TitleInfo::GetPub()const
{
	return _publisher;
}