#pragma once
#include "library.h"
#include <bits/stdc++.h>
using namespace std;
typedef  map< string, shared_ptr<BookData> > Books;
typedef Books::iterator BooksIt;
extern Books books;
int my_atoi(const char* const&);
double my_atof(const char* const&);
bool AccessFile();
bool OpenFile();
bool CreateFile();
void SaveFile();