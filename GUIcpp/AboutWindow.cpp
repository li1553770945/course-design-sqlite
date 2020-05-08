#include "../GUIh/AboutWindow.h"
AboutWindow::AboutWindow(QWidget* parent) :QDialog(parent)
{
	ui.setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);
}