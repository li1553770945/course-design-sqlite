/*global.h
	����һЩȫ���õ��ĺ�����������������ļ����ַ�����С����ת������
*/
#pragma once
#include "../GUIh/MainWindow.h"
#include <QSqlTableModel>

int my_atoi(const char* const&);//���ַ���ת�����������������������-1
double my_atof(const char* const&);//���ַ���ת��С�����������С���򷵻�-1	
bool LoadConfig();//���������ļ���˰�ʵ���Ϣ��
int ChineseConvertPy(const std::string& dest_chinese, std::string& out_py);//������ת����ƴ�������Լ���ɣ�ԭ��ַ�� https://www.jianshu.com/p/ef6803031978
