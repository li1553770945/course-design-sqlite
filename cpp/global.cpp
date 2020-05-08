#include "../h/global.h"
#include <io.h>
Books books;
int my_atoi(const char* const& str)
{
	if (strlen(str) == 0)
		return -1;
	int ans = 0;
	for (int i = 0; i < strlen(str); i++)
	{
		if (str[i] < '0' || str[i]>'9')
			return -1;
		else
		{
			ans *= 10;
			ans += str[i] - '0';
		}
	}
	return ans;
}
double my_atof(const char* const& str)
{
	if (strlen(str) == 0)
		return -1;
	bool point = false;
	int i = 0;
	if (str[i] == '-')
		i++;
	if (str[i] == '.')
		return -1;
	for (; i < strlen(str); i++)
	{
		if (str[i] <= '9' && str[i] >= '0')
			continue;
		if (str[i] == '.')
		{
			if (!point)
			{
				point = true;
				continue;
			}
			else
			{
				return -1;
			}
		}
		else
		{
			return -1;
		}
	}
	return atof(str);
}
bool AccessFile()
{
	return !(_access("book.data", 0) == -1);
}
bool OpenFile()
{
	fstream  file;
	file.open("book.data", ios::binary | ios::in | ios::out);
	if (!file.is_open())
	{
		return false;
	}//读取文件
	while (!file.eof())
	{
		BookData *temp=new BookData;
		shared_ptr<BookData> temp_share(temp);
		file.read((char*)temp, sizeof(BookData));
		if (file.fail())
			break;
		books.insert(make_pair(string(temp->GetISBN()), temp_share));
	}//读入到books
	file.close();
	file.open("config.data", ios::in);
	double fax;
	file >> fax;
	if (!file.fail())
	{
		Sale::SetFax(fax);
	}
	file.close();
	return true;
}
bool CreateFile()
{
	fstream  file;
	file.open("book.data", ios::out);
	file.close();
	if (_access("book.data", 0) == -1)
	{
		return false;
	}
	return true;
}
void SaveFile()
{
	fstream file;
	file.open("book.data", ios::out | ios::binary);
	for (BooksIt it = books.begin();it!=books.end();it++)
	{
		file.write((char*)&*it->second, sizeof(BookData));
	}
	file.close();
	file.open("config.data", ios::out);
	file << Sale::GetFax();
	file.close();
}