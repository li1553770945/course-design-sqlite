#pragma once
#include "../GUIh/MainWindow.h"
#include <QSqlTableModel>

int my_atoi(const char* const&);
double my_atof(const char* const&);
bool LoadConfig();
int ChineseConvertPy(const std::string& dest_chinese, std::string& out_py);//���������Լ���ɣ�ԭ��ַ�� https://www.jianshu.com/p/ef6803031978
