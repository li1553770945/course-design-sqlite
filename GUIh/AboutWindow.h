/*
	AboutWindow.h
	“关于”窗口的头文件
*/
#pragma once
#include "ui_AboutWindow.h"
class AboutWindow : public QDialog
{
	Q_OBJECT

public:
	AboutWindow(QWidget* parent = Q_NULLPTR);//构造函数，没有具体功能

private:
	Ui::AboutWindowClass ui;
};
