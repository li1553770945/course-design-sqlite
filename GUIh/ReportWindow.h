#pragma once
#include "ui_ReportWindow.h"
#include "../model_h/report.h"
class ReportWindow : public QMainWindow
{
	Q_OBJECT

public:
	ReportWindow(QWidget* parent = Q_NULLPTR);//���캯��
private:
	ReportModel* report_model;//����Model
	Ui::ReportWindowClass ui;
	static const int _items_one_page_ = 100;//ÿҳ��ʾ���������
	int _max_page_;//���ҳ����ÿ����ʾ���ݶ���ˢ��
	int _page_=1;//��ǰҳ��
	void closeEvent(QCloseEvent* event);//�ر�ʱ���߸�����
	void SetData();//���ñ������
	void FormatTableHeader();/*���ñ�ͷ�ĸ�ʽ������ÿ�β�ѯ�󽫵�һ���п������Զ�����
	���û�б��������ڹ��캯����ֱ������Ϊ�п����ݵ�����û�����ݻ����*/
private slots:
	void on_CheckBoxName_clicked();
	void on_CheckBoxISBN_clicked();
	void on_CheckBoxAuthor_clicked();
	void on_CheckBoxPublisher_clicked();
	void on_CheckBoxDateAdded_clicked();
	void on_CheckBoxQty_clicked();
	void on_CheckBoxRetail_clicked();
	void on_CheckBoxWholesale_clicked();//��Щ����������Ӧ�����ʾ����ʱ�ĸ�ѡ����ʾ/����ĳЩ��
	void on_ButtonFlush_clicked();//ˢ�°�ť�����ǵ���setData();
	void on_ButtonPreviousPage_clicked();//��һҳ
	void on_ButtonNextPage_clicked();//��һҳ
	void on_LineEditPage_returnPressed();//��ҳ��������»س������л�ҳ
	void on_ButtonSortConfirm_clicked();//�����ȷ����ť����ʵ��ˢ��һ��
signals:
	void Close(std::string);
};

