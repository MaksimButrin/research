#include <Stroustrup.h>

#include <QDebug>
#include <QString>
//#include <string>
//#include <QPair>
//#include <tuple>
//#include <utility>
//#include <vector>
//#include <sstream>


using namespace std;

void init()
{

}


Chapter7dot01::Chapter7dot01()
{
}

Chapter7dot01::~Chapter7dot01()
{
	//qDebug() << "\n";
}



void Chapter7dot01::calcMain()
{
	int lval = 0;
	int rval{ 0 };
	char op;
	int res{ 0 };
	QString expression{ "" };

	// „тение чего - то наподобие 1 + 3
	cin >> lval;
	if (!cin)
		qDebug().noquote() << "No left value";

	for (char op; cin >> op;)
	{
		if (op != 'x')
		{
			cin >> rval;
		}

		if (!cin)
		{
			qDebug().noquote() << "No right value";
		}

		expression += op;

		switch (op)
		{
		case '+':
			lval += rval; // lval = lval + rval
			break;

		case '-':
			lval -= rval; // lval = lval - rval
			break;

		case '*':
			lval *= rval; // lval = lval * rval
			break;

		case '/':
			lval /= rval; // lval = lval / rval
			break;

		default:
			qDebug().noquote() << "Result is: " << lval;
			return;
		}

	}

	qDebug().noquote() << QString("Wrong expression '%1'").arg(expression);
	return;


}

/* ==================================== Calculator ======================================== */
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


const QString MESSAGE_ERROR_01{ "Error : %1" };
const QString MESSAGE_RESULT_01{ "Result is equals %1" };
const char NUMBER = '8'; //token._kind is 
const char QUIT = 'q'; // the token for exiting program
const char END_EXPR = ';'; // the token for setting end an expression
const string PROMPT = "> "; // the token for setting end an expression
const char NAME = 'a';
const char LET = 'L';
const string DECL_KEY = "let"; // the key word 'let'

Token::Token(const char kind, const double value) :
	_kind(kind), _value(value)
{
}

Token::Token(const char kind, const QString & varName)
	: _kind(kind), _value(0.0), _name(varName)
{
}

Token::Token(const char kind) 
	: _kind(kind), _value(0.0)
{
}

Token::~Token()
{
}

void Token::printValue()
{
	qDebug().noquote() << QString("Kind is equals '%1', value is equals '%2'").arg(getKind()).arg(getValue());
}

char Token::getKind()
{
	return _kind;
}


QString Token::getVarName()
{
	return _name;
}


double Token::getValue()
{
	return _value;
}

void Chapter7dot01::temporary()
{
	Token t2{ '+', 2.2 };
	t2.printValue();

	//calcMain();
}

/*Token StrausCalc::getToken()
{
	char ch;
	cin >> ch;    // note that >> skips whitespace (space, newline, tab, etc.)

	switch (ch)
	{
		//not yet   case ';':    // for "print"
		//not yet   case 'q':    // for "quit"
	case '(':
	case ')':
	case '+':
	case '-':
	case '*':
	case '/':
		return Token(ch); // let each character represent itself
	case '.':
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
	{
		cin.putback(ch); // put digit back into the input stream
		double val;
		cin >> val;		// read a floating-point number
		return Token('8', val); // let '8' represent "a number"
	}
	default:
		qDebug().noquote() << ERROR_MESSAGE_01.arg("Bad token");
	}

}*/

double StrausCalc::statement(TokenStream & ts)
{
	auto t = ts.getToken();
	switch (t.getKind())
	{
	case LET:
		return declaration(ts);
	default:
		ts.putback(t);
		return expression(ts);
	}
}

double StrausCalc::expression(TokenStream & ts)
{
	//qDebug().noquote() << "\n" << __FUNCTION__;
	//qDebug().noquote() << "\n" << __FUNCTION__ << QString("kind = '%1', value = '%2'").arg(t.getKind()).arg(t.getValue());

	// read and evaluate a Term
	double left = term(ts);
	// get the next token
	auto t = ts.getToken();
	// определ€ем вид лексемы
	while (true)
	{
		switch (t.getKind())
		{
		case '+':
			// evaluate Term and add
			left += term(ts);
			t = ts.getToken();
			break;

		case '-':
			// evaluate Term and subtract
			left -= term(ts);
			t = ts.getToken();
			break;

		default:
			// finally: no more + or -: return the answer
			ts.putback(t);
			return left;
		}

	}


	return 0.0;
}

