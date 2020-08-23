#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_SaleWindow.h"
#include "../h/library.h"
#include "../GUIh/FindWindow.h"
#include "../GUIh/ReportWindow.h"
#include "../model_h/Sale.h"
class SaleWindow : public QMainWindow
{
	Q_OBJECT

public:
	SaleWindow(QWidget* parent);//���캯��
signals:
	void Close(std::string);//�رյ�ʱ����߸�����
	void SendBook(QSqlRecord);//�����ϸ��Ϣʱ�����򿪵������Ϣ���ڷ��͵�ǰ�����Ϣ
private:
	Ui::SaleWindowClass ui;
	SaleModel *sale_model;//����model
	QSqlRecord _q_record_;//���浱ǰҪ��ӵ����ﳵ�������Ϣ��Ҳ��������ISBN���»س�����ʱ��Ĳ�ѯ���
	void closeEvent(QCloseEvent* event);
	bool _add_enable_;//�Ƿ������ӣ������һ��ʱû������ISBN����������
	void  AddEnable(bool);//�����ܷ����ӵ���Ӧ���������粻������ʱ���Ӱ�ť���ɵ��
	ReportWindow* report_window;//����ⴰ�ڵ�ָ��
	FindWindow* find_window;//�򿪲��Ҵ��ڵ�ָ��
	void FormatTableHeader();/*��ʽ�����⣬����ÿ�β�ѯ�󽫵�һ���п������Զ�����
							 ���û�б��������ڹ��캯����ֱ������Ϊ�п����ݵ�����û�����ݻ����*/
	int _delete_row_;//����Ҽ�ѡ��Ҫɾ��������

private slots:
	void on_Confirm_clicked();//����ISBN�����ȷ����ť�Ĳۺ���
	void on_ISBN_returnPressed();//����ISBN���»س�������on_Confirm_clicked();
	void on_ButtonDetail_clicked();//�����ϸ��Ϣ��ť���������Ϣ����
	void on_ButtonLibrary_clicked();//�����ⰴť������ⴰ��
	void SonClose(std::string);//�����Ӵ��ڹرյĺ���
	void on_ButtonAddToCart_clicked();//�����ӵ����ﳵ��ť�Ĳۺ���
	void on_Num_returnPressed();//������������»س�������on_ButtonAddToCart_clicked();
	void on_ButtonSattle_clicked();//������㰴ť
	void on_ButtonFind_clicked();////������Ұ�ť���򿪲��Ҵ���
	void on_ButtonClear_clicked();//�����հ�ť�����������Ϣ
	void on_TableCart_customContextMenuRequested(const QPoint& pos);//�Ҽ����ﳵ�е��飬�����˵������ڴ���ɾ��
	void Delete();//ɾ�����ﳵ�е�һ��
	void ItemChange(QStandardItem*);//ֱ���ڹ��ﳵ��˫���޸���Ŀ
};

