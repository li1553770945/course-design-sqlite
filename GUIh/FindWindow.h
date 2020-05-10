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
	void FormatTableHeader();
private slots:
	void closeEvent(QCloseEvent* event);
	void on_ButtonFind_clicked();
	void on_LineEditContent_returnPressed();
signals:
	void Close(std::string);
};