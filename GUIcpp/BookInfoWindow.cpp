//#include "../GUIh/BookInfoWindow.h"
//#include <qdebug.h>
//#include <QtWidgets/QMainWindow>
//BookInfoWindow::BookInfoWindow(QWidget* parent)
//	: QDialog(parent)
//{
//	
//	book = NULL;
//	setAttribute(Qt::WA_DeleteOnClose);
//	ui.setupUi(this);
//}
//void BookInfoWindow::SetData()
//{
//	ui.Name->setText(QString::fromLocal8Bit(book->GetName()));
//	ui.Author->setText(QString::fromLocal8Bit(book->GetAuth()));
//	ui.Publisher->setText(QString::fromLocal8Bit(book->GetPub()));
//	ui.ISBN->setText(QString(book->GetISBN()));
//	ui.DateAdded->setText(QString(book->GetDateAdded()));
//	ui.Retail->setText(QString::number(book->GetRetail(),10,2));
//	ui.Wholesale->setText(QString::number(book->GetWholesale(),10,2));
//	ui.Qty->setText(QString::number(book->GetQty()));
//}
//void BookInfoWindow::ReceiveBookPtr(const BookData* ptr)
//{
//	book = ptr;
//	SetData();
//}
