#include "../GUIh/ReportWindow.h"
#include "../h/global.h"
#include "../model_h/report.h"
#include <QtWidgets\qmessagebox.h>
# pragma execution_character_set("utf-8")
ReportWindow::ReportWindow(QWidget* parent) :QMainWindow(parent)
{
	setAttribute(Qt::WA_DeleteOnClose);
	ui.setupUi(this);
	report_model = new BookModelNotSort(this);
	sort_model = new ReportModel(this,report_model);
	ui.Table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui.Table->setModel(sort_model);
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

		sort_model->sort(column, Qt::AscendingOrder);
		//ÉýÐòÅÅÁÐ
	}
	else
	{
		sort_model->sort(column, Qt::DescendingOrder);
		//½µÐòÅÅÁÐ
	}
	report_model->select();
	FormatTableHeader();
}
void ReportWindow::FormatTableHeader()
{
	
	if (report_model->rowCount() != 0)
	{
		ui.Table->horizontalHeader()->setSectionResizeMode(1,QHeaderView::ResizeToContents);
	}
	ui.Table->setColumnHidden(0, true);
}
void ReportWindow::on_ButtonSortConfirm_clicked()
{
	
	SetData();
}