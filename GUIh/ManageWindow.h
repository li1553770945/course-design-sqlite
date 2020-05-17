#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_ManageWindow.h"
#include "../h/library.h"
#include <qsqlrecord.h>
class ManageWindow : public QMainWindow
{
	Q_OBJECT

public:
	ManageWindow(QWidget* parent = Q_NULLPTR);//构造函数

private:
	QSqlRecord _q_result;//在编辑选项卡输入ISBN点击确定时的返回结果，因为两个函数都要用，定义为了私有变量
	Ui::ManageWindowClass ui;
	void closeEvent(QCloseEvent* event);//关闭时告诉父窗口自己关闭了
private slots:
	void on_ButtonAdd_clicked();//点击添加时按钮时的功能，添加一本书
	void on_ButtonISBNConfirm_clicked();//输入ISBN点击查找按钮时的功能
	void on_ButtonSave_clicked();//点击保存按钮的功能
	void on_ButtonDelete_clicked();//点击删除按钮的功能
	void on_ISBNInput_returnPressed();//在ISBN输入框按下回车键，直接调用on_ButtonAdd_clicked()函数
	void on_ButtonFaxConfirm_clicked();//点击修改税率选项卡确定按钮
	void on_LineEditFax_returnPressed();//在修改税率的输入框按下回车建，直接调用on_ButtonFaxConfirm_clicked()函数
signals:
	void Close(std::string);//发送自己已经关闭信息的新号函数
};
