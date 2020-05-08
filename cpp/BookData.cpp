#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
#include "../h/library.h"
using namespace std;
void BookData::SetDateAdded(const char* const & date)
{
	
	strcpy(_date_added, date);
	
}
void BookData::SetQty(int qty)
{
	if (qty < 0)
		throw "库存输入错误！,请输入不小于0的整数！";
	_qty = qty;
}
void BookData::SetWholesale(double price)
{
	if (price < 0)
		throw "批发价输入错误！请输入不小于0的小数！";
	_whosale = price;
}
void BookData::SetRetail(double price)
{
	if (price < 0)
		throw "零售价输入错误！请输入不小于0的小数！";
	_retail = price;
}
const char* BookData::GetDateAdded()const
{
	return _date_added;
}
double BookData::GetWholesale()const
{
	return _whosale;
}
double BookData::GetRetail()const
{
	return _retail;
}
int BookData::GetQty()const 
{
	return _qty;
}
bool BookData::operator<(const BookData &rhs)const 
{
	return strcmp(_isbn, rhs.GetISBN())<0;
}