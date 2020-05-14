#include "../GUIh/ReportWindow.h"
#include "../h/global.h"
#include "../model_h/report.h"
#include <QtWidgets\qmessagebox.h>
#include "qdebug.h"
# pragma execution_character_set("utf-8")
ReportWindow::ReportWindow(QWidget* parent) :QMainWindow(parent)
{
	setAttribute(Qt::WA_DeleteOnClose);
	ui.setupUi(this);
	report_model = new ReportModel(this);
	ui.Table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui.Table->setModel(report_model);
	SetData();
	ui.LineEditPage->setText("1");
	_max_page_ = (report_model->rowCount() + _items_one_page_ - 1) / _items_one_page_;
	ui.LabelSumPage->setText(QString::number(_max_page_));
	
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
	int column=0;
	if (ui.RadioName->isChecked())
		column = 9;
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
		report_model->sort(column, Qt::AscendingOrder);
		//升序排列
	}
	else
	{
		report_model->sort(column, Qt::DescendingOrder);
		//降序排列
	}
	report_model->select();
	_max_page_ = (report_model->rowCount()+ _items_one_page_ -1)/_items_one_page_;//计算最大页数
	FormatTableHeader();
}
void ReportWindow::FormatTableHeader()
{
	
	if (report_model->rowCount() != 0)
	{
		ui.Table->horizontalHeader()->setSectionResizeMode(1,QHeaderView::ResizeToContents);
	}
	ui.Table->setColumnHidden(0, true);
	ui.Table->setColumnHidden(9, true);
}
void ReportWindow::on_ButtonSortConfirm_clicked()
{
	
	SetData();
}
void ReportWindow::on_ButtonPreviousPage_clicked()
{
	if (_page_ == 1)
	{
		QMessageBox box(QMessageBox::Information, "提示", "当前已经是第一页！");
		box.exec();
		return;
	}
	else
	{
		_page_--;
		ui.LineEditPage->setText(QString::number(_page_));
	}
}
void ReportWindow::on_ButtonNextPage_clicked()
{
	if (_page_ == _max_page_)
	{
		QMessageBox box(QMessageBox::Information, "提示", "当前已经是最后一页！");
		box.exec();
		return;
	}
	else
	{
		_page_++;
		ui.LineEditPage->setText(QString::number(_page_));
	}
}
void ReportWindow::on_LineEditPage_returnPressed()
{

}