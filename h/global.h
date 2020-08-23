/*global.h
	声明一些全局用到的函数，例如加载配置文件，字符串与小数的转换函数
*/
#pragma once
#include "../GUIh/MainWindow.h"
#include <QSqlTableModel>

int my_atoi(const char* const&);//将字符串转成整数，如果不是整数返回-1
double my_atof(const char* const&);//将字符串转成小数，如果不是小数则返回-1	
bool LoadConfig();//加载配置文件（税率等信息）
int ChineseConvertPy(const std::string& dest_chinese, std::string& out_py);//将汉字转化成拼音，非自己完成，原地址： https://www.jianshu.com/p/ef6803031978
