#include <bits/stdc++.h>
#include "../h/library.h"
#include "../h/global.h"
using namespace std;
bool Management::FindISBN(BooksIt & it,string & isbn)//根据ISBN查找书
{
	 it = books.find(isbn);
	if (it != books.end())
		return true;
	else
		return false;
}
bool Management::FindISBN(string &isbn)//根据ISBN查找书
{
	BooksIt it=books.find(isbn);
	if (it != books.end())
		return true;
	else
		return false;
}
bool Management::Add(BookData*& book_ptr)
{
	if (FindISBN(string(book_ptr->GetISBN())))
		return false;
	else
	{
		shared_ptr <BookData> book_p(book_ptr);
		books.insert(make_pair(string(book_p->GetISBN()), book_p));
		return true;
	}
	
}
bool Management::Delete(BooksIt& it)
{
	books.erase(it);
	return true;
}
bool Management::Edit(BooksIt& it, BookData* book_ptr)
{
	shared_ptr<BookData> shared_p(book_ptr);
	it->second = shared_p;
	return true;
}
void Management::FindEqual(list <shared_ptr<BookData> >& results,string& content, map <FindWhere, bool>& find_where)
{
	results.clear();
	for (auto book : books)
	{
		if (find_where[FindWhere::NAME]==true&&!strcmp(book.second->GetName(),content.data()))
		{
			
			results.push_back(book.second);
			continue;
		}
		if (find_where[FindWhere::AUTHOR] == true && !strcmp(book.second->GetAuth(), content.data()))
		{
			results.push_back(book.second);
			continue;
		}
		if (find_where[FindWhere::PUBLISHER] == true && !strcmp(book.second->GetPub(), content.data()))
		{
			results.push_back(book.second);
			continue;
		}
	}
}
void Management::FindInclude(list <shared_ptr<BookData> >& results,string & content, map <FindWhere, bool>& find_where)
{
	results.clear();
	for (auto book : books)
	{
		if (find_where[FindWhere::NAME] == true &&string(book.second->GetName()).find(content)!=string::npos)
		{
			results.push_back(book.second);
			continue;
		}
		if (find_where[FindWhere::AUTHOR] == true && string(book.second->GetAuth()).find(content) != string::npos)
		{
			results.push_back(book.second);
			continue;
		}
		if (find_where[FindWhere::PUBLISHER] == true && string(book.second->GetPub()).find(content) != string::npos)
		{
			results.push_back(book.second);
			continue;
		}
	}
}

