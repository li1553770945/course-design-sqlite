#include "../GUIh/AboutWindow.h"
AboutWindow::AboutWindow(QWidget* parent) :QDialog(parent)
{
	ui.setupUi(this);//����ui
	setAttribute(Qt::WA_DeleteOnClose);//����Ϊ�رպ���������
}