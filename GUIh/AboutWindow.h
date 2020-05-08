#pragma once
#include "ui_AboutWindow.h"
class AboutWindow : public QDialog
{
	Q_OBJECT

public:
	AboutWindow(QWidget* parent = Q_NULLPTR);

private:
	Ui::AboutWindowClass ui;
};
