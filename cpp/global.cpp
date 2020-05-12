#include "../h/global.h"
#include <io.h>
#include "../model_h/Sale.h"
#include <qsettings.h>
#include <qdebug.h>
int my_atoi(const char* const& str)
{
	if (strlen(str) == 0)
		return -1;
	int ans = 0;
	for (int i = 0; i < strlen(str); i++)
	{
		if (str[i] < '0' || str[i]>'9')
			return -1;
		else
		{
			ans *= 10;
			ans += str[i] - '0';
		}
	}
	return ans;
}
double my_atof(const char* const& str)
{
	if (strlen(str) == 0)
		return -1;
	bool point = false;
	int i = 0;
	if (str[i] == '-')
		i++;
	if (str[i] == '.')
		return -1;
	for (; i < strlen(str); i++)
	{
		if (str[i] <= '9' && str[i] >= '0')
			continue;
		if (str[i] == '.')
		{
			if (!point)
			{
				point = true;
				continue;
			}
			else
			{
				return -1;
			}
		}
		else
		{
			return -1;
		}
	}
	return atof(str);
}
bool LoadConfig()
{
	QSettings configIni("config.ini", QSettings::IniFormat);
	QString fax_rate = configIni.value("Sale/fax_rate").toString();
	if (fax_rate != "")
	{
		double rate = my_atof(fax_rate.toStdString().data());
		if (rate >= 0)
			SaleModel::SetFax(rate);
	}
	return true;
}