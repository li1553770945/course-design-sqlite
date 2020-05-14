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
	FindModel* find_model;
	void FormatTableHeader();/*��ʽ�����⣬����ÿ�β�ѯ�󽫵�һ���п������Զ�����
							 ���û�У�ֱ�����ð����ݵ�����û�����ݻ�����*/
private slots:
	void closeEvent(QCloseEvent* event);//�رյ�ʱ����߸�����
	void on_ButtonFind_clicked();//������Ұ�ť
	void on_LineEditContent_returnPressed();//���»س�����ֱ�ӵ��õ�����Ұ�ť�Ĳۺ���
signals:
	void Close(std::string);//
};