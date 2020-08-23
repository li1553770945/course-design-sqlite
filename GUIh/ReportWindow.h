#pragma once
#include "ui_ReportWindow.h"
#include "../model_h/report.h"
class ReportWindow : public QMainWindow
{
	Q_OBJECT

public:
	ReportWindow(QWidget* parent = Q_NULLPTR);//构造函数
private:
	ReportModel* report_model;//创建Model
	Ui::ReportWindowClass ui;
	static const int _items_one_page_ = 100;//每页显示的最大条数
	int _max_page_;//最大页数，每次显示数据都会刷新
	int _page_=1;//当前页数
	void closeEvent(QCloseEvent* event);//关闭时告诉父窗口
	void SetData();//设置表格数据
	void FormatTableHeader();/*设置表头的格式，例如每次查询后将第一列列宽设置自动调整
	如果没有本函数，在构造函数里直接设置为列宽按内容调整但没有内容会崩溃*/
private slots:
	void on_CheckBoxName_clicked();
	void on_CheckBoxISBN_clicked();
	void on_CheckBoxAuthor_clicked();
	void on_CheckBoxPublisher_clicked();
	void on_CheckBoxDateAdded_clicked();
	void on_CheckBoxQty_clicked();
	void on_CheckBoxRetail_clicked();
	void on_CheckBoxWholesale_clicked();//这些函数用于响应点击显示的列时的复选框，显示/隐藏某些列
	void on_ButtonFlush_clicked();//刷新按钮，就是调用setData();
	void on_ButtonPreviousPage_clicked();//上一页
	void on_ButtonNextPage_clicked();//下一页
	void on_LineEditPage_returnPressed();//在页数输入框按下回车键，切换页
	void on_ButtonSortConfirm_clicked();//排序的确定按钮，其实和刷新一样
signals:
	void Close(std::string);
};

