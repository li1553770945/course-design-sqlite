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
	//用于增加测试书，慎重使用！
	/*for (int i = 1; i <= 100; i++)
	{
		BookData* book = new BookData;
		char s[10];
		sprintf(s, "%d", i);
		book->SetName((string("书名")+string(s)).data());
		book->SetISBN(s);
		book->SetAuthor((string("作者") + string(s)).data());
		book->SetPub((string("出版社") + string(s)).data());
		book->SetDateAdded("2020-04-29");
		book->SetQty(10);
		book->SetRetail(10.5);
		book->SetWholesale(10);
		Management::Add(book);

	}*/
	return a.exec();
}
