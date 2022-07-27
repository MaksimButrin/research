//#pragma once

#include <iostream>
#include <QDebug>
#include <QString>
#include "Consts.h"

using namespace cst;


namespace hw
{

void run();
void ch14Task01();

inline void printCall(const QString & msg)
{
	qDebug().noquote() << QString("Calling: %1").arg(msg);
}
/*
���������� ����� 81 � ����������� �������� vf() � �������������
�������� f() . ���������� ��� ������� � ������ 81 . ����������
������ ������� ���, ����� ��� �������� ���� ��� (��������,
"B1::vf()") . �������� ��� ������� ���������.
*/
class B1
{
public:
	B1() {};
	~B1() {};

	virtual void vf() { printCall("B1::vf()"); };
	/* �������� � ����� B1 ����� ����������� ������� pvf() � ����������� ��������� */
	/* ��� �������� � ������ ����������, ���� ���� ����� ���������� */
	//virtual void pvf() = 0 { printCall("B1::pvf()"); };
	void f() { printCall("B1::f()"); };
};

/* ���������� ����� D1 , ����������� �� ������ B1, � ���������� � ��� ������� vf() */
class D1: public B1
{
public:
	D1() {};
	~D1() {};

	void vf() override { printCall("D1::vf()"); };
};

/*
������ ���������� ������� f() � ������ D1(��� D11) � ��������� ��. 1-3. ���������
����������.
*/
class D11 : public B1
{
public:
	D11() {};
	~D11() {};

	void vf() override { printCall("D11::vf()"); };
	void f() { printCall("D11::f()"); };

};


/*
���������� ����� D2, ����������� �� ������ Dl , � ���������� � ���
������� pvf() . �������� ������ ������ D2 � �������� �� ���� �������
f() , vf() � pvf()
*/
class B11
{
public:
	B11() {};
	~B11() {};

	virtual void vf() { printCall("B11::vf()"); };
	virtual void pvf() = 0;
	void f() { printCall("B11::f()"); };
};

class D12 : public B11
{
public:
	D12() {};
	~D12() {};

	void vf() override { printCall("D12::vf()"); };
	virtual void pvf() = 0;
	void f() { printCall("D12::f()"); };

};

class D2 : public D12
{
public:
	D2() {};
	~D2() {};

	void pvf() override { printCall("D2::pvf()"); };

};

/*
���������� ����� B2 � ����� ����������� �������� pvf() . ����������
����� D21 � ������-������ ���� string � ��������-������, �������������
������� pvf() ; ������� D21::pvf() ������ ��������
�������� ����������� ���� ����� ���� string. ���������� ����� D22,
����������� ������ D21, �� ����������� ����, ��� ��� ���� ����� ���
int. ���������� ������� f() , ���������� �������� ���� B2& � ����������
������� pvf() ��� ����� ���������. �������� �������
f() � ����������� D21 � D22.

*/
class B2
{
public:
	B2() {};
	~B2() {};

	virtual void pvf() = 0; /* ����� ����������� �-�� (pure virtual function) */
};

class D21 : public B2
{
public:
	D21() {};
	~D21() {};

	void pvf() override { printCall(QString("D21::pvf() - %1").arg(QString::fromStdString(_s))); };
	std::string _s{ "string" };
};

class D22 : public B2
{
public:
	D22() {};
	~D22() {};

	void pvf() override { printCall(QString("D22::pvf() - %1").arg(QString::number(_s))); };
	int _s{ 5 };
};

inline void callB2(B2 & b)
{
	b.pvf();
}


















}//namespace hw