/*
	AboutWindow.h
	�����ڡ����ڵ�ͷ�ļ�
*/
#pragma once
#include "ui_AboutWindow.h"
class AboutWindow : public QDialog
{
	Q_OBJECT

public:
	AboutWindow(QWidget* parent = Q_NULLPTR);//���캯����û�о��幦��

private:
	Ui::AboutWindowClass ui;
};