double StrausCalc::term(TokenStream & ts)
{
	//qDebug().noquote() << "\n" << __FUNCTION__;
	//qDebug().noquote() << "\n" << __FUNCTION__ << QString("kind = '%1', value = '%2'").arg(t.getKind()).arg(t.getValue());

	double d = 0;
	// считыааем и вычисл€ем первичное выражение
	double left = extra(ts);
	// get the next token from token stream
	auto t = ts.getToken();
	// определ€ем вид лексемы

	while (true)
	{
		switch (t.getKind())
		{
		case '*':
			// вычисл€ем первичное выражение и умножаем
			left *= extra(ts);
			t = ts.getToken();
			break;

		case '/':
			// вычисл€ем первичное выражение и делим
			d = extra(ts);
			if (d == 0.0)
			{
				
				auto msg{ MESSAGE_ERROR_01.arg("Divide by zero") };
				throw runtime_error(msg.toStdString());
				return 0.0;
			}

			left /= d;
			t = ts.getToken();
			break;

		case '%':
			// вычисл€ем первичное выражение и остатка от целочисленного делени€
			d = extra(ts);
			if (d == 0.0)
			{
				auto msg{ MESSAGE_ERROR_01.arg("% Divide by zero") };
				throw runtime_error(msg.toStdString());
			}
			left = fmod(left, d);
			t = ts.getToken();
			break;

		default:
			// put t back into the token stream
			ts.putback(t);
			return left;
		}

	}


	return 0.0;
}

double StrausCalc::extra(TokenStream & ts)
{
	double left = primary(ts);
	Token t = ts.getToken();        // get the next token from token stream

	while (true) {
		switch (t.getKind()) {
		case '!':   //
		{
			if (left == 0)
			{
				left = 1;    // ‘акториал нул€ равен 1
				t = ts.getToken();
				break;
			}
			else
			{
				int d(1);
				for (int i = 1; i < left; ++i)
				{
					d *= i + 1;
				}
				left = d;
				t = ts.getToken();
				break;
			}
		}

		default:
			ts.putback(t);  // ѕомещает объект t обратно в поток лескем
			return left;
		}
	}
}

double StrausCalc::primary(TokenStream & ts)
{
	//qDebug().noquote() << "\n" << __FUNCTION__ << QString("kind = '%1', value = '%2'").arg(t.getKind()).arg(t.getValue());

	double d = 0.0;
	// получаем следующую лексему
	auto t = ts.getToken();
	// определ€ем вид лексемы

	switch (t.getKind())
	{
	case '(': // handle '(' expression ')'
		d = expression(ts);
		t = ts.getToken();
		if (t.getKind() != ')')
		{
			auto msg{ MESSAGE_ERROR_01.arg("')' expected") };
			throw runtime_error(msg.toStdString());
		}

		return d;

	case '{': // handle '{' expression '}'
		d = expression(ts);
		t = ts.getToken();
		if (t.getKind() != '}')
		{
			auto msg{ MESSAGE_ERROR_01.arg("'}' expected") };
			throw runtime_error(msg.toStdString());
		}

		return d;

	case '!':
		return t.getValue();

	case '-':
		return -primary(ts);

	case '+':
		return primary(ts);

	case NUMBER:
		// we use NUMBER('8') to represent a number
		return t.getValue(); // return the number's value

	case NAME:
		// we use NAME('a') to represent a variable value
		return getVariableValue(t.getVarName()); // return the value of variable

	case QUIT:
		ts.putback(t.getKind());
		return 0.0;


	default:
		throw runtime_error(MESSAGE_ERROR_01.arg("Primary expected").toStdString());
	}
	
}

void StrausCalc::calculate()
{
	while (cin)
	{
		try
		{
			cout << PROMPT;

			auto t = _tokenStream.getToken();

			while (t.getKind() == END_EXPR)
			{
				t = _tokenStream.getToken();
			}

			if (t.getKind() == QUIT)
			{
				return;
			}

			_tokenStream.putback(t);

			qDebug().noquote() << MESSAGE_RESULT_01.arg(statement(_tokenStream));

		}
		catch (exception& e)
		{
			cerr << e.what() << '\n';
			_tokenStream.ignore(END_EXPR);
		}
		

	}
}


int StrausCalc::calcRun()
{
	//qDebug().noquote() << "\n" << __FUNCTION__;
	//QVector<int> qvctr{0,2,3};
	//temporary(qvctr);
	//temporary(&qvctr);
	//vector<int> vctr{0,2,3};
	//temporary(vctr);

	try
	{
		defineVariable("pi", 3.141);
		defineVariable("e", 2.718);

		calculate();

		return 0;
	}
	catch (exception& e)
	{
		cerr << e.what() << endl;
		qDebug() << " - For close window, input symbol ~ \n"; // -For continue, input symbol C \n";
		char ch;
		for (char ch; cin >> ch;)
		{
			if (ch == '~')
			{
				return 1;
			}
			else if (ch == 'C' || ch == 'c')
			{
				calcRun();
			}
		}
		return 1;
	}
	catch (...)
	{
		cerr << "exception \n";
		keepWindowOpen("~2");
		return 2;
	}
}

double StrausCalc::getVariableValue(const QString &name, bool * result)
{
	if (result)
		*result = false;

	for (auto & item : _variableStorage)
	{
		if (item.getName() == name)
		{
			return item.getValue();
			if (result)
				*result = true;
		}
	}
	
	return 0.0;
}


