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
	A *a[5];
	int x;
	for (int id_x = 0; id_x < 5; id_x++)
	{
		cin >> x;
		if (x == 0) { a[id_x] = new A; }
		else { a[id_x] = new B; }
	}
	cout << endl;
	for (int id_y = 0; id_y < 5; id_y++) { (*a[id_y]).f(); }
	for (int id_z = 0; id_z < 5; id_z++) { delete a[id_z]; }

	system("pause");
	return 0;
}