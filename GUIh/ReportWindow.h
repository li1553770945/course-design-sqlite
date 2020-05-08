#pragma once
#include "ui_ReportWindow.h"
class ReportWindow : public QMainWindow
{
	Q_OBJECT

public:
	ReportWindow(QWidget* parent = Q_NULLPTR);


private:
	Ui::ReportWindowClass ui;
	static const int _item_one_page_=1000;
	int _max_page_;
	int _page_=1;
	void closeEvent(QCloseEvent* event);
	void SetData();
	void Initialize();
private slots:
	void on_CheckBoxName_clicked();
	void on_CheckBoxISBN_clicked();
	void on_CheckBoxAuthor_clicked();
	void on_CheckBoxPublisher_clicked();
	void on_CheckBoxDateAdded_clicked();
	void on_CheckBoxQty_clicked();
	void on_CheckBoxRetail_clicked();
	void on_CheckBoxWholesale_clicked();
	void on_ButtonFlush_clicked();
	void on_ButtonPreviousPage_clicked();
	void on_ButtonNextPage_clicked();
	void on_LineEditPage_returnPressed();
	void on_ButtonSortConfirm_clicked();
signals:
	void Close(std::string);
};

