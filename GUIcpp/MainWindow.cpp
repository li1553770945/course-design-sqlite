#include "../GUIh/MainWindow.h"
#include "../GUIh/SaleWindow.h"
#include "../GUIh/ReportWindow.h"
#include "../GUIh/ManageWindow.h"
#include "../GUIh/AboutWindow.h"
#include "../h/global.h"
#include "../h/library.h"
#include <qmessagebox.h>
#include <QCloseEvent> 
#include <QProgressDialog>
#include <qthread.h>
#include "../h/sqlite.h"
#include <qdebug.h>
#include <qfiledialog.h>
#include <xlnt/xlnt.hpp>
#include <Windows.h>
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
		exit(EXIT_SUCCESS);
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
	AboutWindow* about_window = new AboutWindow(this);
	about_window->exec();
}

void MainWindow::on_ActionImportExcel_triggered()
{
	
	//定义文件对话框类
	QFileDialog* file_dialog = new QFileDialog(this);
	file_dialog->setWindowTitle(QStringLiteral("选中文件"));
	file_dialog->setDirectory(".");
	//设置文件过滤器
	file_dialog->setNameFilter("Excel文件(*.xlsx)");
	//设置视图模式
	file_dialog->setViewMode(QFileDialog::Detail);
	//打印所有选择的文件的路径
	QStringList file_names;
	if (file_dialog->exec()) {
		file_names = file_dialog->selectedFiles();
	}
	QString file_name;
	if (file_names.length())
		 file_name = file_names[0];
	else
		return;
	xlnt::workbook wb;
	wb.load(file_name.toStdString());
	xlnt::worksheet ws = wb.active_sheet();
	int row = 2;
	int success=0, fail = 0;
	while (true)
	{
		row++;
		if (!ws.cell(1, row).has_value())
			break;
		for (int i = 1; i <= 8; i++)
		{
			BookData book;
			try
			{
				book.SetName(ws.cell(1,row).to_string().c_str());//设置书名
				book.SetISBN(ws.cell(2, row).to_string().c_str());
				book.SetAuthor(ws.cell(3, row).to_string().c_str());
				book.SetPub(ws.cell(4, row).to_string().c_str());//设置出版社
				book.SetDateAdded(ws.cell(5, row).to_string().c_str());//设置进货日期
				book.SetQty(my_atoi(ws.cell(6, row).to_string().c_str()));//设置库存
				book.SetRetail(my_atof(ws.cell(7, row).to_string().c_str()));//设置零售价
				book.SetWholesale(my_atof(ws.cell(8, row).to_string().c_str()));//设置批发价
				
			}
			catch (const char* err)//如果输入的数据有问题
			{
				fail++;
				break;
			}
			BookOpe::Result result = BookOpe::Insert(book);
			if (result == BookOpe::Result::Success)
			{
				success++;
			}
			else if (result == BookOpe::Result::Exist)
			{
				fail++;
				break;
			}
			else if (result == BookOpe::Result::Fail)
			{
				fail++;
				break;
			}
		}

		
	}
	string message = "共找到" + to_string(row - 3) + "条数据,成功" + to_string(success) + "条,失败" + to_string(fail) + "条";
	QMessageBox box(QMessageBox::Information, "提示", QString::fromStdString(message));
	box.exec();

}
void MainWindow::on_ActionExportExcel_triggered()
{
	
	string GetDateTime();
	xlnt::workbook wb;
	xlnt::worksheet ws = wb.active_sheet();
	ws.merge_cells("A1:H1");
	xlnt::alignment center;
	center.horizontal(xlnt::horizontal_alignment::center);
	ws.cell(1, 1).alignment(center);
	ws.cell(1, 1).value(string("书库管理系统导出 ") + GetDateTime());
	ws.cell(1,2).value("书名");
	ws.cell(2,2).value("ISBN");
	ws.cell(3,2).value("作者");
	ws.cell(4,2).value("出版社");
	ws.cell(5,2).value("进货日期");
	ws.cell(6,2).value("库存");
	ws.cell(7,2).value("零售价");
	ws.cell(8,2).value("批发价");
	QString sql = "SELECT name,isbn,author,publisher,date_added,qty,retail,wholesale FROM books";
	QSqlQuery query;
	query.exec(sql);
	int row = 3;
	while (query.next())
	{
		ws.cell(1, row).value(query.value(0).toString().toStdString());
		ws.cell(2, row).value(query.value(1).toString().toStdString());
		ws.cell(3, row).value(query.value(2).toString().toStdString());
		ws.cell(4, row).value(query.value(3).toString().toStdString());
		ws.cell(5, row).value(query.value(4).toString().toStdString());
		ws.cell(6, row).value(query.value(5).toInt());
		ws.cell(7, row).value(query.value(6).toDouble());
		ws.cell(8, row).value(query.value(7).toDouble());
		row++;
	}
	QString file_path = QFileDialog::getSaveFileName(this, "保存文件", "../books", "EXCEL文件(*.xlsx)");
	if (!file_path.isEmpty())
	{
		wb.save(file_path.toStdString());
		QMessageBox box(QMessageBox::Information, "提示", "导出成功！");
		box.exec();
	}
	
}
string GetDateTime()
{
	time_t timep;
	time(&timep);
	char tmp[64];
	strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", localtime(&timep));
	return tmp;
}

