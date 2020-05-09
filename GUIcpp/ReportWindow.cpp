#include "../GUIh/ReportWindow.h"
#include "../h/global.h"
#include "../model_h/books.h"
#include <QtWidgets\qmessagebox.h>
# pragma execution_character_set("utf-8")
ReportWindow::ReportWindow(QWidget* parent) :QMainWindow(parent)
{
	setAttribute(Qt::WA_DeleteOnClose);
	ui.setupUi(this);
	ui.Table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	books = new BookModel(this);
	ui.Table->setModel(books);
	SetData();
}
void ReportWindow::closeEvent(QCloseEvent* event)
{
	emit Close(std::string("report"));
}
void ReportWindow::on_CheckBoxName_clicked()
{
	if(ui.CheckBoxName->isChecked())
		ui.Table->setColumnHidden(1, false);
	else
		ui.Table->setColumnHidden(1, true);
}
void ReportWindow::on_CheckBoxISBN_clicked()
{
	if (ui.CheckBoxISBN->isChecked())
		ui.Table->setColumnHidden(2, false);
	else
		ui.Table->setColumnHidden(2, true);
}
void ReportWindow::on_CheckBoxAuthor_clicked()
{
	if (ui.CheckBoxAuthor->isChecked())
		ui.Table->setColumnHidden(3, false);
	else
		ui.Table->setColumnHidden(3, true);
}
void ReportWindow::on_CheckBoxPublisher_clicked()
{
	if (ui.CheckBoxPublisher->isChecked())
		ui.Table->setColumnHidden(4, false);
	else
		ui.Table->setColumnHidden(4, true);
}
void ReportWindow::on_CheckBoxDateAdded_clicked()
{
	if (ui.CheckBoxDateAdded->isChecked())
		ui.Table->setColumnHidden(5, false);
	else
		ui.Table->setColumnHidden(5, true);
}
void ReportWindow::on_CheckBoxQty_clicked()
{
	if (ui.CheckBoxQty->isChecked())
		ui.Table->setColumnHidden(6, false);
	else
		ui.Table->setColumnHidden(6, true);
}

void ReportWindow::on_CheckBoxRetail_clicked()
{
	if (ui.CheckBoxRetail->isChecked())
		ui.Table->setColumnHidden(7, false);
	else
		ui.Table->setColumnHidden(7, true);
}
void ReportWindow::on_CheckBoxWholesale_clicked()
{
	if (ui.CheckBoxWholesale->isChecked())
		ui.Table->setColumnHidden(8, false);
	else
		ui.Table->setColumnHidden(8, true);
}
void ReportWindow::on_ButtonFlush_clicked()
{
	SetData();
}
void ReportWindow::SetData()
{
	
	books->select();
	ui.Table->setColumnHidden(0, true);
}
//void ReportWindow::Initialize()
//{
//	_max_page_ = (books.size() + _item_one_page_ - 1) / _item_one_page_;
//	ui.LabelSumPage->setText(QString::number(_max_page_));
//	ui.LineEditPage->setText(QString::number(1));
//	_page_ = 1;
//	Report::SetBookVec();
//	on_ButtonSortConfirm_clicked();
//	SetData();
//}
//void ReportWindow::on_ButtonPreviousPage_clicked()
//{
//	if (_page_ == 1)
//	{
//		QMessageBox box(QMessageBox::Information, "提示", "已经是第一页！");
//		box.exec();
//	}
//	else
//	{
//		_page_--;
//		SetData();
//		ui.LineEditPage->setText(QString::number(_page_));
//	}
//}
//void ReportWindow::on_ButtonNextPage_clicked()
//{
//	if (_page_ == _max_page_)
//	{
//		QMessageBox box(QMessageBox::Information, "提示", "已经是最后一页！");
//		box.exec();
//	}
//	else
//	{
//		_page_++;
//		SetData();
//		ui.LineEditPage->setText(QString::number(_page_));
//	}
//
//}
//void ReportWindow::on_LineEditPage_returnPressed()
//{
//	int page = my_atoi(ui.LineEditPage->text().toLocal8Bit().data());
//	if (page < 1||page>_max_page_)
//	{
//		char information[50];
//		sprintf(information, "页数必须是1~%d之间的整数！",_max_page_);
//		QMessageBox box(QMessageBox::Information, "提示", information);
//		ui.LineEditPage->setText(QString::number(_page_));
//		box.exec();
//	}
//	else
//	{
//		_page_ = page;
//		SetData();
//	}
//}
void ReportWindow::on_ButtonSortConfirm_clicked()
{
	int column = 1;
	if (ui.RadioName->isChecked())
		column = 1;
	if (ui.RadioDateAdded->isChecked())
		column = 5;
	if (ui.RadioQty->isChecked())
		column = 6;
	if (ui.RadioRetail->isChecked())
		column = 7;
	if (ui.RadioWholesale->isChecked())
		column = 8;
	if (ui.RadioPositive->isChecked())
	{
		books->setSort(column, Qt::AscendingOrder); //id属性，即第0列，升序排列
	}
	else
	{
		books->setSort(column, Qt::DescendingOrder); //id属性，即第0列，降序排
	}
	SetData();
}