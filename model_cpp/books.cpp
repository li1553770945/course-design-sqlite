#include "../model_h/books.h"
#include "../h/global.h"
#include <qsqlrecord.h>
#include <qdebug.h>
#include "../model_h/sqlite.h"
#pragma execution_character_set("utf-8")
BookModel::BookModel(QObject* parent=(QObject*)nullptr):QSqlTableModel(parent)
{
    this->setTable("books");
    this->setHeaderData(1, Qt::Horizontal, "书名");
    this->setHeaderData(2, Qt::Horizontal, "ISBN");
    this->setHeaderData(3, Qt::Horizontal, "作者");
    this->setHeaderData(4, Qt::Horizontal, "出版社");
    this->setHeaderData(5, Qt::Horizontal, "进货日期");
    this->setHeaderData(6, Qt::Horizontal, "库存");
    this->setHeaderData(7, Qt::Horizontal, "零售价");
    this->setHeaderData(8, Qt::Horizontal, "批发价");
}

QVariant BookModel::data(const QModelIndex& item, int role) const
{
    QVariant value = QSqlQueryModel::data(item, role);
    if (role == Qt::TextAlignmentRole)
    {
        value = (Qt::AlignCenter);
        return value;
    }
    return value;
}
BookOpe::Result BookOpe::Insert(BookData& book)
{
    if (QueryRow(string(book.GetISBN())) != -1)
        return Result::Exist;
    QSqlQuery query(Sqlite::_database);
    query.prepare("insert into books(name,isbn,author,publisher,date_added,qty,retail,wholesale) VALUES (:name,:isbn,:author,:publisher,:date_added,:qty,:retail,:wholesale)");
    query.bindValue(":name", QString::fromLocal8Bit(book.GetName()));
    query.bindValue(":isbn", book.GetISBN());
    query.bindValue(":author", QString::fromLocal8Bit(book.GetAuth()));
    query.bindValue(":publisher", QString::fromLocal8Bit(book.GetPub()));
    query.bindValue(":date_added", book.GetDateAdded());
    query.bindValue(":qty", book.GetQty());
    query.bindValue(":retail", book.GetRetail());
    query.bindValue(":wholesale", book.GetWholesale());
    if (query.exec())
        return Result::Success;
    else
        return Result::Fail;
}
BookOpe::Result BookOpe::Delete(string &isbn)
{
    QSqlQuery query(Sqlite::_database);
    if (query.exec("DELETE FROM books WHERE isbn=" + QString::fromStdString(isbn) + ";"))
        return Result::Success;
    else
        return Result::Fail;
}
int  BookOpe::QueryRow(string& isbn)
{
    QSqlQuery query;
    query.exec("SELECT * FROM books WHERE isbn=" + QString::fromStdString(isbn) + ";");
    query.last();
    if (query.isValid())
    {
        return query.at();
    }
    else
    {
        return -1;
    }
}
QSqlRecord BookOpe::Query(string& isbn)
{
    QSqlQuery query(Sqlite::_database);
    query.exec("SELECT * FROM books WHERE isbn=" + QString::fromStdString(isbn) + ";");
    query.first();
    return query.record();
}
