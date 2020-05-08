#include "../h/library.h"
#include "../h/global.h"
vector <shared_ptr<BookData>> Report:: _book_vec;
void Report::SetBookVec()
{
	_book_vec.clear();
	for (auto book : books)
	{
		_book_vec.push_back(book.second);
	}
}
void Report::Sort(string &key)
{
	if (key=="name")
	{
		sort(_book_vec.begin(), _book_vec.end(),SortMethod::NamePositive);
	}
	if (key == "-name")
	{
		sort(_book_vec.begin(), _book_vec.end(), SortMethod::NameBackward);
	}
	if (key == "qty")
	{
		sort(_book_vec.begin(), _book_vec.end(), SortMethod::QtyPositive);
	}
	if (key == "-qty")
	{
		sort(_book_vec.begin(), _book_vec.end(), SortMethod::QtyBackward);
	}
	if (key == "date_added")
	{
		sort(_book_vec.begin(), _book_vec.end(), SortMethod::DateAddedPositive);
	}
	if (key == "-date_added")
	{
		sort(_book_vec.begin(), _book_vec.end(), SortMethod::DateAddedBackward);
	}
	if (key == "retail")
	{
		sort(_book_vec.begin(), _book_vec.end(), SortMethod::RetailPositive);
	}
	if (key == "-retail")
	{
		sort(_book_vec.begin(), _book_vec.end(), SortMethod::RetailBackward);
	}
	if (key == "wholesale")
	{
		sort(_book_vec.begin(), _book_vec.end(), SortMethod::WholesalePositive);
	}
	if (key == "-wholesale")
	{
		sort(_book_vec.begin(), _book_vec.end(), SortMethod::WholesaleBackward);
	}
}
bool SortMethod::NamePositive(const shared_ptr<BookData>& a, const shared_ptr<BookData>& b)
{
	return (strcmp(a->GetName(), b->GetName()) < 0);
}
bool SortMethod::NameBackward(const shared_ptr<BookData>& a, const shared_ptr<BookData>& b)
{
	return (strcmp(a->GetName(), b->GetName()) > 0);
}
bool SortMethod::QtyPositive(const shared_ptr<BookData>& a, const shared_ptr<BookData>& b)
{
	return a->GetQty() < b->GetQty();
}
bool SortMethod::QtyBackward(const shared_ptr<BookData>& a, const shared_ptr<BookData>& b)
{
	return a->GetQty() > b->GetQty();
}
bool SortMethod::DateAddedPositive(const shared_ptr<BookData>& a, const shared_ptr<BookData>& b)
{
	return (strcmp(a->GetDateAdded(), b->GetDateAdded()) < 0);
}
bool SortMethod::DateAddedBackward(const shared_ptr<BookData>& a, const shared_ptr<BookData>& b)
{
	return (strcmp(a->GetDateAdded(), b->GetDateAdded()) > 0);
}
bool SortMethod::RetailPositive(const shared_ptr<BookData>& a, const shared_ptr<BookData>& b)
{
	return a->GetRetail() < b->GetRetail();
}
bool SortMethod::RetailBackward(const shared_ptr<BookData>& a, const shared_ptr<BookData>& b)
{
	return a->GetRetail() > b->GetRetail();
}bool SortMethod::WholesalePositive(const shared_ptr<BookData>& a, const shared_ptr<BookData>& b)
{
	return a->GetWholesale() < b->GetWholesale();
}
bool SortMethod::WholesaleBackward(const shared_ptr<BookData>& a, const shared_ptr<BookData>& b)
{
	return a->GetWholesale() > b->GetWholesale();
}