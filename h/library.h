#pragma once
#include <bits/stdc++.h>
using namespace std;

class TitleInfo {//书的基本信息，固定
protected:
	char _isbn[13], _name[51], _author[31], _publisher[31];
public:
	void SetName(const char* const& name);
	void SetISBN(const char* const& isbn);
	void SetAuthor(const char* const& author);
	void SetPub(const char* const& publisher);
	const char* GetISBN()const;
	const char* GetName()const;
	const char* GetAuth()const;
	const char* GetPub()const;
};
class BookData :public TitleInfo {//书的所有信息，可变的，数量等
protected:

	char _date_added[15];
	int _qty;
	double _whosale, _retail;//批发价、零售价
public:
	void SetDateAdded(const char* const&);
	void SetQty(int);
	void SetWholesale(double);
	void SetRetail(double);
	const char* GetDateAdded()const;
	double GetWholesale()const;
	double GetRetail()const;
	int GetQty()const;
	bool operator <(const BookData& rhs)const;

};
typedef  map< string, shared_ptr<BookData> > Books;
typedef Books::iterator BooksIt;
class Sale;
class ShoppingItem
{
	BookData* _book_ptr_;
	int _num_;
public:
	ShoppingItem(BookData* ptr, int num);
	friend Sale;
};
class Sale {
public:
	enum AddStatus { //表示添加状态的常数
	};
	static constexpr AddStatus SUCCESS = static_cast<AddStatus>(0x01);
	static constexpr AddStatus EXIST = static_cast<AddStatus>(0x02);
	static constexpr AddStatus OVERQTY = static_cast<AddStatus>(0x04);
	Sale();
	double GetSum();
	double GetSumFaxed();
	static double GetFax();
	static void SetFax(const char * fax_str);
	static void SetFax(double fax);
	void Sattle();
	void AddItem(BookData* &,int& num,int& status,int& row);//既要返回状态，又要返回插入行，无奈，出此对策，传进来状态和行数的引用
	bool IsEmpty();
	BookData* choose_book;
	int FindItem(const BookData*);
	bool ChangeItem(int row,int num);
	void Clear();
	int GetNum(int row);
	double GetRetail(int row);
	int GetQty(int row);
	void DeleteItem(int row);
private:
	vector <ShoppingItem> _cart_;//购物车
	static double _fax_;
	double _sum_;
};

class Management {
public:
	enum class FindWhere { NAME, AUTHOR, PUBLISHER };
	static bool FindISBN(BooksIt& it, string& isbn);//根据ISBN查找书
	static bool FindISBN(string &);//根据ISBN查找书
	static bool Add(BookData*& book_ptr);
	static bool Delete(BooksIt& it);
	static bool Edit(BooksIt& it, BookData* book_ptr);
	static void FindEqual(list <shared_ptr<BookData> >& results,string& content,map <FindWhere,bool> &find_where);
	static void FindInclude(list <shared_ptr<BookData> > & results,string & content, map <FindWhere, bool>& find_where);
};
class Report {
public:
	static void SetBookVec();
	static void Sort(string &key);
	static vector <shared_ptr<BookData>> _book_vec;
};
class SortMethod
{
public:
	static bool NamePositive(const shared_ptr<BookData>& a, const shared_ptr<BookData>& b);
	static bool NameBackward(const shared_ptr<BookData>& a, const shared_ptr<BookData>& b);
	static bool DateAddedPositive(const shared_ptr<BookData>& a, const shared_ptr<BookData>& b);
	static bool DateAddedBackward(const shared_ptr<BookData>& a, const shared_ptr<BookData>& b);
	static bool QtyPositive(const shared_ptr<BookData>& a, const shared_ptr<BookData>& b);
	static bool QtyBackward(const shared_ptr<BookData>& a, const shared_ptr<BookData>& b);
	static bool RetailPositive(const shared_ptr<BookData>& a, const shared_ptr<BookData>& b);
	static bool RetailBackward(const shared_ptr<BookData>& a, const shared_ptr<BookData>& b);
	static bool WholesalePositive(const shared_ptr<BookData>& a, const shared_ptr<BookData>& b);
	static bool WholesaleBackward(const shared_ptr<BookData>& a, const shared_ptr<BookData>& b);
};