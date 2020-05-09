#include "../GUIh/ManageWindow.h"
#include "../h/library.h"
#include <qmessagebox.h>
#include "../h/global.h"
#include "../model_h/books.h"
#include "../model_h/sqlite.h"
#include <qsqlrecord.h>
#include <qdebug.h>
# pragma execution_character_set("utf-8")
ManageWindow::ManageWindow(QWidget* parent) :QMainWindow(parent)
{
	ui.setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);
	ui.LineEditFax->setText(QString::number(SaleModel::GetFax(), 10, 2));
}
void ManageWindow::closeEvent(QCloseEvent* event)
{
	emit Close(std::string("manage"));
}
void ManageWindow::on_ButtonAdd_clicked()
{
	BookData book;
	try
	{
		QByteArray ba = ui.NameAdd->text().toLocal8Bit();
		book.SetName(ba.data());//设置书名
		book.SetISBN(ui.ISBNAdd->text().toLatin1().data());
		ba = ui.AuthorAdd->text().toLocal8Bit();//设置作者
		book.SetAuthor(ba.data());
		ba = ui.PublisherAdd->text().toLocal8Bit();//设置出版社
		book.SetPub(ba.data());//设置出版社
		book.SetQty(my_atoi(ui.QtyAdd->text().toLatin1().data()));//设置库存
		book.SetRetail(my_atof(ui.RetailAdd->text().toLatin1().data()));//设置零售价
		book.SetWholesale(my_atof(ui.WholesaleAdd->text().toLatin1().data()));//设置批发价
		ba = ui.DateAddedAdd->date().toString("yyyy-MM-dd").toLatin1(); // must
		book.SetDateAdded(ba.data());//设置进货日期
	}
	catch (const char* err)
	{
		QMessageBox box(QMessageBox::Warning, "提示", QString::fromLocal8Bit(err));
		box.exec();
		return;
	}
	BookOpe::Result result = BookOpe::Insert(book);
	if (result == BookOpe::Result::Success)
	{
		QMessageBox box(QMessageBox::Information, "提示", "添加成功！");
		box.exec();
	}
	else if (result == BookOpe::Result::Exist)
	{
		QMessageBox box(QMessageBox::Information, "提示", "添加失败！该ISBN已经存在");
		box.exec();
	}
	else if (result == BookOpe::Result::Fail)
	{
		QMessageBox box(QMessageBox::Critical, "提示", "添加失败！未知错误！");
		box.exec();
	}
}
void ManageWindow::on_ButtonISBNConfirm_clicked()
{
	int row = BookOpe::QueryRow(ui.ISBNInput->text().toStdString());
	if (row == -1)
	{
		QMessageBox message_box(QMessageBox::Information, "提示", "ISBN输入错误，请重新输入!", QMessageBox::Yes);
		message_box.exec();
	}
	else
	{
		QSqlRecord record = BookOpe::Query(ui.ISBNInput->text().toStdString());
		_q_result = record;
		ui.ButtonSave->setEnabled(true);
		ui.ButtonDelete->setEnabled(true);
		ui.NameEdit->setText(record.value("name").toString());
		ui.ISBNEdit->setText(record.value("isbn").toString());
		ui.PublisherEdit->setText(record.value("publisher").toString());
		ui.AuthorEdit->setText(record.value("author").toString());
		ui.QtyEdit->setText(record.value("qty").toString());
		ui.RetailEdit->setText(QString::number(record.value("retail").toDouble(), 10, 2));
		ui.WholesaleEdit->setText(QString::number(record.value("retail").toDouble(), 10, 2));
		ui.DateAddedEdit->setDate(QDate::fromString(record.value("publisher").toString(), "yyyy-MM-dd"));
	}
}
void ManageWindow::on_ButtonDelete_clicked()
{
	QMessageBox box(QMessageBox::Warning, "警告", "您确定要删除么？此操作不可恢复！", QMessageBox::Yes | QMessageBox::No);
	switch (box.exec())
	{
	case QMessageBox::Yes:
	{
		if (BookOpe::Delete(ui.ISBNEdit->text().toStdString()) == BookOpe::Result::Success)
		{
			ui.ButtonSave->setEnabled(false);
			ui.ButtonDelete->setEnabled(false);
			QMessageBox success(QMessageBox::Information, "提示", "删除成功！");
			success.exec();
		}
		else
		{
			QMessageBox success(QMessageBox::Critical, "提示", "删除失败！未知错误！");
			success.exec();
		}
	}
	break;
	default:
		return;
	}

}
void ManageWindow::on_ISBNInput_returnPressed()
{
	on_ButtonISBNConfirm_clicked();
}
void ManageWindow::on_ButtonSave_clicked()
{
	BookData book;
	try
	{
		QByteArray ba = ui.NameEdit->text().toLocal8Bit();
		book.SetName(ba.data());//设置书名
		book.SetISBN(ui.ISBNEdit->text().toLatin1().data());

		ba = ui.AuthorEdit->text().toLocal8Bit();//设置作者
		book.SetAuthor(ba.data());

		ba = ui.PublisherEdit->text().toLocal8Bit();//设置出版社
		book.SetPub(ba.data());//设置出版社
		book.SetQty(my_atoi(ui.QtyEdit->text().toLatin1().data()));//设置库存
		book.SetRetail(my_atof(ui.RetailEdit->text().toLatin1().data()));//设置零售价
		book.SetWholesale(my_atof(ui.WholesaleEdit->text().toLatin1().data()));//设置批发价
		ba = ui.DateAddedEdit->date().toString("yyyy-MM-dd").toLatin1(); // must
		book.SetDateAdded(ba.data());//设置进货日期
	}
	catch (const char* err)
	{
		QMessageBox box(QMessageBox::Warning, "提示", QString::fromLocal8Bit(err));
		box.exec();
		return;
	}
	QSqlQuery query(Sqlite::_database);
	QString sql;
	sql = "UPDATE books SET";
	sql = sql + " name =" + book.GetName();
	sql = sql + ",author =" + book.GetAuth();
	sql = sql + ",publisher =" + book.GetPub();
	sql = sql + ",qty =" + QString::number(book.GetQty());
	sql = sql + ",retail =" + QString::number(book.GetRetail(),10,2);
	sql = sql + ",wholesale =" + QString::number(book.GetWholesale(),10,2);
	sql = sql + " WHERE isbn=" + _q_result.value("isbn").toString();
	if (query.exec(sql))
	{
		QMessageBox box(QMessageBox::Information, "提示", "修改成功！");
		box.exec();
	}
	else
	{
		qDebug() << query.lastError();
		QMessageBox box(QMessageBox::Critical, "提示", "修改失败!未知错误!");
		box.exec();
	}
}
void ManageWindow::on_ButtonFaxConfirm_clicked()
{
	QByteArray ba = ui.LineEditFax->text().toLocal8Bit();
	double fax = my_atof(ba.data());
	if (fax < 0)
	{
		QMessageBox box(QMessageBox::Critical, "提示", "设置失败！税率只能是不小于0的小数！");
		box.exec();
	}
	else
	{
		SaleModel::SetFax(fax);
		QMessageBox box(QMessageBox::Information, "提示", "设置成功！");
		box.exec();
	}
}

void ManageWindow::on_LineEditFax_returnPressed()
{
	on_ButtonFaxConfirm_clicked();
}
