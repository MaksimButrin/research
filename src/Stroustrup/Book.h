#pragma once

#include <iostream>
#include <QVector>
#include <QString>
#include <Chrono.h>

namespace liba
{

class Book
{
public:

	enum class StateBook
	{
		inStock,
		inUse,
		broken
	};

	struct InstanceBook
	{
		QString isbn;
		QString nameBook;
		QString nameAuthor;
		nsChrono::Date createDate{ nsChrono::defaultDate() };
		StateBook state{ StateBook::inStock };
	};

	Book();
	Book(const QString & isbn, const QString & nameBook, const QString & nameAuthor, const nsChrono::Date & createDate, const StateBook & state = StateBook::inStock);
	~Book();

	bool isInUse();
	bool isIsbnCorrect() const;

	bool setIsbn(const QString & isbn);

	void print() const;

	QString getIsbn() const;

	InstanceBook getBookInfo() const;
	QString bookInfoToString() const;

private:

	InstanceBook _book;
};

class Library
{
public:
	Library() {}
	~Library() {}
	
	bool addBook(const Book & book);

	void statusLibrary();
	void print();

private:
	QVector<Book> _library;
};


void runLibrary();

bool operator==(const Book::InstanceBook & lhs, const Book::InstanceBook & rhs);
bool operator!=(const Book::InstanceBook & lhs, const Book::InstanceBook & rhs);
//bool operator!=(const Book::getIsbn() & lhs, const Book::getIsbn() & rhs);

ostream& operator<<(ostream& out, const Book& book);
//ostream& operator<<(ostream& out, const Book::InstanceBook& book);

}

//QString enumToString(Enum value) const
//{
//	auto result = _defaultString;
//
//	auto it = std::find_if(std::begin(_table), std::end(_table),
//		[value](const Tuple & item)
//	{
//		return (std::get<0>(item) == value);
//	}
//	);
//
//	if (it != std::end(_table))
//	{
//		result = std::get<1>(*it);
//	}
//
//	return result;
//}