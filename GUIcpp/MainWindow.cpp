#include "../GUIh/MainWindow.h"
#include "../GUIh/SaleWindow.h"
#include "../GUIh/ReportWindow.h"
#include "../GUIh/ManageWindow.h"
#include "../GUIh/AboutWindow.h"
#include "../h/global.h"
#include <qmessagebox.h>
#include <QCloseEvent> 
#include <QProgressDialog>
#include <qthread.h>
#include "../h/sqlite.h"
#include <qdebug.h>
# pragma execution_character_set("utf-8")
MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	sale_window=NULL;
	manage_window = NULL;
	report_window=NULL;
	this->setAttribute(Qt::WA_DeleteOnClose);
	LoadFile();
	ui.setupUi(this);
	
}
void MainWindow::LoadFile()
{
	try 
	{
		Sqlite::LoadDataBase();//尝试加载数据库
		LoadConfig();//尝试加载配置文件（税率等等）
	}
	catch (QString err)
	{
		QMessageBox box(QMessageBox::Critical, "错误", err);
		box.exec();
		exit(EXIT_FAILURE);
	}
	
}
void MainWindow::on_ButtonSale_clicked()
{
	if (manage_window != NULL)//为了防止收银的同时进行修改，规定收银和管理窗口智能同时打开一个
	{
		QMessageBox box(QMessageBox::Information, "提示", "请先关闭管理窗口！");
		box.exec();
		return;
	}
	if (sale_window == NULL)//如果为空，说明还没有打开过这个窗口，那么就新建一个并显示
	{
		
		sale_window = new SaleWindow(this);
		connect(sale_window, SIGNAL(Close(std::string)), this, SLOT(CloseSon(std::string)));
		sale_window->show();
		
	}
	else//如果已经打开了，不再重新创建，而是显示原来的
	{
		sale_window->showNormal();
		sale_window->activateWindow();
	}
}
void MainWindow::on_ButtonManage_clicked()//和收银模块同理
{
	if (sale_window != NULL)
	{
		QMessageBox box(QMessageBox::Information, "提示", "请先关闭收银窗口！");
		box.exec();
		return;
	}
	if (manage_window == NULL)
	{

		manage_window = new ManageWindow(this);
		connect(manage_window, SIGNAL(Close(std::string)), this, SLOT(CloseSon(std::string)));
		manage_window->show();

	}
	else
	{
		manage_window->showNormal();
		manage_window->activateWindow();
	}
}
void MainWindow::on_ButtonReport_clicked()
{
	if (report_window == NULL)
	{
		report_window = new ReportWindow(this);
		connect(report_window, SIGNAL(Close(std::string)), this, SLOT(CloseSon(std::string)));
		report_window->show();
	}
	else
	{
		report_window->showNormal();
		report_window->activateWindow();
	}
}
void MainWindow::on_ButtonExit_clicked()//点击关闭按钮
{
	this->close();
}
void MainWindow::closeEvent(QCloseEvent* event)
{
	if (manage_window != NULL || sale_window != NULL || report_window != NULL)//子窗口还有没关闭的，阻止主窗口关闭
	{
		QMessageBox box(QMessageBox::Warning, "错误", "请先关闭已打开的子窗口！");
		box.exec();
		event->ignore();
		return;
	}
	QMessageBox messageBox(QMessageBox::Warning, "警告", "您确定要退出吗?", QMessageBox::Yes | QMessageBox::No, NULL);//弹窗确认
	switch (messageBox.exec())
	{
	case QMessageBox::Yes:
	
		Sqlite::Close();//关闭数据库连接
		break;
	default:
		event->ignore();
	}
	
}
void MainWindow::CloseSon(std::string name)//子窗口关闭，要将本窗口的指针置位NULL
{
	if (name == "sale")
	{
		sale_window = NULL;
	}
	else if (name == "manage")
	{
		manage_window = NULL;
	}
	else if  (name == "report")
	{
		report_window = NULL;
	}
}
void MainWindow::on_ActionAbout_triggered()//关于窗口
{
	AboutWindow* about_window = new AboutWindow;
	about_window->exec();
}