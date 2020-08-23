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
#include <Windows.h>
#include "../h/libxl/libxl.h"
using namespace libxl;
#pragma comment(lib,"libxl.lib")
#include <qtextcodec.h>


MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
{
	sale_window = NULL;
	manage_window = NULL;
	report_window = NULL;
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
		QMessageBox box(QMessageBox::Critical, u8"错误", err);
		box.exec();
		exit(EXIT_FAILURE);
	}

}
void MainWindow::on_ButtonSale_clicked()
{
	if (manage_window != NULL)//为了防止收银的同时进行修改，规定收银和管理窗口智能同时打开一个
	{
		QMessageBox box(QMessageBox::Information, u8"提示", u8"请先关闭管理窗口！");
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
		QMessageBox box(QMessageBox::Information, u8"提示", u8"请先关闭收银窗口！");
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
		QMessageBox box(QMessageBox::Warning, u8"错误", u8"请先关闭已打开的子窗口！");
		box.exec();
		event->ignore();
		return;
	}
	QMessageBox messageBox(QMessageBox::Warning, u8"警告", u8"您确定要退出吗?", QMessageBox::Yes | QMessageBox::No, NULL);//弹窗确认
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
	else if (name == "report")
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

	void ImportFromFile(ifstream &file);
	//定义文件对话框类
	QString file_name = QFileDialog::getOpenFileName(this,
		u8"打开文件",
		".",
		u8"CSV文件(*.csv)");
	if (file_name.isNull())
	{
		return;
	}
	ifstream file(file_name.toStdString().c_str());
	if (!file.is_open())
	{
		QMessageBox box(QMessageBox::Critical, u8"错误", u8"打开文件失败!");
		box.exec();
		return;
	}
	ImportFromFile(file);
	file.close();
	
	
}
string* Divide(char* line)//将line用逗号分割为8个字符串
{
	string *divide=new string [8];
	char temp_str[1000];
	int temp_str_length = 0,divide_num=0;
	for (int i = 0; i <= strlen(line)&& divide_num<=7; i++)
	{
		if (line[i] == ',')//检测逗号
		{
			temp_str[temp_str_length] = '\0';
			divide[divide_num++] = temp_str;
			temp_str_length = 0;
		}
		else
		{
			temp_str[temp_str_length++] = line[i];
		}
	}
	temp_str[temp_str_length] = '\0';
	if (temp_str_length <= 7)//防止数据中逗号多余7个造成崩溃
	{
		divide[divide_num] = temp_str;
	}
	return divide;
}
void ImportFromFile(ifstream &file)
{
	char line[10000];
	file.getline(line,10000);
	file.getline(line,10000);
	int success = 0, fail = 0;
	while (!file.eof())
	{
		file.getline(line, 10000);
		if (file.fail())
			break;
		BookData book;
		try
		{

			string *divide = Divide(line);
			book.SetName(divide[0].c_str());
			book.SetISBN(divide[1].c_str());
			book.SetAuthor(divide[2].c_str());
			book.SetPub(divide[3].c_str());
			book.SetDateAdded(divide[4].c_str());
			book.SetQty(my_atoi(divide[5].c_str()));
			book.SetRetail(my_atof(divide[6].c_str()));
			book.SetWholesale (my_atof(divide[7].c_str()));
			delete [] divide;
		}
		catch (const char* err)//如果输入的数据有问题
		{
			fail++;
			cout << err;
			continue;
		}
		BookOpe::Result result = BookOpe::Insert(book);
		if (result == BookOpe::Result::Success)
		{
			success++;
		}
		else
		{
			fail++;
		}
		
	}
	QMessageBox box(QMessageBox::Information, QString(u8"提示"), u8"共找到" + QString::number(success + fail) + u8"本书,成功" + QString::number(success) + u8"本，失败" + QString::number(fail) + u8"本.");
	box.exec();
}
void MainWindow::on_ActionExportExcel_triggered()
{
	string GetDateTime();
	ofstream file;
	QString file_name = QFileDialog::getSaveFileName(this, u8"导出为CSV", "./books", u8"CSV文件 (*.csv)");
	if (file_name.isNull())
	{
		return;
	}
	QByteArray file_name_bytes = file_name.toLocal8Bit();//防止中文乱码
	file.open(file_name_bytes.data());
	if (!file.is_open())//保存
	{
		QMessageBox box(QMessageBox::Critical, u8"错误", u8"打开文件失败!");
		box.exec();
		return;
	}
	file << "书库管理系统" << GetDateTime() << "导出" << endl;
	file << "书名," << "ISBN," << "作者," << "出版社," << "进货日期," << "库存," << "零售价," << "批发价" << endl;
	QString sql = "SELECT name,isbn,author,publisher,date_added,qty,retail,wholesale from books;";
	QSqlQuery query;
	query.exec(sql);
	while (query.next())
	{
		for (int i = 0; i <= 7; i++)
		{
			file << query.value(i).toString().toLocal8Bit().data();
			if (i != 7)
			{
				file << ",";
			}
		}
		file << endl;
	}
	file.close();

	QMessageBox box(QMessageBox::Information, u8"提示", u8"保存成功!");
	box.exec();
}
string GetDateTime()
{
	time_t timep;
	time(&timep);
	char tmp[64];
	strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", localtime(&timep));
	return tmp;
}

