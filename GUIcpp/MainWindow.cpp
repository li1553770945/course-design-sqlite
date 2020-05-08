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
# pragma execution_character_set("utf-8")
MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	sale_window=NULL;
	manage_window = NULL;
	report_window=NULL;
	LoadFile();
	ui.setupUi(this);
	this->setAttribute(Qt::WA_DeleteOnClose);
}
void  OpenFileThread::run()
{
	emit OpenResult(OpenFile());
	emit ProcessEnd();
}
void SaveFileThread::run()
{
	SaveFile();
	emit ProcessEnd();
}
void MainWindow::CloseProcess()
{
	_dialog_->close();
	delete _dialog_;
}
void MainWindow::HandleResult(bool result)
{
	if (!result)
	{
		QMessageBox box(QMessageBox::Critical, "错误", "无法打开书库文件！");
		box.exec();
		exit(EXIT_FAILURE);
	}
}
void MainWindow::LoadFile()
{
	if(AccessFile())
	{ 
		_dialog_ = new QProgressDialog("正在读取文件...请勿关闭程序或您的计算机", 0, 0, 0,this);
		_dialog_->setWindowTitle("读取文件");
		OpenFileThread thread;
		connect(&thread, SIGNAL(ProcessEnd()), this, SLOT(CloseProcess()));
		connect(&thread, SIGNAL(OpenResult(bool)), this, SLOT(HandleResult(bool)));
		thread.start();
		_dialog_->exec();
		thread.wait();
	}
	else
	{
		QMessageBox box(QMessageBox::Warning, "警告", "书库文件不存在，将尝试创建");
		box.exec();
		//尝试创建
		if (CreateFile())
		{
			if (!OpenFile())
			{
				QMessageBox box(QMessageBox::Critical, "错误", "创建已成功，但无法打开文件！");
				box.exec();
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			QMessageBox box(QMessageBox::Critical, "错误", "无法创建书库文件！");
			box.exec();
			exit(EXIT_FAILURE);
		}
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
void MainWindow::on_ButtonManage_clicked()
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
void MainWindow::on_ButtonExit_clicked()
{
	this->close();
}
void MainWindow::closeEvent(QCloseEvent* event)
{
	if (manage_window != NULL || sale_window != NULL || report_window != NULL)
	{
		QMessageBox box(QMessageBox::Warning, "错误", "请先关闭已打开的子窗口！");
		box.exec();
		event->ignore();
		return;
	}
	QMessageBox messageBox(QMessageBox::Warning, "警告", "您确定要退出吗?", QMessageBox::Yes | QMessageBox::No, NULL);
	switch (messageBox.exec())
	{
	case QMessageBox::Yes:
	{
		_dialog_ = new QProgressDialog("正在保存文件...请勿关闭程序或您的计算机", 0, 0, 0,this);
		_dialog_->setWindowTitle("保存文件");
		SaveFileThread thread;
		connect(&thread, SIGNAL(ProcessEnd()), this, SLOT(CloseProcess()));
		thread.start();
		_dialog_->exec();
		thread.wait();
		exit(0);
	}
	default:
		event->ignore();
	}
	
}
void MainWindow::CloseSon(std::string name)
{
	if (name == "sale")
	{
		sale_window = NULL;
	}
	else if (name == "manage")
	{
		manage_window = NULL;
	}
	else if (name == "report")
	{
		report_window = NULL;
	}
}
void MainWindow::on_ActionAbout_triggered()
{
	AboutWindow* about_window = new AboutWindow;
	about_window->exec();
}
void MainWindow::on_ActionSave_triggered()
{
	_dialog_ = new QProgressDialog("正在保存文件...请勿关闭程序或您的计算机", 0, 0, 0,this);
	_dialog_->setWindowTitle("保存文件");
	SaveFileThread thread;
	connect(&thread, SIGNAL(ProcessEnd()), this, SLOT(CloseProcess()));
	thread.start();
	_dialog_->exec();
	thread.wait();
	QMessageBox box(QMessageBox::Information, "提示", "保存成功！");
	box.exec();
}