void StrausCalc::setVariableValue(const QString & name, const double & value, bool * result)
{
	if (result)
		*result = false;

	for (auto & item : _variableStorage)
	{
		if (item.getName() == name)
		{
			return item.setValue(value);
			if (result)
				*result = true;
		}
	}
}

bool StrausCalc::isVariableDeclared(const QString & variableName)
{
	for (auto & item : _variableStorage)
	{
		if (item.getName() == variableName)
		{
			return true;
		}
	}
	
	return false;
}

void StrausCalc::defineVariable(const QString & variableName, const double & variableValue, QString * error)
{
	if (!isVariableDeclared(variableName))
	{
		_variableStorage.push_back(variable(variableName, variableValue));
	}
	else
	{
		if (error)
			*error = MESSAGE_ERROR_01.arg(QString("Variable '%1' already declared").arg(variableName));
	}
}

double StrausCalc::declaration(TokenStream & ts, QString * error)
{
	auto t1 = ts.getToken();

	if (t1.getKind() != NAME)
	{
		QString message{ MESSAGE_ERROR_01.arg("Variable name expected in declaration") };
		if (error)
			*error = message;

		throw runtime_error(message.toStdString());
	}

	QString varName = t1.getVarName();

	auto t2 = ts.getToken();
	if (t2.getKind() != '=')
	{
		QString message{ MESSAGE_ERROR_01.arg(QString("Expected symbol '=' in declaration of '%1'").arg(varName)) };
		if (error)
			*error = message;

		throw runtime_error(message.toStdString());
	}

	auto d = expression(ts);

	defineVariable(varName, d);
}


void StrausCalc::keepWindowOpen()
{
	cin.clear();
	qDebug().noquote() << "Please enter a character to exit\n";
	char ch;
	cin >> ch;
	return;
}

void StrausCalc::keepWindowOpen(string s)
{
	if (s == "") return;
	cin.clear();
	cin.ignore(120, '\n');
	for (;;) {
		qDebug().noquote() << QString("Please enter '%1' to exit\n").arg(QString::fromStdString(s));
		string ss;
		while (cin >> ss && ss != s)
			qDebug().noquote() << QString("Please enter '%1' to exit\n").arg(QString::fromStdString(s));
		return;
	}
}

//void StrausCalc::cleanUpMessage()
//{
//	_tokenStream.ignore(END_EXPR);
//}

void StrausCalc::temporary(const QVector<int>& v)
{
	auto sz = v.size();
	sz = sz;
}

void StrausCalc::temporary(const QVector<int>* v)
{
	auto sz = v->size();
	sz = sz;
}

void StrausCalc::temporary(const vector<int> & v)
{
	auto sz = v.size();
	sz = sz;
}

Token TokenStream::getToken()
{
	if (_full)
	{
		_full = false;
		return _buffer;
	}
	char ch;
	cin >> ch;

	switch (ch)
	{
	case END_EXPR: // for "print"
	case QUIT: // for "quit"
	case '=': case '!': case '(': case ')': case '{': case '}': case '+': case '-': case '*': case '/':
		return Token{ ch };   // let each character represent itself
	case '.':
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
	{
		// return the number to input flow
		cin.putback(ch);
		double val;
		// read the number
		cin >> val;
		return Token{ NUMBER, val };
	}
	default:
		if (isalpha(ch)) // Checks whether 'ch' is an alphabetic letter 
		{
			string s;
			s += ch;
			while (cin.get(ch) && (isalpha(ch) || isdigit(ch)))
			{
				s += ch;
			}

			cin.putback(ch);

			if (s == DECL_KEY)
			{
				return Token(LET);
			}

			return Token(NAME, QString::fromStdString(s));
		}
		
		QString message{ MESSAGE_ERROR_01.arg("Bad token") };
		throw runtime_error(message.toStdString());
	}
}

void TokenStream::putback(Token t)
{

	if (_full)
	{
		auto message{ MESSAGE_ERROR_01.arg("Putback() into a full buffer") };
		throw runtime_error(message.toStdString());
	}

	_buffer = t;         // copy t to buffer
	_full = true;        // buffer is now full
}

void TokenStream::ignore(const char & ch)
// value of 'ch' is a symbol represents the kind of Token
{
	// first check buffer
	if (_full && (ch == _buffer.getKind()))
	{
		_full = false;
		return;
	}
	_full = false;

	char buferInCin = 0;
	while (cin >> buferInCin)
	{
		if (buferInCin == ch)
		{
			return;
		}
	}
}

variable::variable(const QString & name, const double & value)
	: _name(name), _value(value)
{
}

QPair<QString, double> variable::getVariable()
{
	return qMakePair(_name, _value);
}

QString variable::getName()
{
	return _name;
}

double variable::getValue()
{
	return _value;
}

void variable::setValue(const double & value)
{
	_value = value;
}

