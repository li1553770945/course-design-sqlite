/*
	BookInfoWindow.h
	“书的信息”窗口的头文件
*/
#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_BookInfoWindow.h"
#include "../h/library.h"
#include <qsqlrecord.h>
class BookInfoWindow : public QDialog
{
	Q_OBJECT

public:
	BookInfoWindow(QWidget* parent = Q_NULLPTR);//构造函数
private slots:
	void ReceiveBook(QSqlRecord);//接收一本书的信息用于显示
private:
	Ui::BookInfoWindowClass ui;
};