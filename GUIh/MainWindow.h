#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include "SaleWindow.h"
#include "ReportWindow.h"
#include "MainWindow.h"
#include "ManageWindow.h"
#include <QProgressDialog>
#include <qthread.h>
class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);
public slots:
	void on_ButtonSale_clicked();
	void on_ButtonManage_clicked();
	void on_ButtonReport_clicked();//���������������ܲ�࣬���ǵ����ťʱ����Ƿ��Ѿ��򿪴��ڣ����û�򿪾ʹ���
	void on_ButtonExit_clicked();//����رհ�ťʱ������this->close()����
	void CloseSon(std::string);//�����Ӵ���ָ�룬�ر�ʱ��ָ���ΪNULL
	void on_ActionAbout_triggered();//����˵�������ʱ���򿪰�������

private:
	Ui::MainWindowClass ui;
	SaleWindow *sale_window;
	ManageWindow *manage_window;
	ReportWindow *report_window;//����������ָ�룬�ֱ�ָ���Ӧ���Ӵ��ڣ����ָ��ΪNULL��֤��û�д򿪴���
	void closeEvent(QCloseEvent* event);//�ڹر�ʱ����ȷ��
	void LoadFile();//�������ݿ⡢�����ļ�
};
