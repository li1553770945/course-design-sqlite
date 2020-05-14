#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_SaleWindow.h"
#include "../h/library.h"
#include "../GUIh/FindWindow.h"
#include "../GUIh/ReportWindow.h"
#include "../model_h/Sale.h"
class Cart
{
public:
	int num;
};
class SaleWindow : public QMainWindow
{
	Q_OBJECT

public:
	SaleWindow(QWidget* parent);
signals:
	void Close(std::string);
	void SendBook(QSqlRecord);
private:
	Ui::SaleWindowClass ui;
	SaleModel *sale_model;
	QSqlRecord _q_record_;
	void closeEvent(QCloseEvent* event);
	bool _add_enable_;
	void  AddEnable(bool);
	ReportWindow* report_window;
	FindWindow* find_window;
	void FormatTableHeader();
	int _delete_row_;

private slots:
	void on_Confirm_clicked();
	void on_ISBN_returnPressed();
	void on_ButtonDetail_clicked();
	void on_ButtonLibrary_clicked();
	void SonClose(std::string);
	void on_ButtonAddToCart_clicked();
	void on_Num_returnPressed();
	void on_ButtonSattle_clicked();
	void on_ButtonFind_clicked();
	void on_ButtonClear_clicked();
	void on_TableCart_customContextMenuRequested(const QPoint& pos);
	void Delete();
	void ItemChange(QStandardItem*);
};

