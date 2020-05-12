#include "../GUIh/SaleWindow.h"
#include <qevent.h>
#include <qmessagebox.h>
#include "../GUIh/ReportWindow.h"
#include <qsqlrecord.h>
#include <qdebug.h>
#include "../h/global.h"
#include "../GUIh/BookInfoWindow.h"
#include "../h/sqlite.h"
# pragma execution_character_set("utf-8")
SaleWindow::SaleWindow(QWidget* parent)
	: QMainWindow(parent)
{
	this->setAttribute(Qt::WA_DeleteOnClose);
	ui.setupUi(this);
	ui.Fax->setText(QString::number(SaleModel::GetFax(), 10, 2));
	report_window = NULL;
	find_window = NULL;
	sale_model = new SaleModel(this);
	connect(sale_model, SIGNAL(itemChanged(QStandardItem*)), this, SLOT(ItemChange(QStandardItem*)));
	ui.TableCart->setModel(sale_model);
	_add_enable_ = false;
	
}
void SaleWindow::on_Confirm_clicked()
{
	QSqlRecord query_result= BookOpe::Query(ui.ISBN->text().toStdString());
	if (query_result.value(1).isNull())
	{
		QMessageBox box(QMessageBox::Information, "��ʾ", "û���ҵ���ISBN��");
		box.exec();
		return;
	}
	else
	{
		_q_record_ = query_result;
		ui.Name->setText(_q_record_.value("name").toString());
		ui.Retail->setText(QString::number(_q_record_.value("retail").toDouble(),10,2));
		ui.Qty->setText(QString::number(_q_record_.value("qty").toInt()));
		AddEnable(true);
	}
}
void SaleWindow::closeEvent(QCloseEvent* event)
{

	if (sale_model->rowCount()!=0)
	{
		QMessageBox box(QMessageBox::Warning, "����", "���Ĺ��ﳵ�д��������Ʒ���˳��󽫲��ᱣ�棡��ȷ��Ҫ�˳�ô��", QMessageBox::Yes | QMessageBox::No);
		switch (box.exec())
		{
		case QMessageBox::Yes:
			sale_model->clear();
			emit Close(std::string("sale"));
			break;
		default:
			event->ignore();
			return;
		}
	}
	sale_model->clear();
	emit Close(std::string("sale"));
	
}
void SaleWindow::on_ISBN_returnPressed()
{
	on_Confirm_clicked();
}
void SaleWindow::on_ButtonDetail_clicked()
{
		BookInfoWindow* book_info_window = new BookInfoWindow;
		connect(this, SIGNAL(SendBook(QSqlRecord)), book_info_window, SLOT(ReceiveBook(QSqlRecord)));
		emit SendBook(_q_record_);
		book_info_window->exec();
}
void SaleWindow::on_ButtonLibrary_clicked()
{
	if (report_window == NULL)
	{
		report_window = new ReportWindow(this);
		connect(report_window, SIGNAL(Close(std::string)), this, SLOT(SonClose(std::string)));
		report_window->show();
	}
	else
	{
		report_window->showNormal();
		report_window->activateWindow();
	}
}
void SaleWindow::on_ButtonAddToCart_clicked()
{
	int num = my_atoi(ui.Num->text().toLocal8Bit().data());
	if (num <= 0)
	{
		QMessageBox box(QMessageBox::Information, "��ʾ", "����ֻ��Ϊ����0��������");
		box.exec();
		return;
	}
	else if (num > _q_record_.value("qty").toInt())
	{
		QMessageBox box(QMessageBox::Information, "��ʾ", "���Ĺ������Ѿ�������棡");
		box.exec();
		return;
	}
	else
	{
		bool status;
		int row;
		disconnect(sale_model, SIGNAL(itemChanged(QStandardItem*)), this, SLOT(ItemChange(QStandardItem*)));
		sale_model->AddItem(_q_record_, num, status, row);
		if (status)
		{
			FormatTableHeader();
			ui.Num->setText("");
			ui.Sum->setText(QString::number(sale_model->GetSum(), 10, 2));
			ui.SumFaxed->setText(QString::number(sale_model->GetSumFaxed(), 10, 2));
			ui.ISBN->setText("");
		}
		else
		{
			QMessageBox box(QMessageBox::Information, "��ʾ", "���Ѿ�������飬λ�ڹ��ﳵ��" + QString::number(row + 1) + "�У����Ĺ���������������棡");
			box.exec();
		}
		connect(sale_model, SIGNAL(itemChanged(QStandardItem*)), this, SLOT(ItemChange(QStandardItem*)));
	}
}
void SaleWindow::on_Num_returnPressed()
{
	if (_add_enable_)
	{
		on_ButtonAddToCart_clicked();
	}
	else
	{
		QMessageBox box(QMessageBox::Information, "��ʾ", "����ѡ��һ���飡");
		box.exec();
	}
}
void SaleWindow::on_ButtonSattle_clicked()//���㰴ť
{
	if(sale_model->rowCount()!=0)
	{
		if (!sale_model->Sattle())
		{
			QMessageBox box(QMessageBox::Critical, "����", "��Ǹ��������δ֪���󣬽���δ�ܳɹ���");
			box.exec();
			return;
		}
		ui.Sum->setText("");
		ui.SumFaxed->setText("");
		ui.Name->setText("");
		ui.Qty->setText("");
		ui.Retail->setText("");
		AddEnable(false);
		QMessageBox box(QMessageBox::Information, "��ʾ", "�����ѳɹ���");
		box.exec();
	}
	else
	{
		QMessageBox box(QMessageBox::Information, "��ʾ", "��ǰ���ﳵΪ�գ�");
		box.exec();
	}
}
void SaleWindow::AddEnable(bool enable)
{

	ui.ButtonAddToCart->setEnabled(enable);
	ui.ButtonDetail->setEnabled(enable);
	_add_enable_ = enable;
}
void SaleWindow::on_ButtonFind_clicked()
{
	if (find_window == NULL)
	{
		find_window = new FindWindow(this);
		connect(find_window, SIGNAL(Close(std::string)), this, SLOT(SonClose(std::string)));
		find_window->show();
	}
	else
	{
		find_window->showNormal();
		find_window->activateWindow();
	}
}
void SaleWindow::SonClose(std::string name)
{
	if (name == "report")
	{
		report_window = NULL;
	}
	if (name == "find")
	{
		find_window = NULL;
	}
}
void SaleWindow::on_ButtonClear_clicked()
{
	if (sale_model->rowCount()==0)
	{
		QMessageBox box(QMessageBox::Information, "��ʾ", "��ǰ���ﳵΪ�գ�");
		box.exec();
		return;
	}
	QMessageBox box(QMessageBox::Warning, "����", "��ȷ��Ҫ����֧������չ��ﳵô���ò������ɻָ���",QMessageBox::Yes|QMessageBox::No);
	switch (box.exec())
	{
	case QMessageBox::Yes:
		sale_model->clear();
		ui.Sum->setText("");
		ui.SumFaxed->setText("");
		ui.Name->setText("");
		ui.Qty->setText("");
		ui.Retail->setText("");
		AddEnable(false);
	}
}
void SaleWindow::FormatTableHeader()
{
	ui.TableCart->setColumnHidden(0, true);
	if (sale_model->rowCount() != 0)
	{
		ui.TableCart->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
	}
}
void SaleWindow::on_TableCart_customContextMenuRequested(const QPoint &pos)
{
	QModelIndex index = ui.TableCart->indexAt(pos);
	int row = index.row(); // ��ȡ���������
	if (row == -1)
		return;
	_delete_row_ = row;
	QMenu *menu=new QMenu(this);
	QAction *action=new QAction("ɾ��",this);
	connect(action, SIGNAL(triggered()), this, SLOT(Delete()));
	menu->addAction(action);
	menu->exec(QCursor::pos());
}
void SaleWindow::Delete()
{
	sale_model -> Delete(_delete_row_);
	ui.Sum->setText(QString::number(sale_model->GetSum(),10,2));
	ui.SumFaxed->setText(QString::number(sale_model->GetSumFaxed(), 10, 2));
}

void SaleWindow::ItemChange(QStandardItem* item)
{
	
	if (item->column() == 4)
	{
		sale_model->ItemChange(item);
		ui.Sum->setText(QString::number(sale_model->GetSum(), 10, 2));
		ui.SumFaxed->setText(QString::number(sale_model->GetSumFaxed(), 10, 2));
	}
}
