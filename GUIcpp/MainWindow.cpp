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
		Sqlite::LoadDataBase();//���Լ������ݿ�
		LoadConfig();//���Լ��������ļ���˰�ʵȵȣ�
	}
	catch (QString err)
	{
		QMessageBox box(QMessageBox::Critical, "����", err);
		box.exec();
		exit(EXIT_FAILURE);
	}
	
}
void MainWindow::on_ButtonSale_clicked()
{
	if (manage_window != NULL)//Ϊ�˷�ֹ������ͬʱ�����޸ģ��涨�����͹���������ͬʱ��һ��
	{
		QMessageBox box(QMessageBox::Information, "��ʾ", "���ȹرչ����ڣ�");
		box.exec();
		return;
	}
	if (sale_window == NULL)//���Ϊ�գ�˵����û�д򿪹�������ڣ���ô���½�һ������ʾ
	{
		
		sale_window = new SaleWindow(this);
		connect(sale_window, SIGNAL(Close(std::string)), this, SLOT(CloseSon(std::string)));
		sale_window->show();
		
	}
	else//����Ѿ����ˣ��������´�����������ʾԭ����
	{
		sale_window->showNormal();
		sale_window->activateWindow();
	}
}
void MainWindow::on_ButtonManage_clicked()//������ģ��ͬ��
{
	if (sale_window != NULL)
	{
		QMessageBox box(QMessageBox::Information, "��ʾ", "���ȹر��������ڣ�");
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
void MainWindow::on_ButtonExit_clicked()//����رհ�ť
{
	this->close();
}
void MainWindow::closeEvent(QCloseEvent* event)
{
	if (manage_window != NULL || sale_window != NULL || report_window != NULL)//�Ӵ��ڻ���û�رյģ���ֹ�����ڹر�
	{
		QMessageBox box(QMessageBox::Warning, "����", "���ȹر��Ѵ򿪵��Ӵ��ڣ�");
		box.exec();
		event->ignore();
		return;
	}
	QMessageBox messageBox(QMessageBox::Warning, "����", "��ȷ��Ҫ�˳���?", QMessageBox::Yes | QMessageBox::No, NULL);//����ȷ��
	switch (messageBox.exec())
	{
	case QMessageBox::Yes:
	
		Sqlite::Close();//�ر����ݿ�����
		exit(EXIT_SUCCESS);
		break;
	default:
		event->ignore();
	}
	
}
void MainWindow::CloseSon(std::string name)//�Ӵ��ڹرգ�Ҫ�������ڵ�ָ����λNULL
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
void MainWindow::on_ActionAbout_triggered()//���ڴ���
{
	AboutWindow* about_window = new AboutWindow(this);
	about_window->exec();
}

void MainWindow::on_ActionImportExcel_triggered()
{
	
	//�����ļ��Ի�����
	QFileDialog* file_dialog = new QFileDialog(this);
	file_dialog->setWindowTitle(QStringLiteral("ѡ���ļ�"));
	file_dialog->setDirectory(".");
	//�����ļ�������
	file_dialog->setNameFilter("Excel�ļ�(*.xlsx)");
	//������ͼģʽ
	file_dialog->setViewMode(QFileDialog::Detail);
	//��ӡ����ѡ����ļ���·��
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
				book.SetName(ws.cell(1,row).to_string().c_str());//��������
				book.SetISBN(ws.cell(2, row).to_string().c_str());
				book.SetAuthor(ws.cell(3, row).to_string().c_str());
				book.SetPub(ws.cell(4, row).to_string().c_str());//���ó�����
				book.SetDateAdded(ws.cell(5, row).to_string().c_str());//���ý�������
				book.SetQty(my_atoi(ws.cell(6, row).to_string().c_str()));//���ÿ��
				book.SetRetail(my_atof(ws.cell(7, row).to_string().c_str()));//�������ۼ�
				book.SetWholesale(my_atof(ws.cell(8, row).to_string().c_str()));//����������
				
			}
			catch (const char* err)//������������������
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
	string message = "���ҵ�" + to_string(row - 3) + "������,�ɹ�" + to_string(success) + "��,ʧ��" + to_string(fail) + "��";
	QMessageBox box(QMessageBox::Information, "��ʾ", QString::fromStdString(message));
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
	ws.cell(1, 1).value(string("������ϵͳ���� ") + GetDateTime());
	ws.cell(1,2).value("����");
	ws.cell(2,2).value("ISBN");
	ws.cell(3,2).value("����");
	ws.cell(4,2).value("������");
	ws.cell(5,2).value("��������");
	ws.cell(6,2).value("���");
	ws.cell(7,2).value("���ۼ�");
	ws.cell(8,2).value("������");
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
	QString file_path = QFileDialog::getSaveFileName(this, "�����ļ�", "../books", "EXCEL�ļ�(*.xlsx)");
	if (!file_path.isEmpty())
	{
		wb.save(file_path.toStdString());
		QMessageBox box(QMessageBox::Information, "��ʾ", "�����ɹ���");
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

