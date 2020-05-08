#include "../h/library.h"
#include "../h/global.h"
Sale::Sale()
{
	_sum_ = 0;
	choose_book = NULL;
}
double Sale::GetFax()
{
	return _fax_;
}
void Sale::SetFax(const char* fax_str)
{
	double fax = my_atof(fax_str);
	if (fax<0)
	{
		throw "税率只能是不小于零的小数！";
	}
	_fax_ = fax;
}
void Sale::SetFax(double fax)
{
	_fax_ = fax;
}
double Sale::_fax_ = 0.06;
ShoppingItem::ShoppingItem(BookData *ptr,int num)
{
	_book_ptr_ = ptr;
	_num_ = num;
}
void Sale::AddItem(BookData* & book_ptr, int &num,int &status,int& row)
{
	int find_row = FindItem(book_ptr);
	if (find_row == -1)
	{
		if (num > book_ptr->GetQty())
		{
			status = OVERQTY;
			return;
		}
		_cart_.push_back(ShoppingItem(book_ptr, num));
		_sum_ += book_ptr->GetRetail() * num;
		status = SUCCESS;
		row =_cart_.size()-1;
		return;
	}
	else
	{
		row = find_row;
		if (num + _cart_[find_row]._num_ > _cart_[find_row]._book_ptr_->GetQty())
		{
			status = EXIST | OVERQTY;
		}
		else
		{
			_sum_ += num * _cart_[find_row]._book_ptr_->GetRetail();
			num += _cart_[find_row]._num_;
			 _cart_[find_row]._num_ = num;
			 status = EXIST|SUCCESS;
			
		}
	}
}
void Sale::Sattle()
{
	for (auto item : _cart_)
	{
		item._book_ptr_->SetQty(item._book_ptr_->GetQty() - item._num_);
	}
	_cart_.clear();
}
bool Sale::IsEmpty()
{
	return _cart_.empty();
}
int Sale::FindItem(const BookData* find_book)
{
	for (int i=0; i < _cart_.size(); i++)
	{
		if (_cart_[i]._book_ptr_ == find_book)
			return i;
	}
	return -1;
}
double Sale::GetSum()
{
	return _sum_;
}
double Sale::GetSumFaxed()
{
	return _sum_*(1+_fax_);
}
void Sale::Clear()
{
	_cart_.clear();
	_sum_ = 0;
}
bool Sale::ChangeItem(int row,int num)
{
	if (num > _cart_[row]._book_ptr_->GetQty())
		return false;
	else
	{
		_sum_ += (num - _cart_[row]._num_) * (_cart_[row]._book_ptr_->GetRetail());
		_cart_[row]._num_ = num;
		return true;
	}
}
int Sale::GetNum(int row)
{
	return _cart_[row]._num_;
}
double Sale::GetRetail(int row)
{
	return _cart_[row]._book_ptr_->GetRetail();
}
int Sale::GetQty(int row)
{
	return _cart_[row]._book_ptr_->GetQty();
}
void Sale::DeleteItem(int row)
{
	cout << row;
	_sum_ -= _cart_[row]._num_ * _cart_[row]._book_ptr_->GetRetail();
	_cart_.erase(_cart_.begin()+row);
}