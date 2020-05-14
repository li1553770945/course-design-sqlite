#include "../GUIh/FindWindow.h"
#include "../h/library.h"
#include <qmessagebox.h>
#include <qdebug.h>
# pragma execution_character_set("utf-8")
FindWindow::FindWindow(QWidget* parent) :QMainWindow(parent)
{
	ui.setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);
	ui.Table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	find_model = new FindModel(this);
	ui.Table->setModel(find_model);
	
}
void FindWindow::closeEvent(QCloseEvent* event)
{
	emit Close(string("find"));
}
void FindWindow::on_ButtonFind_clicked()
{
	QString value = ui.LineEditContent->text();
	if (!ui.CheckBoxName->isChecked()&&!ui.CheckBoxAuthor->isChecked()&& !ui.CheckBoxPublisher->isChecked())
	{
		QMessageBox box(QMessageBox::Information, "提示", "至少选择一个查找项！");
		box.exec();
		return;
	}
	QString order = " ORDER BY";
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
	QString sql = "SELECT name,isbn,author,publisher,date_added,qty,retail,wholesale FROM books WHERE";
	if (ui.RadioEqual->isChecked())
	{
		bool first_key = true;
		if (ui.CheckBoxName->isChecked())
		{
			if (first_key)
				first_key = false;
			else
				sql += " OR";
			sql = sql + " name='" + value+"'";
		}
		if (ui.CheckBoxAuthor->isChecked())
		{
			if (first_key)
				first_key = false;
			else
				sql += " OR";
			sql = sql + " author='" + value + "'";
		}
		if (ui.CheckBoxPublisher->isChecked())
		{
			if (first_key)
				first_key = false;
			else
				sql += " OR";
			sql = sql + " publisher='" + value + "'";
		}
	}
	else 
	{
		bool first_key = true;
		if (ui.CheckBoxName->isChecked())
		{
			if (first_key)
				first_key = false;
			else
				sql += " OR";
			sql = sql + " name LIKE '%" + value + "%'";
		}
		if (ui.CheckBoxAuthor->isChecked())
		{
			if (first_key)
				first_key = false;
			else
				sql += " OR";
			sql = sql + " author LIKE '%" + value + "%'";
		}
		if (ui.CheckBoxPublisher->isChecked())
		{
			if (first_key)
				first_key = false;
			else
				sql += " OR";
			sql = sql + " publisher LIKE '%" + value + "%'";
		}
	}
	sql += order;
	clock_t start = clock();
	find_model->setQuery(sql);
	FormatTableHeader();
	clock_t end = clock();
	double use_time = (end - start) / CLOCKS_PER_SEC;
	ui.statusbar->showMessage(QString("查找“")+value+QString("”共找到")+QString::number(find_model->rowCount())+ QString("个结果，用时") + QString::number(use_time, 10, 3) + QString("秒"));
}
void FindWindow::on_LineEditContent_returnPressed()
{
	on_ButtonFind_clicked();
}
void FindWindow::FormatTableHeader()
{
	find_model->SetHeader();
	if (find_model->rowCount() != 0)
	{
		ui.Table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
	}
}