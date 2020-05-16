#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include "SaleWindow.h"
#include "ReportWindow.h"
#include "MainWindow.h"
#include "ManageWindow.h"
#include <QProgressDialog>
#include <qthread.h>
class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);
public slots:
	void on_ButtonSale_clicked();
	void on_ButtonManage_clicked();
	void on_ButtonReport_clicked();//这里三个函数功能差不多，就是点击按钮时检测是否已经打开窗口，如果没打开就创建
	void on_ButtonExit_clicked();//点击关闭按钮时，调用this->close()函数
	void CloseSon(std::string);//控制子窗口指针，关闭时将指针变为NULL
	void on_ActionAbout_triggered();//点击菜单栏关于时，打开帮助窗口

private:
	Ui::MainWindowClass ui;
	SaleWindow *sale_window;
	ManageWindow *manage_window;
	ReportWindow *report_window;//这里有三个指针，分别指向对应的子窗口，如果指针为NULL，证明没有打开窗口
	void closeEvent(QCloseEvent* event);//在关闭时弹窗确认
	void LoadFile();//加载数据库、配置文件
};
