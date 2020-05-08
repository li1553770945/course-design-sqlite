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
	void on_ButtonReport_clicked();
	void on_ButtonExit_clicked();
	void CloseSon(std::string);//�����Ӵ���ָ�룬�ر�ʱ��ָ���ΪNULL
	void on_ActionAbout_triggered();
	void on_ActionSave_triggered();
	void CloseProcess();
	void HandleResult(bool);

private:
	QProgressDialog* _dialog_;
	Ui::MainWindowClass ui;
	SaleWindow *sale_window;
	ManageWindow *manage_window;
	ReportWindow *report_window;
	void closeEvent(QCloseEvent* event);
	void LoadFile();
};

class OpenFileThread : public QThread
{
	Q_OBJECT
protected:
	void run();
signals:
	void ProcessEnd();
	void OpenResult(bool);
};

class SaveFileThread : public QThread
{
	Q_OBJECT
protected:
	void run();
signals:
	void ProcessEnd();
};