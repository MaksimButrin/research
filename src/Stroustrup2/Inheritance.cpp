#include "Inheritance.h"

#include <QSharedPointer>


namespace inh
{


void run()
{
	//virtFunc01();
	//virtFunc02();
	virtFunc04();
}



void virtFunc01()
{
	/*
		����������� ������� � ��� �������, ������� ������������ � ������� ������,
		� ����� ����������� ����� ����� �� ��������������.
		����������� ������� ���������� ������ ����� ��������� ��� ������ �� ������� �����.
	*/

	X x;
	X *px = &x;  // ��������� �� ������� �����
	Y y;
	x.seti(10);
	y.seti(15);

	px->print();  // ����� X: 10
	px = &y;
	px->print();  // ����� Y: 15
	cin.get();
}

void virtFunc02()
{
	{
		Child01 *child = new Child01(7);
		Parent01 * parent = child;
		delete parent;
	}
	
	qDebug().noquote() << SEPARATOR;

	{
		Child02 *child = new Child02(7);
		Parent02 * parent = child;
		delete parent;
	}

	qDebug().noquote() << SEPARATOR;

	{
		/*
			����� �� �����, ����� ������ ������ Parent �� ������ ������ Child �������� Parent::getName() ������ Child::getName(). ����� ��� �������, ����� ������ ������������ �������� ���������� ������� ���������
		*/
		Child03 child;
		Parent03 & parent = child;
		// �� ��������� ����� ������ Child::GetName()
		qDebug().noquote() << "parent.getName = " << parent.getName();
		// ����� Parent::GetName() ������ ��������������� Child::GetName()
		// !!! ������������ �����
		qDebug().noquote() << "parent.Parent03::getName = " << parent.Parent03::getName();
	}

}

void virtFunc04()
{
	B04 b;
	D04 d;
	DD04 dd;

	qDebug().noquote() << SEPARATOR_MINI << "call04(b)" << SEPARATOR_MINI;
	call04(b);

	qDebug().noquote() << SEPARATOR_MINI << "call04(d)" << SEPARATOR_MINI;
	call04(d);
	
	qDebug().noquote() << SEPARATOR_MINI << "call04(dd)" << SEPARATOR_MINI;
	call04(dd);
	
	qDebug().noquote() << SEPARATOR;

	qDebug().noquote() << SEPARATOR_MINI << "b.f(); b.g();" << SEPARATOR_MINI;
	b.f();
	b.g();	
	
	qDebug().noquote() << SEPARATOR_MINI << "d.f(); d.g();" << SEPARATOR_MINI;
	d.f();
	d.g();

	qDebug().noquote() << SEPARATOR_MINI << "dd.f(); dd.g();" << SEPARATOR_MINI;
	dd.f();
	dd.g();

	/* private ����������� (������ �� �������� �������), �.�. �� ����������� ����������� ����� ��� private */
	C04 c;
	c.f(); /* ��������� ����� */
	//c.g(); /* ��� ������� �.�. ��������� ����� ������ ����� ���� ���������� */

	E04 e;
	e.f(); /* ��������� ����� */
	e.g(); /* ������ ��������� ����� �.�. virtFunc04 �������� friend � E04 */

	qDebug().noquote() << SEPARATOR_MINI << "s.f(); s.Mom04::f();" << SEPARATOR_MINI;

	Son04 s;
	// ����� ������� ������ ����
	s.f();
	// ��� �������� ������ ������ ���� ����� ������ � ���������� � ��������
	s.Mom04::f(); /* !!! ������, ��������������� �� ��������  */
	Son0401 s1;
	//s1.f(); 
	/* ������ ����������, ������ ��� ����������� ����������� ����� ���������� ���������� � ������ ������ � �� ����� ����� ������ ������� ���������� 
	������: f() �� ����� �� ������� �����, �������� ����������� ��������� ����� ����������� ������ ��� ������������
	
	������ Mom04::f() �������� �� �� Son0401 �� �����, 
	� ������ Son0401::f() ����� �� Son0401 �� �� ��������
	*/

	/* ����� ���������� ����� �� ���������� ����������, �� ���� ��� ����� �������� */
	s.g(0.0); /* ���������� ����� Son04::g(int), ���� �� ������������ usin Mom04:g; 
			, ������ ���������� ���������� �����, ������ ��� ������ g() � ���� ��������� ������ ����,
			� ����� ���������� ���������� �� ���������� ���������� 
			usin Mom04:g; - ��� g ������ �����, ������ ������������ ���� ������ (���������� ������ ������ ����������), 
			� ����� Mom04 ������ ���� �� � ����� �� ���������� ��� � Son04 (���������� �� ���� ���� �� �������, ������ ������� ������ Son) */




	/* ??? �� ����� �� ������� !!! */

	// Calling: virtual B04::f()
	// Calling: not virtual B04::g()
	// =================== call04(d) ===================
	// Calling: override D04::f()
	// Calling: not virtual B04::g()
	// =================== call04(dd) ===================
	// Calling: override D04::f()
	// Calling: not virtual B04::g()
	// ===============================================
	// =================== b.f(); b.g(); ===================
	// Calling: virtual B04::f()
	// Calling: not virtual B04::g()
	// =================== d.f(); d.g(); ===================
	// Calling: override D04::f()
	// Calling: D04::g()
	// =================== dd.f(); dd.g(); ===================
	// Calling: DD04::f()
	// Calling: DD04::g()
}












}//namespace inh
