#include "Book.h"
#include <QRegExp> 
#include <QDebug> 


namespace liba
{


const QRegExp ISBN_RX{ "[0-9]-[A-Z]" };

Book::Book()
{
}

Book::Book(const QString & isbn, const QString & nameBook, const QString & nameAuthor, const nsChrono::Date & createDate, const StateBook & state)
	: _book{isbn, nameBook, nameAuthor, createDate, state}
{
}


Book::~Book()
{
}


bool Book::isInUse()
{
	return (_book.state == StateBook::inUse);
}

bool Book::isIsbnCorrect() const
{
	
	return _book.isbn.contains(ISBN_RX);
}

bool Book::setIsbn(const QString & isbn)
{
	if (isbn.contains(ISBN_RX))
	{
		_book.isbn = isbn;
		return true;
	}
	return false;
}

void Book::print() const
{
	auto message = bookInfoToString();

	qDebug().noquote() << message;
}

QString Book::getIsbn() const
{
	return _book.isbn;
}

Book::InstanceBook Book::getBookInfo() const
{
	return _book;
}

QString Book::bookInfoToString() const
{
	auto book = getBookInfo();

	auto info = QString("ISBN: '%1'\nBookName: '%2'\nAuthor: '%3'\nCreateDate: %4\n\n").arg(book.isbn).arg(book.nameBook).arg(book.nameAuthor).arg(book.createDate.toString());
	
	return info;
}

bool Library::addBook(const Book & book)
{
	QString message{"Book '%1', ISBN %2, status '%3'"};
	
	if (book.isIsbnCorrect())
	{
		_library.push_back(book);
		
		qDebug().noquote() << message.arg(book.getBookInfo().nameBook).arg(book.getBookInfo().isbn).arg("is added");

		return true;
	}
	
	qDebug().noquote() << message.arg(book.getBookInfo().nameBook).arg(book.getBookInfo().isbn).arg("no added");

	return false;
}

void Library::statusLibrary()
{
	qDebug().noquote() << QString("Count books equals %1").arg(_library.size());
}

void Library::print()
{
	for (auto & item : _library)
	{
		cout << item;
	}
}

void runLibrary()
{
	Library lib;

	lib.addBook(Book("00-11-RR", "book 1", "author 1", nsChrono::Date(2012, nsChrono::Month::aug, 10)));
	lib.addBook(Book("00-12-RR", "book 2", "author 2", nsChrono::Date(2012, nsChrono::Month::aug, 20)));
	lib.addBook(Book("00-13-hh", "book 3", "author 3", nsChrono::Date(2012, nsChrono::Month::aug, 30)));
	lib.addBook(Book("00-11-RR", "book 4", "author 4", nsChrono::Date(2012, nsChrono::Month::aug, 10)));

	lib.print();

	lib.statusLibrary();
	

}



bool operator==(const Book::InstanceBook & lhs, const Book::InstanceBook & rhs)
{
	return lhs.isbn == rhs.isbn;
}


bool operator!=(const Book::InstanceBook & lhs, const Book::InstanceBook & rhs)
{
	return lhs.isbn != rhs.isbn;
}

ostream & operator<<(ostream & out, const Book & book)
{
	return out << book.bookInfoToString().toStdString();
}

//ostream & operator<<(ostream & out, const Book::InstanceBook & book)
//{
//	// TODO: insert return statement here
//}


}