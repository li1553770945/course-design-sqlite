#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_SaleWindow.h"
#include "../h/library.h"
#include "../GUIh/FindWindow.h"
#include "../GUIh/ReportWindow.h"
#include "../model_h/Sale.h"
class SaleWindow : public QMainWindow
{
	Q_OBJECT

public:
	SaleWindow(QWidget* parent);//构造函数
signals:
	void Close(std::string);//关闭的时候告诉父窗口
	void SendBook(QSqlRecord);//点击详细信息时，给打开的书的信息窗口发送当前书的信息
private:
	Ui::SaleWindowClass ui;
	SaleModel *sale_model;//创建model
	QSqlRecord _q_record_;//保存当前要添加到购物车的书的信息，也就是输入ISBN按下回车键的时候的查询结果
	void closeEvent(QCloseEvent* event);
	bool _add_enable_;//是否能增加，比如刚一打开时没有输入ISBN，不能增加
	void  AddEnable(bool);//处理能否增加的相应动作，例如不能增加时增加按钮不可点击
	ReportWindow* report_window;//打开书库窗口的指针
	FindWindow* find_window;//打开查找窗口的指针
	void FormatTableHeader();/*格式化标题，例如每次查询后将第一列列宽设置自动调整
							 如果没有本函数，在构造函数里直接设置为列宽按内容调整但没有内容会崩溃*/
	int _delete_row_;//点击右键选择要删除的行数

private slots:
	void on_Confirm_clicked();//输入ISBN，点击确定按钮的槽函数
	void on_ISBN_returnPressed();//输入ISBN按下回车，调用on_Confirm_clicked();
	void on_ButtonDetail_clicked();//点击详细信息按钮，打开书的信息窗口
	void on_ButtonLibrary_clicked();//点击书库按钮，打开书库窗口
	void SonClose(std::string);//处理子窗口关闭的函数
	void on_ButtonAddToCart_clicked();//点击添加到购物车按钮的槽函数
	void on_Num_returnPressed();//在数量输入框按下回车，调用on_ButtonAddToCart_clicked();
	void on_ButtonSattle_clicked();//点击结算按钮
	void on_ButtonFind_clicked();////点击查找按钮，打开查找窗口
	void on_ButtonClear_clicked();//点击清空按钮，清空所有信息
	void on_TableCart_customContextMenuRequested(const QPoint& pos);//右键购物车中的书，弹出菜单，用于处理删除
	void Delete();//删除购物车中的一条
	void ItemChange(QStandardItem*);//直接在购物车中双击修改数目
};

