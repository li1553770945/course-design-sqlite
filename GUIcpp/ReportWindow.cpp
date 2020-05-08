#include "../GUIh/ReportWindow.h"
#include "../h/global.h"
#include <QtWidgets\qmessagebox.h>
# pragma execution_character_set("utf-8")
ReportWindow::ReportWindow(QWidget* parent) :QMainWindow(parent)
{
	//ui.Table->setSortingEnabled(false);
	ui.setupUi(this);
	Initialize();
	setAttribute(Qt::WA_DeleteOnClose);
}
void ReportWindow::closeEvent(QCloseEvent* event)
{
	ui.Table->clearContents();
	emit Close(std::string("report"));
}
void ReportWindow::on_CheckBoxName_clicked()
{
	if(ui.CheckBoxName->isChecked())
		ui.Table->setColumnHidden(0, false);
	else
		ui.Table->setColumnHidden(0, true);
}
void ReportWindow::on_CheckBoxISBN_clicked()
{
	if (ui.CheckBoxISBN->isChecked())
		ui.Table->setColumnHidden(1, false);
	else
		ui.Table->setColumnHidden(1, true);
}
void ReportWindow::on_CheckBoxAuthor_clicked()
{
	if (ui.CheckBoxAuthor->isChecked())
		ui.Table->setColumnHidden(2, false);
	else
		ui.Table->setColumnHidden(2, true);
}
void ReportWindow::on_CheckBoxPublisher_clicked()
{
	if (ui.CheckBoxPublisher->isChecked())
		ui.Table->setColumnHidden(3, false);
	else
		ui.Table->setColumnHidden(3, true);
}
void ReportWindow::on_CheckBoxDateAdded_clicked()
{
	if (ui.CheckBoxDateAdded->isChecked())
		ui.Table->setColumnHidden(4, false);
	else
		ui.Table->setColumnHidden(4, true);
}
void ReportWindow::on_CheckBoxQty_clicked()
{
	if (ui.CheckBoxQty->isChecked())
		ui.Table->setColumnHidden(5, false);
	else
		ui.Table->setColumnHidden(5, true);
}

void ReportWindow::on_CheckBoxRetail_clicked()
{
	if (ui.CheckBoxRetail->isChecked())
		ui.Table->setColumnHidden(6, false);
	else
		ui.Table->setColumnHidden(6, true);
}
void ReportWindow::on_CheckBoxWholesale_clicked()
{
	if (ui.CheckBoxWholesale->isChecked())
		ui.Table->setColumnHidden(7, false);
	else
		ui.Table->setColumnHidden(7, true);
}
void ReportWindow::on_ButtonFlush_clicked()
{
	Initialize();
}
void ReportWindow::SetData()
{
	clock_t start=clock();
	ui.Table->clearContents();
	ui.Table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
	ui.Table->setRowCount(_item_one_page_);
	int row_count = 0;
	while(row_count< _item_one_page_)
	{
		if (((_page_ - 1) * _item_one_page_ + row_count) >= Report::_book_vec.size())
		{
			break;
		}
		shared_ptr<BookData>  book = Report::_book_vec[(_page_ - 1) * _item_one_page_ + row_count];
		ui.Table->setItem(row_count, 0,new QTableWidgetItem(QString::fromLocal8Bit(book->GetName())));
		ui.Table->setItem(row_count, 1, new QTableWidgetItem(book->GetISBN()));
		ui.Table->setItem(row_count, 2, new QTableWidgetItem(QString::fromLocal8Bit(book->GetAuth())));
		ui.Table->setItem(row_count, 3, new QTableWidgetItem(QString::fromLocal8Bit(book->GetPub())));
		ui.Table->setItem(row_count, 4, new QTableWidgetItem(book->GetDateAdded()));
		ui.Table->setItem(row_count, 5, new QTableWidgetItem(QString::number(book->GetQty())));
		ui.Table->setItem(row_count, 6, new QTableWidgetItem(QString::number(book->GetRetail(),10,2)));
		ui.Table->setItem(row_count, 7, new QTableWidgetItem(QString::number(book->GetWholesale(), 10, 2)));
		for (int j = 0; j < 8; j++)
		{
			ui.Table->item(row_count, j)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		}
		row_count++;
	}
	ui.Table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui.Table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
	clock_t end = clock();		
	double endtime = (double)(end - start) / CLOCKS_PER_SEC;
	ui.statusbar->showMessage(QString("书库中共有") + QString::number(books.size()) + QString("本书，本页加载耗时")+QString::number(endtime,10,3)+QString("秒"));
}
void ReportWindow::Initialize()
{
	_max_page_ = (books.size() + _item_one_page_ - 1) / _item_one_page_;
	ui.LabelSumPage->setText(QString::number(_max_page_));
	ui.LineEditPage->setText(QString::number(1));
	_page_ = 1;
	Report::SetBookVec();
	on_ButtonSortConfirm_clicked();
	SetData();
}
void ReportWindow::on_ButtonPreviousPage_clicked()
{
	if (_page_ == 1)
	{
		QMessageBox box(QMessageBox::Information, "提示", "已经是第一页！");
		box.exec();
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
		QMessageBox box(QMessageBox::Information, "提示", "已经是最后一页！");
		box.exec();
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
	int page = my_atoi(ui.LineEditPage->text().toLocal8Bit().data());
	if (page < 1||page>_max_page_)
	{
		char information[50];
		sprintf(information, "页数必须是1~%d之间的整数！",_max_page_);
		QMessageBox box(QMessageBox::Information, "提示", information);
		ui.LineEditPage->setText(QString::number(_page_));
		box.exec();
	}
	else
	{
		_page_ = page;
		SetData();
	}
}
void ReportWindow::on_ButtonSortConfirm_clicked()
{
	string key;
	if (ui.RadioName->isChecked())
	{
		key = "name";
	}
	if (ui.RadioQty->isChecked())
	{
		key = "qty";
	}
	if (ui.RadioDateAdded->isChecked())
	{
		key = "date_added";
	}
	if (ui.RadioRetail->isChecked())
	{
		key = "retail";
	}
	if (ui.RadioWholesale->isChecked())
	{
		key = "wholesale";
	}
	if (ui.RadioBackward->isChecked())
	{
		key = string("-") + key;
	}
	Report::Sort(key);
	_page_ = 1;
	ui.LineEditPage->setText(QString::number(1));
	SetData();
}