/*
	BookInfoWindow.h
	�������Ϣ�����ڵ�ͷ�ļ�
*/
#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_BookInfoWindow.h"
#include "../h/library.h"
#include <qsqlrecord.h>
class BookInfoWindow : public QDialog
{
	Q_OBJECT

public:
	BookInfoWindow(QWidget* parent = Q_NULLPTR);//���캯��
private slots:
	void ReceiveBook(QSqlRecord);//����һ�������Ϣ������ʾ
private:
	Ui::BookInfoWindowClass ui;
};