#include "../GUIh/MainWindow.h"
#include <qtranslator.h>
//#include <vld.h>
using namespace std;
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	QTranslator translator;
	translator.load("qrc/qt_zh_CN");
	a.installTranslator(&translator);
	w.show();
	//�������Ӳ����飬����ʹ�ã�
	/*for (int i = 1; i <= 100; i++)
	{
		BookData* book = new BookData;
		char s[10];
		sprintf(s, "%d", i);
		book->SetName((string("����")+string(s)).data());
		book->SetISBN(s);
		book->SetAuthor((string("����") + string(s)).data());
		book->SetPub((string("������") + string(s)).data());
		book->SetDateAdded("2020-04-29");
		book->SetQty(10);
		book->SetRetail(10.5);
		book->SetWholesale(10);
		Management::Add(book);

	}*/
	return a.exec();
}
