#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_ManageWindow.h"
#include "../h/library.h"
#include <qsqlrecord.h>
class ManageWindow : public QMainWindow
{
	Q_OBJECT

public:
	ManageWindow(QWidget* parent = Q_NULLPTR);

private:
	QSqlRecord _q_result;
	Ui::ManageWindowClass ui;
	void closeEvent(QCloseEvent* event);
private slots:
	void on_ButtonAdd_clicked();
	void on_ButtonISBNConfirm_clicked();
	void on_ButtonSave_clicked();
	void on_ButtonDelete_clicked();
	void on_ISBNInput_returnPressed();
	void on_ButtonFaxConfirm_clicked();
	void on_LineEditFax_returnPressed();
signals:
	void Close(std::string);
	
};
