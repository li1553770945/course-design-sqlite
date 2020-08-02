#include "../GUIh/MainWindow.h"
#include <qtranslator.h>
#include "../h/global.h"
using namespace std;
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	QTranslator translator;
	translator.load("qrc/qt_zh_CN");
	a.installTranslator(&translator);
	w.show();
	return a.exec();
}
