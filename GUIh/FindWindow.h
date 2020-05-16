/*
	FindWindow.h
	“查找”窗口的头文件
*/
#pragma once
#include <QtWidgets/QMainWindow>
#include <ui_FindWindow.h>
#include "../h/library.h"
#include "../model_h/find.h"
class FindWindow : public QMainWindow
{
	Q_OBJECT

public:
	FindWindow(QWidget* parent = Q_NULLPTR);
	

private:
	Ui::FindWindowClass ui;
	FindModel* find_model;//创建model
	void FormatTableHeader();/*格式化标题，例如每次查询后将第一列列宽设置自动调整
							 如果没有本函数，在构造函数里直接设置为列宽按内容调整但没有内容会崩溃*/
private slots:
	void closeEvent(QCloseEvent* event);//关闭的时候告诉父窗口
	void on_ButtonFind_clicked();//点击查找按钮
	void on_LineEditContent_returnPressed();//按下回车键，直接调用点击查找按钮的槽函数
signals:
	void Close(std::string);//告诉父窗口自己关闭的信号函数
};