#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_ManageWindow.h"
#include "../h/library.h"
#include <qsqlrecord.h>
class ManageWindow : public QMainWindow
{
	Q_OBJECT

public:
	ManageWindow(QWidget* parent = Q_NULLPTR);//���캯��

private:
	QSqlRecord _q_result;//�ڱ༭ѡ�����ISBN���ȷ��ʱ�ķ��ؽ������Ϊ����������Ҫ�ã�����Ϊ��˽�б���
	Ui::ManageWindowClass ui;
	void closeEvent(QCloseEvent* event);//�ر�ʱ���߸������Լ��ر���
private slots:
	void on_ButtonAdd_clicked();//������ʱ��ťʱ�Ĺ��ܣ����һ����
	void on_ButtonISBNConfirm_clicked();//����ISBN������Ұ�ťʱ�Ĺ���
	void on_ButtonSave_clicked();//������水ť�Ĺ���
	void on_ButtonDelete_clicked();//���ɾ����ť�Ĺ���
	void on_ISBNInput_returnPressed();//��ISBN������»س�����ֱ�ӵ���on_ButtonAdd_clicked()����
	void on_ButtonFaxConfirm_clicked();//����޸�˰��ѡ�ȷ����ť
	void on_LineEditFax_returnPressed();//���޸�˰�ʵ�������»س�����ֱ�ӵ���on_ButtonFaxConfirm_clicked()����
signals:
	void Close(std::string);//�����Լ��Ѿ��ر���Ϣ���ºź���
};
