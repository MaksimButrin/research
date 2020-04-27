#include <iostream>
#include <QPair>
#include <QVector>
//#include <std_lib_facilities.h>
//#include <tuple>
//#include <string>
//#include <set>
//#include <map>

using namespace std;


void init();

//------------------------------------------------------------------------------
/* GRAMMAR
 * =======
 * Calculation:
 *      Statement
 *      Print
 *      Quit
 *      Calculation Statement
 *
 * Statement:
 *      Declaration
 *      Expression
 *
 * Declaration:
 *      "let" Name "=" Expression
 */
 //------------------------------------------------------------------------------

class Token
{
public:
	Token(const char kind);
	Token(const char kind, const double value);
	Token(const char kind, const QString &name);
	~Token();

	void printValue();

	char getKind();
	QString getVarName();
	double getValue();

private:
	char _kind = ' ';
	double _value{ 0.0 };
	QString _name;

};

class TokenStream 
{
public:
	TokenStream() {};
	Token getToken();            // get a Token
	void putback(Token t);  // put a Token back
	void ignore(const char & ch);

private:
	bool _full{ false };      // is there a Token in the buffer?
	Token _buffer = { '0' };           // where we store a 'putback' Token
};


class variable
{
public:
	variable(const QString & name = "", const double & value = 0.0);
	~variable() {}
	
	QPair<QString, double> getVariable();
	QString getName();
	double getValue();

	void setValue(const double & value);

private:
	QString _name;
	double _value;

};


class StrausCalc
{
public:
	StrausCalc() {}
	~StrausCalc() {}

	
	// statement (инструкция) as example this is 'let'
	double statement(TokenStream & ts);
	// handles '+' & '-'
	double expression(TokenStream & ts);
	// handles '*', '/' & '%'
	double term(TokenStream & ts);
	// deal with '!'
	double extra(TokenStream & ts);
	// handles numbers and brackets
	double primary(TokenStream & ts);
	
	int calcRun();
	void calculate();

	//
	double getVariableValue(const QString &name, bool *result = nullptr);
	void setVariableValue(const QString &name, const double &value, bool *result = nullptr);
	bool isVariableDeclared(const QString &variableName);
	void defineVariable(const QString &variableName, const double &variableValue, QString *error = nullptr);
	double declaration(TokenStream & ts, QString * error = nullptr);

	//
	void keepWindowOpen();
	void keepWindowOpen(string s);
	//void cleanUpMessage();
	void temporary(const QVector<int> & v);
	void temporary(const QVector<int> * v);
	void temporary(const vector<int> & v);


private:
	TokenStream _tokenStream;
	QVector<variable> _variableStorage;
};



class Chapter7dot01
{
public:
	Chapter7dot01();
	~Chapter7dot01();

	void temporary();
	void calcMain();

private:

};