#include "../GUIh/FindWindow.h"
#include "../h/library.h"
#include <qmessagebox.h>
#include <vector>
# pragma execution_character_set("utf-8")
FindWindow::FindWindow(QWidget* parent) :QMainWindow(parent)
{
	ui.setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);
	ui.Table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	find_model = new FindModel(this);
	ui.Table->setModel(find_model);
	//ui.Table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
	
}
void FindWindow::closeEvent(QCloseEvent* event)
{
	emit Close(string("find"));
}
void FindWindow::on_ButtonFind_clicked()
{
	if (!ui.CheckBoxName->isChecked()&&!ui.CheckBoxAuthor->isChecked()&& !ui.CheckBoxPublisher->isChecked())
	{
		QMessageBox box(QMessageBox::Information, "提示", "至少选择一个查找项！");
		box.exec();
		return;
	}
	std::vector <QString> fields;
	QString key = ui.LineEditContent->text();
	QString find_method;
	if (ui.RadioEqual->isChecked())
		find_method = "accurate";
	else
		find_method = "fuzzy";
	if (ui.CheckBoxName->isChecked())
		fields.push_back("name");
	if (ui.CheckBoxAuthor->isChecked())
		fields.push_back("author");
	if (ui.CheckBoxPublisher->isChecked())
		fields.push_back("publisher");
	clock_t start = clock();
	find_model->Query(key,fields,find_method);
	FormatTableHeader();
	find_model->sort(1);
	clock_t end = clock();
	double use_time = (end - start) / CLOCKS_PER_SEC;
	ui.statusbar->showMessage(QString("查找“")+key+QString("”共找到")+QString::number(find_model->rowCount())+ QString("个结果，用时") + QString::number(use_time, 10, 3) + QString("秒"));
}
void FindWindow::on_LineEditContent_returnPressed()
{
	on_ButtonFind_clicked();
}
void FindWindow::FormatTableHeader()
{
	ui.Table->setColumnHidden(0, true);
	ui.Table->setColumnHidden(9, true);
	if (find_model->rowCount() != 0)
	{
		ui.Table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
	}
}