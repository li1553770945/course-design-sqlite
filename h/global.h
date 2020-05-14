#pragma once
#include "../GUIh/MainWindow.h"
#include <QSqlTableModel>

int my_atoi(const char* const&);
double my_atof(const char* const&);
bool LoadConfig();
int ChineseConvertPy(const std::string& dest_chinese, std::string& out_py);//本函数非自己完成，原地址： https://www.jianshu.com/p/ef6803031978
