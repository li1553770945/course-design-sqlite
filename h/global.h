#pragma once
#include "../GUIh/MainWindow.h"
#include <QSqlTableModel>

extern MainWindow* mainwindow_ptr;
int my_atoi(const char* const&);
double my_atof(const char* const&);
bool AccessFile();
bool OpenFile();
bool CreateFile();