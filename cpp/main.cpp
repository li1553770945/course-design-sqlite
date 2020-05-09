#include "../GUIh/MainWindow.h"
#include <qtranslator.h>
#include "../model_h/sqlite.h"
#include "../h/global.h"
using namespace std;
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	mainwindow_ptr = &w;
	QTranslator translator;
	translator.load("qrc/qt_zh_CN");
	a.installTranslator(&translator);
	w.show();
	return a.exec();
}
