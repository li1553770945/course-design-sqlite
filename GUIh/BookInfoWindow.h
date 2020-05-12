#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_BookInfoWindow.h"
#include "../h/library.h"
#include <qsqlrecord.h>
class BookInfoWindow : public QDialog
{
	Q_OBJECT

public:
	BookInfoWindow(QWidget* parent = Q_NULLPTR);
private slots:
	void ReceiveBook(QSqlRecord);//接受书的信息
private:
	Ui::BookInfoWindowClass ui;
};