#include <iostream>
using namespace std;

class A{
public:
	virtual void f(){ cout << "A\n"; }
};

class B : public A{
public:
	virtual void f(){ cout << "B\n"; }
};

int main(void)
{
	A *a;
	int x;
	cin >> x;
	if (x == 0) { a = new A; }
	else { a = new B; }
	(*a).f();
	delete a;
	
	system("pause");
	return 0;
}