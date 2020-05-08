#include "../GUIh/FindWindow.h"
#include "../h/library.h"
#include <qmessagebox.h>
# pragma execution_character_set("utf-8")
FindWindow::FindWindow(QWidget* parent) :QMainWindow(parent)
{
	ui.setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);
	ui.Table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui.Table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
	
}
void FindWindow::closeEvent(QCloseEvent* event)
{
	ui.Table->clearContents();
	emit Close(std::string("find"));
}
void FindWindow::on_ButtonFind_clicked()
{
	if (!ui.CheckBoxName->isChecked()&&!ui.CheckBoxAuthor->isChecked()&& !ui.CheckBoxPublisher->isChecked())
	{
		QMessageBox box(QMessageBox::Information, "提示", "至少选择一个查找项！");
		box.exec();
		return;
	}
	_start_ = clock();
	map <Management::FindWhere, bool >find_where;
	if (ui.CheckBoxName->isChecked())
		find_where[Management::FindWhere::NAME] = true;
	if (ui.CheckBoxAuthor->isChecked())
		find_where[Management::FindWhere::AUTHOR] = true;
	if (ui.CheckBoxPublisher->isChecked())
		find_where[Management::FindWhere::PUBLISHER] = true;
	QByteArray ba = ui.LineEditContent->text().toLocal8Bit();
	_find_content_ = ba.data();
	if (ui.RadioEqual->isChecked())
	{
		Management::FindEqual(_find_results_, _find_content_, find_where);
	}
	else if (ui.RadioInclude->isChecked())
	{
		Management::FindInclude(_find_results_, _find_content_, find_where);
	}
	SetTable();
}
void  FindWindow::SetTable()
{
	ui.Table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
	ui.Table->clearContents();
	ui.Table->setRowCount(_find_results_.size());
	int row = 0;
	for (auto book : _find_results_)
	{
		ui.Table->setItem(row, 0, new QTableWidgetItem(QString::fromLocal8Bit(book->GetName())));//添加表格
		ui.Table->setItem(row, 1, new QTableWidgetItem(QString(book->GetISBN())));
		ui.Table->setItem(row, 2, new QTableWidgetItem(QString::fromLocal8Bit(book->GetAuth())));
		ui.Table->setItem(row, 3, new QTableWidgetItem(QString::fromLocal8Bit(book->GetPub())));
		ui.Table->setItem(row, 4, new QTableWidgetItem(QString::number(book->GetQty(),10)));
		ui.Table->setItem(row, 5, new QTableWidgetItem(QString::number(book->GetRetail(), 10,2)));
		ui.Table->setItem(row, 6, new QTableWidgetItem(QString::number(book->GetWholesale(), 10,2)));
		ui.Table->setItem(row, 7, new QTableWidgetItem(QString(book->GetDateAdded())));
		row++;
	}
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			ui.Table->item(i, j)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		}
	}
	ui.Table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
	clock_t end = clock();		//程序结束用时
	double endtime = (double)(end - _start_) / CLOCKS_PER_SEC;
	ui.statusbar->showMessage(QString("搜索“")+QString::fromLocal8Bit(_find_content_.data())+QString("”共找到")+QString::number(_find_results_.size())+QString("个结果，用时")+QString::number(endtime,10,3)+QString("秒"));
}
void FindWindow::on_LineEditContent_returnPressed()
{
	on_ButtonFind_clicked();
}