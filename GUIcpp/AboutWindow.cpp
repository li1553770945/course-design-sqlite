#include "../GUIh/AboutWindow.h"
AboutWindow::AboutWindow(QWidget* parent) :QDialog(parent)
{
	ui.setupUi(this);//设置ui
	setAttribute(Qt::WA_DeleteOnClose);//设置为关闭后立刻销毁
}