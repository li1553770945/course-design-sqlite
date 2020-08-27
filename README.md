# <center>《面向对象程序设计课程设计》报告 </center>
[![](https://img.shields.io/github/v/release/li1553770945/course-design-sqlite?include_prereleases)](https://github.com/li1553770945/course-design-sqlite/releases)
![](https://img.shields.io/github/repo-size/li1553770945/course-design-sqlite) 
![](https://img.shields.io/badge/Qt-5.14.2-green)  

### <center>FIVESTAR图书管理系统的设计与实现</center>
  - [一、程序的主要功能](#1)
  - [二、系统总框架图](#2)
  - [三、系统各个类的说明](#3)
  - [四、比较有特色的函数](#4)
  - [五、存在的不足与对策、编程体会](#5)
  - [六、编程体会](#6)
  - [七、程序源代码](#7)

<h2 id=1>一、程序的主要功能</h2>
程序主要是按照课本要求完成，有一些细微的改动。

+ ### 主窗口
  用户可选择不同功能，可以查看关于，可以导入\导出为CSV。
+ ### 前台收银模块
  用户可输入ISBN来查找一本书，可以按指定数量添加到购物车。最后可以选择结算。用户在选择时可以点击查看书的详细信息，并且可以打开书库查看当前所有的图书信息，如果不知道一本书的全部信息，可以使用查找功能，输入书名、作者、出版社中的部分关键字就可以查到相关信息。
+ ### 管理模块
  管理模块一共有三个选项卡：
  +	添加：可以添加一本书，系统会自动检查信息的有效性以及是否有重复ISBN。
  + 编辑：用户输入一个ISBN查找一本书，可以对找到的书除ISBN之外的信息进行修改，可以删除一本书。
  + 修改税率：修改销售模块的交易税率。

+ ### 报表模块  
  可以查看当前书库所有的书，并支持显示部分列，支持按特定一列正序或逆序排序。为了防止书太多时程序响应时间过长，采用分页处理，每页只显示100本书，可以通过点击“上一页”“下一页”切换，或者也可以直接输入页数直达对应页。
<h2 id=2>二、系统总框架图</h2>

### 功能
[![dhACUU.md.png](https://s1.ax1x.com/2020/08/27/dhACUU.md.png)](https://imgchr.com/i/dhACUU)


### 架构
[![dhA9ET.png](https://s1.ax1x.com/2020/08/27/dhA9ET.png)](https://imgchr.com/i/dhA9ET)
  
<h2 id=3>三、系统各个类的说明</h2> 

1. ### 数据库相关
```cpp
class Sqlite {//数据库的一些操作
public:
	static QSqlDatabase _database;//数据库
	static bool Open();//打开或创建链接
	static bool CreateBooksTable();//创建books数据表
	static bool Close();//关闭连接
	static void LoadDataBase();//控制打开和检查的函数
};
```
```cpp
class BookOpe {//书的一些操作
public:
	enum class Result { Success, Fail, Exist };//用于标识插入/删除的结果
	static Result Insert(BookData&);//插入一本书，如果存在返回Result::Exit，未知错误失败返回Result::Fail
	static Result Delete(string& isbn);//根据传入的isbn，删除一本书
	static int QueryRow(string& isbn);//查询一本书所在的行数，若不存在返回-1。主要是为了判断是否存在
	static QSqlRecord Query(string& isbn);//根据传入的isbn，查找一本书的信息，返回QSqlRecord，如果不存在，返回结果的isValid()为false，需要调用端判断
```
2. ### 检验书的信息有效性相关，其实是上一个没用数据库版本的遗留，又懒得重写检验有效性
```cpp
class TitleInfo {//书的基本信息，固定
protected:
	char _isbn[13], _name[51], _author[31], _publisher[31];//都是英语，顾名思义
public:
	void SetName(const char* const& name);//设置书名，如果无效会throw一个const char *的错误，并包含错误原因
	void SetISBN(const char* const& isbn);//设置ISBN，如果无效会throw一个const char *的错误，并包含错误原因
	void SetAuthor(const char* const& author);//设置作者，如果无效会throw一个const char *的错误，并包含错误原因
	void SetPub(const char* const& publisher);//设置出版社，如果无效会throw一个const char *的错误，并包含错误原因
	const char* GetISBN()const;
	const char* GetName()const;
	const char* GetAuth()const;
	const char* GetPub()const;
};
```
```cpp
class BookData :public TitleInfo {//书的所有信息，可变的，数量等
protected:

	char _date_added[15];//进货日期
	int _qty;//库存
	double _whosale, _retail;//批发价、零售价
public:
	void SetDateAdded(const char* const&);//设置进货日期，如果无效会throw一个const char *的错误，并包含错误原因
	void SetQty(int);//设置库存，如果无效会throw一个const char *的错误，并包含错误原因
	void SetWholesale(double);//设置批发价，如果无效会throw一个const char *的错误，并包含错误原因
	void SetRetail(double);//设置零售价，如果无效会throw一个const char *的错误，并包含错误原因
	const char* GetDateAdded()const;
	double GetWholesale()const;
	double GetRetail()const;
	int GetQty()const;
};
```
3. ### 委托层，在项目里均以“XXXWindow”命名
#### 关于窗口
```cpp
class AboutWindow : public QDialog
{
	Q_OBJECT

public:
	AboutWindow(QWidget* parent = Q_NULLPTR);//构造函数，没有具体功能

private:
	Ui::AboutWindowClass ui;
};
```
#### 书的信息窗口
```cpp
class BookInfoWindow : public QDialog//书的信息窗口
{
	Q_OBJECT

public:
	BookInfoWindow(QWidget* parent = Q_NULLPTR);//构造函数
private slots:
	void ReceiveBook(QSqlRecord);//接收一本书的信息用于显示
private:
	Ui::BookInfoWindowClass ui;
};
```
#### 查找窗口
```cpp
class FindWindow : public QMainWindow//查找窗口
{
	Q_OBJECT

public:
	FindWindow(QWidget* parent = Q_NULLPTR);
	

private:
	Ui::FindWindowClass ui;
	FindModel* find_model;//创建model
	void FormatTableHeader();/*格式化标题，例如每次查询后将第一列列宽设置自动调整
							 如果没有本函数，在构造函数里直接设置为列宽按内容调整但没有内容会崩溃*/
private slots:
	void closeEvent(QCloseEvent* event);//关闭的时候告诉父窗口
	void on_ButtonFind_clicked();//点击查找按钮
	void on_LineEditContent_returnPressed();//按下回车键，直接调用点击查找按钮的槽函数
signals:
	void Close(std::string);//告诉父窗口自己关闭的信号函数
};
```
#### 主窗口
```cpp
class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);
public slots:
	void on_ButtonSale_clicked();
	void on_ButtonManage_clicked();
	void on_ButtonReport_clicked();//这里三个函数功能差不多，就是点击按钮时检测是否已经打开窗口，如果没打开就创建
	void on_ButtonExit_clicked();//点击关闭按钮时，调用this->close()函数
	void CloseSon(std::string);//控制子窗口指针，关闭时将指针变为NULL
	void on_ActionAbout_triggered();//点击菜单栏关于时，打开帮助窗口

private:
	Ui::MainWindowClass ui;
	SaleWindow *sale_window;
	ManageWindow *manage_window;
	ReportWindow *report_window;//这里有三个指针，分别指向对应的子窗口，如果指针为NULL，证明没有打开窗口
	void closeEvent(QCloseEvent* event);//在关闭时弹窗确认
	void LoadFile();//加载数据库、配置文件
};
```
#### 管理窗口
```cpp
class ManageWindow : public QMainWindow
{
	Q_OBJECT

public:
	ManageWindow(QWidget* parent = Q_NULLPTR);//构造函数

private:
	QSqlRecord _q_result;//在编辑选项卡输入ISBN点击确定时的返回结果，因为两个函数都要用，定义为了私有变量
	Ui::ManageWindowClass ui;
	void closeEvent(QCloseEvent* event);//关闭时告诉父窗口自己关闭了
private slots:
	void on_ButtonAdd_clicked();//点击添加时按钮时的功能，添加一本书
	void on_ButtonISBNConfirm_clicked();//输入ISBN点击查找按钮时的功能
	void on_ButtonSave_clicked();//点击保存按钮的功能
	void on_ButtonDelete_clicked();//点击删除按钮的功能
	void on_ISBNInput_returnPressed();//在ISBN输入框按下回车键，直接调用on_ButtonAdd_clicked()函数
	void on_ButtonFaxConfirm_clicked();//点击修改税率选项卡确定按钮
	void on_LineEditFax_returnPressed();//在修改税率的输入框按下回车建，直接调用on_ButtonFaxConfirm_clicked()函数
signals:
	void Close(std::string);//发送自己已经关闭信息的新号函数
};
```
#### 报表窗口
```cpp
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
```
#### 销售窗口
```cpp
class SaleWindow : public QMainWindow
{
	Q_OBJECT

public:
	SaleWindow(QWidget* parent);//构造函数
signals:
	void Close(std::string);//关闭的时候告诉父窗口
	void SendBook(QSqlRecord);//点击详细信息时，给打开的书的信息窗口发送当前书的信息
private:
	Ui::SaleWindowClass ui;
	SaleModel *sale_model;//创建model
	QSqlRecord _q_record_;//保存当前要添加到购物车的书的信息，也就是输入ISBN按下回车键的时候的查询结果
	void closeEvent(QCloseEvent* event);
	bool _add_enable_;//是否能增加，比如刚一打开时没有输入ISBN，不能增加
	void  AddEnable(bool);//处理能否增加的相应动作，例如不能增加时增加按钮不可点击
	ReportWindow* report_window;//打开书库窗口的指针
	FindWindow* find_window;//打开查找窗口的指针
	void FormatTableHeader();/*格式化标题，例如每次查询后将第一列列宽设置自动调整
							 如果没有本函数，在构造函数里直接设置为列宽按内容调整但没有内容会崩溃*/
	int _delete_row_;//点击右键选择要删除的行数

private slots:
	void on_Confirm_clicked();//输入ISBN，点击确定按钮的槽函数
	void on_ISBN_returnPressed();//输入ISBN按下回车，调用on_Confirm_clicked();
	void on_ButtonDetail_clicked();//点击详细信息按钮，打开书的信息窗口
	void on_ButtonLibrary_clicked();//点击书库按钮，打开书库窗口
	void SonClose(std::string);//处理子窗口关闭的函数
	void on_ButtonAddToCart_clicked();//点击添加到购物车按钮的槽函数
	void on_Num_returnPressed();//在数量输入框按下回车，调用on_ButtonAddToCart_clicked();
	void on_ButtonSattle_clicked();//点击结算按钮
	void on_ButtonFind_clicked();////点击查找按钮，打开查找窗口
	void on_ButtonClear_clicked();//点击清空按钮，清空所有信息
	void on_TableCart_customContextMenuRequested(const QPoint& pos);//右键购物车中的书，弹出菜单，用于处理删除
	void Delete();//删除购物车中的一条
	void ItemChange(QStandardItem*);//直接在购物车中双击修改数目
};
```
4. ### 模型层
#### 查找
```cpp
class FindModel: public QSqlQueryModel
{
public:
	QVariant data(const QModelIndex& item, int role) const;//使得数据能够居中
	FindModel(QObject *parent);//构造函数
	void SetHeader();//设置表头
};
```
#### 报表
```cpp
class ReportModel :public QSqlQueryModel
{
public:
	ReportModel(QObject *parent);//使得数据能够居中
	QVariant data(const QModelIndex& index, int role) const;//构造函数
	void SetHeader();//设置表头
};
```
#### 销售
```cpp
class SaleModel:public QStandardItemModel
{
	Q_OBJECT;
private:
	static double _fax_;//税率
	double _sum_;//购物车所有书的总金额
	std::vector <int> _num_;//用于存储每本书的购买数量，当用户直接输入数量，如果不符合规定，则按此数组恢复
	
	
public:
	void ItemChange(QStandardItem* item);//修改一个条目的数量时
	static void SetFax(double fax);//设置税率	
	static double GetFax();//得到税率
	SaleModel(QObject *parent);
	QVariant data(const QModelIndex& item, int role) const;//数据居中
	void AddItem(const QSqlRecord & record, int & num,bool &status,int &row);/*使用status的引用，如果为true则正常添加，引用row，返回要添加的书的所在行（如果已存在，返回所在行
	因为比如用户添加的书超过了库存，要告诉用户在哪一行）*/
	void clear();//清空所有条目并置零总金额
	double GetSum();//返回总金额
	double GetSumFaxed();//返回税后总金额
	bool Sattle();//结算，扣掉库存并清空
	void Delete(int row);//删除一个条目，请重新计算总金额
};
```
<h2 id=4>四、比较有特色的函数</h2>  

  1. global.cpp中的my_atoi和my_atof函数：原来自带的atoi和atof如果无法转换则返回0，但是有些数据，例如库存等是可能输入0的，为了区分到底是输入了0，还是输入错误，重写这两个函数，如果转换失败会返回一个负数，从而可以根据是否返回负数判断是否输入错误，如若用户本身输入负数，则本身就是错误的，因此不必担心是输入错误还是本身输入了负数（因为两种情况下输入都是错误的）。
  2. global.cpp中的 ChineseConvertPy函数（用于将汉字转化为拼音，该函数非自己完成，为网上摘抄），原来sqlite对于中文排序不正确的BUG困扰了很长时间，最后采用的方法是新增一列，专门用来存储拼音，在按名称排序时，不按真的名称排序，而是按照拼音排序。
  3. ReportWindow的翻页函数
   报表窗口实现了翻页功能，即便应对大量数据也不会因为渲染而卡顿，能自动检测总页数，识别第一页和最后一页。
  4. ReportWindow的SetData函数，顾名思义，就是用来设置数据的。里面因为原来的QSqlQuery功能不足，因此这里直接执行SQL语句进行查询。                                                                    

<h2 id=5>五、存在的不足与对策</h2>

1. ### 界面不够美观  
    虽然写了界面，但是事实上就是最最普通的界面，没有任何修饰。  
    对策：考虑到本程序为图书管理系统，因此效率至上，对于程序的美观度要求适当放宽。

2. ### 在模糊查询功能效率较低
   查找窗口的模糊查询功能使用了前通配，将会导致全表扫描，效率较低，磁盘IO和CPU使用都将比较高。
3. ### 分层架构有些问题
   有的函数为了方便，在委托层直接修改了数据，没有调用模型层函数   。
4. ### 只能导出为CSV
	开始想导出EXCEL，后来尝试了xlnt库和libxl，效果都不太满意，因此选择了相对妥协的方案导出EXCEL。
<h2 id=6>七、编程体会</h2>
写代码比较多的程序和写一个简单的程序比起来，需要注意很多问题。

1. 如果写一个几十行的程序，可以把变命名为"a","b","c1","c2"等，但是如果程序较长，这样的命名方式会导致混乱。
2. 本次课设让我对C++有了更深的理解。之前一直不清楚C++和C语言的区别，面向对象也只是一个抽象的概念，完全不能理解。现在终于明白了C++的面向对象思维。类的继承，多态，虚函数原来都这么巧妙。
<h2 id=7>八、程序源代码</h2>