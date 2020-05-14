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
	_page_ = 1;
	ui.LineEditPage->setText("1");
	ui.LabelSumPage->setText(QString::number(_max_page_));
	
}
void ReportWindow::closeEvent(QCloseEvent* event)
{
	emit Close(std::string("report"));
}
void ReportWindow::on_CheckBoxName_clicked()
{
	ui.Table->setColumnHidden(0, !ui.CheckBoxName->isChecked());
}
void ReportWindow::on_CheckBoxISBN_clicked()
{
	ui.Table->setColumnHidden(1, !ui.CheckBoxISBN->isChecked());
}
void ReportWindow::on_CheckBoxAuthor_clicked()
{
	ui.Table->setColumnHidden(2, !ui.CheckBoxAuthor->isChecked());
}
void ReportWindow::on_CheckBoxPublisher_clicked()
{
	ui.Table->setColumnHidden(3, !ui.CheckBoxPublisher->isChecked());
}
void ReportWindow::on_CheckBoxDateAdded_clicked()
{
	ui.Table->setColumnHidden(4, !ui.CheckBoxDateAdded->isChecked());
}
void ReportWindow::on_CheckBoxQty_clicked()
{
	ui.Table->setColumnHidden(5, !ui.CheckBoxQty->isChecked());
}
void ReportWindow::on_CheckBoxRetail_clicked()
{
	ui.Table->setColumnHidden(6, !ui.CheckBoxRetail->isChecked());
}
void ReportWindow::on_CheckBoxWholesale_clicked()
{
	ui.Table->setColumnHidden(7, !ui.CheckBoxWholesale->isChecked());
}
void ReportWindow::on_ButtonFlush_clicked()
{
	SetData();
}
void ReportWindow::SetData()
{
	QString order=" ORDER BY";
	if (ui.RadioName->isChecked())
		order += " name_pinyin";
	if (ui.RadioDateAdded->isChecked())
		order += " date_added";
	if (ui.RadioQty->isChecked())
		order += " qty";
	if (ui.RadioRetail->isChecked())
		order += " retaill";
	if (ui.RadioWholesale->isChecked())
		order += " wholesale";
	if (ui.RadioPositive->isChecked())
	{
		order += " ASC";
		//升序排列
	}
	else
	{
		order += " DESC";
		//降序排列
	}
	QString limit = "  LIMIT " + QString::number(_items_one_page_) + " OFFSET " + QString::number((_page_ - 1) * _items_one_page_);
	QString sql = "select name,isbn,author,publisher,qty,date_added,retail,wholesale from books" + order + limit;
	report_model->setQuery(sql);
	report_model->SetHeader();

	QSqlQuery query_max_row;
	query_max_row.exec("select count(id) from books");
	query_max_row.next();
	int max_row = query_max_row.value(0).toInt();
	_max_page_=(max_row+_items_one_page_-1)/ _items_one_page_;
	ui.statusbar->showMessage("书库中共有"+QString::number(max_row)+"本书，每页显示"+QString::number(_items_one_page_)+"本书");
	FormatTableHeader();
}
void ReportWindow::FormatTableHeader()
{
	
	if (report_model->rowCount() != 0)
	{
		ui.Table->horizontalHeader()->setSectionResizeMode(0,QHeaderView::ResizeToContents);
	}
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
		SetData();
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
		SetData();
		ui.LineEditPage->setText(QString::number(_page_));
	}
}
void ReportWindow::on_LineEditPage_returnPressed()
{
	int page = ui.LineEditPage->text().toInt();
	if (page<=0||page>_max_page_)
	{
		QMessageBox box(QMessageBox::Information, "提示", "数量必须是1~"+QString::number(_max_page_)+"之间的整数");
		box.exec();
		return;
	}
	else
	{
		_page_ = page;
		SetData();
	}
}