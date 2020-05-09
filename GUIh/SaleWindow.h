#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_SaleWindow.h"
#include "../h/library.h"
#include "../GUIh/FindWindow.h"
#include "../GUIh/ReportWindow.h"
class Cart
{
public:
	int num;
};
class SaleWindow : public QMainWindow
{
	Q_OBJECT

public:
	SaleWindow(QWidget* parent = Q_NULLPTR);
	static double _fax;
signals:
	void Close(std::string);

private:
	//Sale _sale_;
	Ui::SaleWindowClass ui;
	//void closeEvent(QCloseEvent* event);
	//bool select;
	//void Select(bool);
	//ReportWindow* report_window;
	//FindWindow* find_window;
	//int _delete_row_;

private slots:
	/*void on_Confirm_clicked();
	void on_ISBN_returnPressed();
	void on_ButtonDetail_clicked();
	void on_ButtonLibrary_clicked();
	void on_ButtonAddToCart_clicked();
	void on_Num_returnPressed();
	void on_ButtonSattle_clicked();
	void on_ButtonFind_clicked();
	void SonClose(std::string);
	void on_ButtonClear_clicked();
	void on_TableCart_cellChanged(int, int);
	void on_TableCart_customContextMenuRequested(const QPoint& pos);
	void Delete();*/
};

