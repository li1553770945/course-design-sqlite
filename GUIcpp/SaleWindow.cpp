#include "../GUIh/SaleWindow.h"
#include <qevent.h>
#include <qmessagebox.h>
#include "../h/library.h"
#include "../h/global.h"
#include "../GUIh//BookInfoWindow.h"
#include "../GUIh/ReportWindow.h"
#include "../GUIh/FindWindow.h"
# pragma execution_character_set("utf-8")
SaleWindow::SaleWindow(QWidget* parent)
	: QMainWindow(parent)
{
	this->setAttribute(Qt::WA_DeleteOnClose);
	ui.setupUi(this);
	ui.Fax->setText(QString::number(Sale::GetFax(), 10, 2));
	select = false;
	find_window = NULL;
	report_window = NULL;
	ui.TableCart->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui.TableCart->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
}
void SaleWindow::on_Confirm_clicked()
{
	BooksIt it;
	if (!Management::FindISBN(it, ui.ISBN->text().toStdString()))
	{
		QMessageBox message_box(QMessageBox::Warning, "��ʾ", "ISBN�����������������!", QMessageBox::Yes);
		message_box.exec();
	}
	else
	{
		_sale_.choose_book =&*(it->second);
		ui.Name->setText(QString::fromLocal8Bit(_sale_.choose_book->GetName()));
		ui.Qty->setText(QString::number(_sale_.choose_book->GetQty()));
		ui.Retail->setText(QString::number(_sale_.choose_book->GetRetail(),10,2));
		Select(true);
	}
}
void SaleWindow::closeEvent(QCloseEvent* event)
{

	if (ui.TableCart->rowCount() != 0)
	{
		QMessageBox box(QMessageBox::Warning, "����", "���Ĺ��ﳵ�д��������Ʒ���˳��󽫲��ᱣ�棡��ȷ��Ҫ�˳�ô��", QMessageBox::Yes | QMessageBox::No);
		switch (box.exec())
		{
		case QMessageBox::Yes:
			ui.TableCart->clearContents();
			emit Close(std::string("sale"));
			break;
		default:
			event->ignore();
		}
	}
	else
	{
		ui.TableCart->clearContents();
		emit Close(std::string("sale"));
	}
	
}
void SaleWindow::on_ISBN_returnPressed()
{
	on_Confirm_clicked();
}
void SaleWindow::on_ButtonDetail_clicked()
{
		BookInfoWindow* book_info_window = new BookInfoWindow;
		connect(this, SIGNAL(SendBookPtr(const BookData*)), book_info_window, SLOT(ReceiveBookPtr(const BookData*)));
		emit SendBookPtr(&*_sale_.choose_book);
		book_info_window->exec();
}
void SaleWindow::on_ButtonLibrary_clicked()
{
	if (report_window == NULL)
	{
		report_window = new ReportWindow(this);
		connect(report_window, SIGNAL(Close(std::string)), this, SLOT(SonClose(std::string)));
		report_window->show();
	}
	else
	{
		report_window->showNormal();
		report_window->activateWindow();
	}
}
void SaleWindow::on_ButtonAddToCart_clicked()
{

	QByteArray ba = ui.Num->text().toLatin1(); // must
	int num = my_atoi(ba.data());
	if (num <= 0)
	{
		QMessageBox box(QMessageBox::Information, "��ʾ", "��������Ϊ����0��������");
		box.exec();
		return;
	}
	
	ui.TableCart->disconnect(SIGNAL(cellChanged(int,int)));
	int status;
	int row;
	_sale_.AddItem(_sale_.choose_book, num, status, row);
	if (status== Sale::SUCCESS||status==(Sale::EXIST|Sale::SUCCESS))
	{
		if (row >= ui.TableCart->rowCount())
		{
			ui.TableCart->insertRow(row);
		}
		ui.TableCart->setItem(row, 0, new QTableWidgetItem(QString::fromLocal8Bit(_sale_.choose_book->GetName())));//��ӱ��
		ui.TableCart->setItem(row, 1, new QTableWidgetItem(QString::number(_sale_.choose_book->GetRetail(), 10, 2)));
		ui.TableCart->setItem(row, 2, new QTableWidgetItem(QString::number(num)));
		ui.TableCart->setItem(row, 3, new QTableWidgetItem(QString::number(_sale_.choose_book->GetRetail() * num, 10, 2)));
		for (int j = 0; j < 4; j++)
		{
			ui.TableCart->item(row, j)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		}
		ui.TableCart->item(row, 0)->setFlags(Qt::NoItemFlags);
		ui.TableCart->item(row, 1)->setFlags(Qt::NoItemFlags);
		ui.TableCart->item(row, 3)->setFlags(Qt::NoItemFlags);
		ui.Sum->setText(QString::number(_sale_.GetSum(), 10, 2));
		ui.SumFaxed->setText(QString::number(_sale_.GetSumFaxed() ,10, 2));
		ui.ISBN->setText("");
		ui.Num->setText("");
	}
	else if (status == Sale::OVERQTY)
	{
		QMessageBox box(QMessageBox::Information, "��ʾ", "���Ĺ������Ѿ�������棡");
		box.exec();
	}
	else if (status == Sale::OVERQTY|Sale::EXIST)
	{
		char message[100];
		sprintf(message,"���ﳵ�Ѿ����ڴ��飬λ�ڵ�%d��,�����Ѿ���������������Ĺ������Ѿ�������棡",row+1);
		QMessageBox box(QMessageBox::Information, "��ʾ", message);
		box.exec();
	}
	connect(ui.TableCart, SIGNAL(cellChanged(int, int)), this, SLOT(on_TableCart_cellChanged(int,int)));
}
void SaleWindow::on_Num_returnPressed()
{
	if(select)
		on_ButtonAddToCart_clicked();
	else
	{
		QMessageBox box(QMessageBox::Information, "��ʾ", "����ѡ��һ���飡");
		box.exec();
	}
}
void SaleWindow::on_ButtonSattle_clicked()//���㰴ť
{
	if(!_sale_.IsEmpty())
	{
		_sale_.Sattle();
		ui.TableCart->clearContents();
		ui.TableCart->setRowCount(0);
		ui.Sum->setText("");
		ui.SumFaxed->setText("");
		ui.Name->setText("");
		ui.Qty->setText("");
		ui.Retail->setText("");
		_sale_.choose_book = NULL;
		Select(false);
		QMessageBox box(QMessageBox::Information, "��ʾ", "�����ѳɹ���");
		box.exec();
	}
	else
	{
		QMessageBox box(QMessageBox::Information, "��ʾ", "��ǰ���ﳵΪ�գ�");
		box.exec();
	}
}
void SaleWindow::Select(bool flag)//�ı䵱ǰ�Ƿ��Ѿ�ѡ��һ���飨�������棬�����ڱ����ѡ��
{
	if (flag == false)
	{
		select = false;
		ui.ButtonAddToCart->setEnabled(false);//���û��ѡ����ô��ӵ����ﳵ����ϸ��Ϣ��ť������ʹ��
		ui.ButtonDetail->setEnabled(false);
	}
	else
	{
		select = true;
		ui.ButtonAddToCart->setEnabled(true);
		ui.ButtonDetail->setEnabled(true);
	}
}
void SaleWindow::on_ButtonFind_clicked()
{
	if (find_window == NULL)
	{
		find_window = new FindWindow(this);
		connect(find_window, SIGNAL(Close(std::string)), this, SLOT(SonClose(std::string)));
		find_window->show();
	}
	else
	{
		find_window->showNormal();
		find_window->activateWindow();
	}
}
void SaleWindow::SonClose(std::string name)
{
	if (name == "report")
	{
		report_window = NULL;
	}
	if (name == "find")
	{
		find_window = NULL;
	}
}
void SaleWindow::on_TableCart_cellChanged(int row,int column)//˫���޸�����
{
	QByteArray ba=ui.TableCart->item(row, column)->text().toLatin1();
	int num = my_atoi(ba.data());
	if (num <= 0)
	{
		QMessageBox box(QMessageBox::Information, "��ʾ", "��������Ϊ����0��������");
		box.exec();
		ui.TableCart->disconnect(SIGNAL(cellChanged(int, int)));
		ui.TableCart->setItem(row, 2, new QTableWidgetItem(QString::number(_sale_.GetNum(row))));//��ԭ�û�����
		ui.TableCart->item(row, 2)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		connect(ui.TableCart, SIGNAL(cellChanged(int, int)), this, SLOT(on_TableCart_cellChanged(int, int)));
		return;
	}
	if (_sale_.ChangeItem(row, num))
	{
	
		ui.TableCart->disconnect(SIGNAL(cellChanged(int, int)));
		ui.TableCart->setItem(row, 3, new QTableWidgetItem(QString::number(_sale_.GetRetail(row)*num,10,2)));//�����ܼ�
		ui.TableCart->item(row, 3)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		connect(ui.TableCart, SIGNAL(cellChanged(int, int)), this, SLOT(on_TableCart_cellChanged(int, int)));
		ui.Sum->setText(QString::number(_sale_.GetSum()));
		ui.SumFaxed->setText(QString::number(_sale_.GetSumFaxed()));
		return;
	}
	else
	{
		QMessageBox box(QMessageBox::Information, "��ʾ",QString("���Ĺ������Ѿ��������")+QString::number(_sale_.GetQty(row))+QString("!"));
		box.exec();
		ui.TableCart->disconnect(SIGNAL(cellChanged(int, int)));
		ui.TableCart->setItem(row, 2, new QTableWidgetItem(QString::number(_sale_.GetNum(row))));//��ԭ�û�����
		ui.TableCart->item(row, 2)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		connect(ui.TableCart, SIGNAL(cellChanged(int, int)), this, SLOT(on_TableCart_cellChanged(int, int)));
		return;
	}
}
void SaleWindow::on_ButtonClear_clicked()
{
	if (_sale_.IsEmpty())
	{
		QMessageBox box(QMessageBox::Information, "��ʾ", "��ǰ���ﳵΪ�գ�");
		box.exec();
		return;
	}
	QMessageBox box(QMessageBox::Warning, "����", "��ȷ��Ҫ����֧������չ��ﳵô���ò������ɻָ���",QMessageBox::Yes|QMessageBox::No);
	switch (box.exec())
	{
	case QMessageBox::Yes:
		_sale_.choose_book = NULL;
		ui.TableCart->clearContents();
		ui.TableCart->setRowCount(0);
		ui.Sum->setText("");
		ui.SumFaxed->setText("");
		_sale_.Clear();
		ui.Name->setText("");
		ui.Qty->setText("");
		Select(false);
	}
}
void SaleWindow::on_TableCart_customContextMenuRequested(const QPoint &pos)
{
	QModelIndex index = ui.TableCart->indexAt(pos);
	int row = index.row(); // ��ȡ���������
	_delete_row_ = row;
	if (row == -1)
		return;
	QMenu *menu=new QMenu(this);
	QAction *action=new QAction("ɾ��",this);
	connect(action, SIGNAL(triggered()), this, SLOT(Delete()));
	menu->addAction(action);
	menu->exec(QCursor::pos());
	
	
}
void SaleWindow::Delete()
{
	_sale_.DeleteItem(_delete_row_);
	ui.TableCart->removeRow(_delete_row_);
	ui.Sum->setText(QString::number(_sale_.GetSum()));
	ui.SumFaxed->setText(QString::number(_sale_.GetSumFaxed()));
}