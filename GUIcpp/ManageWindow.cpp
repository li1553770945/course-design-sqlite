#include "../GUIh/ManageWindow.h"
#include "../h/library.h"
#include <qmessagebox.h>
#include "../h/global.h"
# pragma execution_character_set("utf-8")
ManageWindow::ManageWindow(QWidget* parent):QMainWindow(parent)
{
	ui.setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);
	ui.DateAddedAdd->setDate(QDate::currentDate());
	ui.LineEditFax->setText(QString::number(Sale::GetFax(),10,2));
}
void ManageWindow::closeEvent(QCloseEvent* event)
{
	emit Close(std::string("manage"));
}
void ManageWindow::on_ButtonAdd_clicked()
{
	BookData *book=new BookData;
	try
	{
		QByteArray ba = ui.NameAdd->text().toLocal8Bit();
		book->SetName(ba.data());//��������
		book->SetISBN(ui.ISBNAdd->text().toLatin1().data());
		ba = ui.AuthorAdd->text().toLocal8Bit();//��������
		book->SetAuthor(ba.data());
		ba = ui.PublisherAdd->text().toLocal8Bit();//���ó�����
		book->SetPub(ba.data());//���ó�����
		book->SetQty(my_atoi(ui.QtyAdd->text().toLatin1().data()));//���ÿ��
		book->SetRetail(my_atof(ui.RetailAdd->text().toLatin1().data()));//�������ۼ�
		book->SetWholesale(my_atof(ui.WholesaleAdd->text().toLatin1().data()));//����������
		ba = ui.DateAddedAdd->date().toString("yyyy-MM-dd").toLatin1(); // must
		book->SetDateAdded(ba.data());//���ý�������
	}
	catch (const char* err)
	{
		QMessageBox box(QMessageBox::Warning, "��ʾ", QString::fromLocal8Bit(err));
		box.exec();
		return;
	}
	if (Management::Add(book))
	{
		QMessageBox box(QMessageBox::Information, "��ʾ", "��ӳɹ���");
		box.exec();
	}
	else
	{
		QMessageBox box(QMessageBox::Information, "��ʾ", "���ʧ�ܣ���ISBN�Ѿ�����");
		box.exec();
	}
}
void ManageWindow::on_ButtonISBNConfirm_clicked()
{
	BooksIt it; 
	if (!Management::FindISBN(it, ui.ISBNInput->text().toStdString()))
	{
		QMessageBox message_box(QMessageBox::Warning, "��ʾ", "ISBN�����������������!", QMessageBox::Yes);
		message_box.exec();
	}
	else
	{
		ui.ButtonSave->setEnabled(true);
		ui.ButtonDelete->setEnabled(true);
		current_edit_book = &*it->second;
		current_it = it;
		ui.NameEdit->setText(QString::fromLocal8Bit(current_edit_book->GetName()));
		ui.ISBNEdit->setText(QString::fromLocal8Bit(current_edit_book->GetISBN()));
		ui.PublisherEdit->setText(QString::fromLocal8Bit(current_edit_book->GetPub()));
		ui.AuthorEdit->setText(QString::fromLocal8Bit(current_edit_book->GetAuth()));
		ui.QtyEdit->setText(QString::number(current_edit_book->GetQty()));
		ui.RetailEdit->setText(QString::number(current_edit_book->GetRetail(), 10, 2));
		ui.WholesaleEdit->setText(QString::number(current_edit_book->GetWholesale(), 10, 2));
		ui.DateAddedEdit->setDate(QDate::fromString(QString(current_edit_book->GetDateAdded()), "yyyy-MM-dd"));
	}
}
void ManageWindow::on_ButtonDelete_clicked()
{
	QMessageBox box(QMessageBox::Warning, "����", "��ȷ��Ҫɾ��ô���˲������ɻָ���",QMessageBox::Yes| QMessageBox::No);
	switch (box.exec())
	{
		case QMessageBox::Yes:
		{
			Management::Delete(current_it);
			ui.ButtonSave->setEnabled(false);
			ui.ButtonDelete->setEnabled(false);
			QMessageBox success(QMessageBox::Information, "��ʾ", "ɾ���ɹ���");
			success.exec();
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
	BookData *book=new BookData;
	try
	{
		QByteArray ba = ui.NameEdit->text().toLocal8Bit();
		book->SetName(ba.data());//��������
		book->SetISBN(ui.ISBNEdit->text().toLatin1().data());

		ba = ui.AuthorEdit->text().toLocal8Bit();//��������
		book->SetAuthor(ba.data());

		ba = ui.PublisherEdit->text().toLocal8Bit();//���ó�����
		book->SetPub(ba.data());//���ó�����
		book->SetQty(my_atoi(ui.QtyEdit->text().toLatin1().data()));//���ÿ��
		book->SetRetail(my_atof(ui.RetailEdit->text().toLatin1().data()));//�������ۼ�
		book->SetWholesale(my_atof(ui.WholesaleEdit->text().toLatin1().data()));//����������
		ba = ui.DateAddedEdit->date().toString("yyyy-MM-dd").toLatin1(); // must
		book->SetDateAdded(ba.data());//���ý�������
	}
	catch (const char* err)
	{
		QMessageBox box(QMessageBox::Warning, "��ʾ", QString::fromLocal8Bit(err));
		box.exec();
		return;
	}
	if (Management::Edit(current_it, book))
	{
		QMessageBox box(QMessageBox::Information, "��ʾ", "�޸ĳɹ���");
		box.exec();
	}
	else
	{
		QMessageBox box(QMessageBox::Information, "��ʾ", "�޸�ʧ�ܣ���ISBN�Ѿ����ڣ�");
		box.exec();
	}
}
void ManageWindow::on_ButtonFaxConfirm_clicked()
{
	QByteArray ba = ui.LineEditFax->text().toLocal8Bit();
	try {
		Sale::SetFax(ba.data());
		QMessageBox box(QMessageBox::Information, "��ʾ", "���óɹ���");
		box.exec();
	}
	catch (const char* err)
	{
		QMessageBox box(QMessageBox::Information, "��ʾ", QString::fromLocal8Bit(err));
		box.exec();
	}
}

void ManageWindow::on_LineEditFax_returnPressed()
{
	on_ButtonFaxConfirm_clicked();
}
