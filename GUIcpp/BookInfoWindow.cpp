#include "../GUIh/BookInfoWindow.h"
#include <qdebug.h>
#include <QtWidgets/QMainWindow>
BookInfoWindow::BookInfoWindow(QWidget* parent)
	: QDialog(parent)
{
	setAttribute(Qt::WA_DeleteOnClose);
	ui.setupUi(this);
}
void BookInfoWindow::ReceiveBook(QSqlRecord record)
{
	ui.Name->setText(record.value("name").toString());
	ui.ISBN->setText(record.value("isbn").toString());
	ui.Author->setText(record.value("author").toString());
	ui.Publisher->setText(record.value("publisher").toString());
	ui.DateAdded->setText(record.value("date_added").toString());
	ui.Retail->setText(QString::number(record.value("publisher").toDouble(),10,2));
	ui.Wholesale->setText(QString::number(record.value("wholesale").toDouble(), 10, 2));
	ui.Qty->setText(QString::number(record.value("qty").toInt()));
}
