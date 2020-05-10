#include "../GUIh/SaleWindow.h"
#include <qevent.h>
#include <qmessagebox.h>
#include "../GUIh/ReportWindow.h"
#include <qsqlrecord.h>
#include <qdebug.h>
#include "../h/global.h"
#include "../GUIh/BookInfoWindow.h"
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
	ui.TableCart->setModel(sale_model);
	_add_enable_ = false;
	
}
void SaleWindow::on_Confirm_clicked()
{
	_q_record_=BookOpe::Query(ui.ISBN->text().toStdString());
	if (_q_record_.value(1).isNull())
	{
		QMessageBox box(QMessageBox::Information, "提示", "没有找到该ISBN！");
		box.exec();
		return;
	}
	else
	{
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
		QMessageBox box(QMessageBox::Warning, "警告", "您的购物车有待结算的物品，退出后将不会保存！您确定要退出么？", QMessageBox::Yes | QMessageBox::No);
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
		QMessageBox box(QMessageBox::Information, "提示", "数量只能为大于0的整数！");
		box.exec();
		return;
	}
	if (num > _q_record_.value("qty").toInt())
	{
		QMessageBox box(QMessageBox::Information, "提示", "您的购买量已经超过库存！");
		box.exec();
		return;
	}
	else
	{
		bool status;
		int row;
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
			QMessageBox box(QMessageBox::Information, "提示", "您已经购买此书，位于购物车第"+QString::number(row)+"行，您的购买总量将超过库存！");
			box.exec();
			return;
		}
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
		QMessageBox box(QMessageBox::Information, "提示", "请先选择一本书！");
		box.exec();
	}
}
void SaleWindow::on_ButtonSattle_clicked()//结算按钮
{
	if(sale_model->rowCount()!=0)
	{
		if (!sale_model->Sattle())
		{
			QMessageBox box(QMessageBox::Critical, "错误", "抱歉，程序发生未知错误！");
			box.exec();
			return;
		}
		ui.Sum->setText("");
		ui.SumFaxed->setText("");
		ui.Name->setText("");
		ui.Qty->setText("");
		ui.Retail->setText("");
		AddEnable(false);
		QMessageBox box(QMessageBox::Information, "提示", "交易已成功！");
		box.exec();
	}
	else
	{
		QMessageBox box(QMessageBox::Information, "提示", "当前购物车为空！");
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
//void SaleWindow::on_TableCart_cellChanged(int row,int column)//双击修改数量
//{
//	QByteArray ba=ui.TableCart->item(row, column)->text().toLatin1();
//	int num = my_atoi(ba.data());
//	if (num <= 0)
//	{
//		QMessageBox box(QMessageBox::Information, "提示", "数量必须为大于0的整数！");
//		box.exec();
//		ui.TableCart->disconnect(SIGNAL(cellChanged(int, int)));
//		ui.TableCart->setItem(row, 2, new QTableWidgetItem(QString::number(_sale_.GetNum(row))));//还原用户更改
//		ui.TableCart->item(row, 2)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
//		connect(ui.TableCart, SIGNAL(cellChanged(int, int)), this, SLOT(on_TableCart_cellChanged(int, int)));
//		return;
//	}
//	if (_sale_.ChangeItem(row, num))
//	{
//	
//		ui.TableCart->disconnect(SIGNAL(cellChanged(int, int)));
//		ui.TableCart->setItem(row, 3, new QTableWidgetItem(QString::number(_sale_.GetRetail(row)*num,10,2)));//修正总价
//		ui.TableCart->item(row, 3)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
//		connect(ui.TableCart, SIGNAL(cellChanged(int, int)), this, SLOT(on_TableCart_cellChanged(int, int)));
//		ui.Sum->setText(QString::number(_sale_.GetSum()));
//		ui.SumFaxed->setText(QString::number(_sale_.GetSumFaxed()));
//		return;
//	}
//	else
//	{
//		QMessageBox box(QMessageBox::Information, "提示",QString("您的购买量已经超过库存")+QString::number(_sale_.GetQty(row))+QString("!"));
//		box.exec();
//		ui.TableCart->disconnect(SIGNAL(cellChanged(int, int)));
//		ui.TableCart->setItem(row, 2, new QTableWidgetItem(QString::number(_sale_.GetNum(row))));//还原用户更改
//		ui.TableCart->item(row, 2)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
//		connect(ui.TableCart, SIGNAL(cellChanged(int, int)), this, SLOT(on_TableCart_cellChanged(int, int)));
//		return;
//	}
//}
void SaleWindow::on_ButtonClear_clicked()
{
	if (sale_model->rowCount()==0)
	{
		QMessageBox box(QMessageBox::Information, "提示", "当前购物车为空！");
		box.exec();
		return;
	}
	QMessageBox box(QMessageBox::Warning, "警告", "您确定要放弃支付并清空购物车么？该操作不可恢复！",QMessageBox::Yes|QMessageBox::No);
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
//void SaleWindow::on_TableCart_customContextMenuRequested(const QPoint &pos)
//{
//	QModelIndex index = ui.TableCart->indexAt(pos);
//	int row = index.row(); // 获取鼠标所在行
//	_delete_row_ = row;
//	if (row == -1)
//		return;
//	QMenu *menu=new QMenu(this);
//	QAction *action=new QAction("删除",this);
//	connect(action, SIGNAL(triggered()), this, SLOT(Delete()));
//	menu->addAction(action);
//	menu->exec(QCursor::pos());
//	
//	
//}
//void SaleWindow::Delete()
//{
//	_sale_.DeleteItem(_delete_row_);
//	ui.TableCart->removeRow(_delete_row_);
//	ui.Sum->setText(QString::number(_sale_.GetSum()));
//	ui.SumFaxed->setText(QString::number(_sale_.GetSumFaxed()));
//}