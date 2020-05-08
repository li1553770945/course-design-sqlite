#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
#include "../h/library.h"
using namespace std;
void TitleInfo::SetName(const char * const &name)
{
	if (strlen(name) > 50)
		throw "�������ܳ���50���ַ���";
	if (strlen(name) == 0)
		throw "������������";
	strcpy(_name, name);
}
void TitleInfo::SetISBN(const char* const&isbn)
{
	if (strlen(isbn) > 13)
		throw "ISBN��Ų��ܳ���13���ַ���";
	if (strlen(isbn) == 0)
		throw "������ISBN";
	for (int i = 0; i < strlen(isbn); i++)
		if (!(isbn[i] >= '0' && isbn[i] <= '9'))
			throw "ISBNֻ���Ǵ����֣�";

	strcpy(_isbn, isbn);
}
void TitleInfo::SetAuthor(const char * const&auth)
{
	if(strlen(auth)>30)
		throw "���߲��ܳ���30���ַ�!";
	if (strlen(auth) == 0)
		throw "���������ߣ�";
	strcpy(_author, auth);
	
}
void TitleInfo::SetPub(const char* const &Pub)
{
	if(strlen(Pub)>30)
		throw "�����粻�ܳ���30���ַ�!";
	if (strlen(Pub) == 0)
		throw "����������磡";
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