# include <iostream>

using namespace std;

class figura {
public:
  virtual void rysuj ()=0;
  virtual float pole ()=0;
};


class punkt: public figura {
protected:
   int  x, y;
public:
    punkt (int i  =0 , int j = 0): x(i), y(j) {cout <<"konstruktor figura"<<endl;}
    void wsp() {cout << " x = " << x << " y = " << y << endl;}
    void rysuj(){cout << "rysuje punkt x = " << x << "   y = " << y << endl;};
    float pole (){cout << "licze pole punktu " << endl;} ;
};

class okrag: public punkt {
protected:
   int  r;
public:
   okrag(int i =0 , int j =0, int k = 1): punkt(i,j), r(k) {}
   void rysuj(){ cout <<" rysuje okrag "<<endl; wsp();}
   float pole () {cout << "licze pole okregu: " << 3.14*r*r << endl;}
;

class kwadrat : public punkt {
protected:
   int  bok1;
public:
   kwadrat (int i =0, int j=0, int k=0): punkt(i,j), bok1(k) { }
    void rysuj(){cout <<"rysuje kwadrat"<<endl; wsp();}
    float pole () {cout << "licze pole kwadratu: " << bok1*bok1 << endl;}
};


class pros : public kwadrat {
	protected:
   int  bok2;
public:
   pros(int i =0, int j=0, int k=0, int l=0): kwadrat (i,j,k), bok2(l) {cout <<"konstruktor kwadrat"<<endl; }
   void rysuj(){cout <<"rysuje prostokat"<<endl; wsp();}
   float pole () {cout << "licze pole prostokatu: " << bok1*bok2 << endl;}
};


class elipsa: public okrag {
	protected:
   	   int  r1;
    public:
      elipsa(int i =0 , int j =0, int k = 1, int l=2): okrag(i,j,k), r1(l) {}
      void rysuj(){ cout <<" rysuje elipsa "<<endl; wsp();}
      float pole () {cout << "licze pole elipsy: " << (r1*r)*3.14 << endl;}
};

punkt p1;
okrag o1 (4,5,3);
kwadrat k1(10,-10, 100);
pros pr1, pr2(55,66,3,7);
elipsa el1(1,1,2,4);
///////////
//void rysuj_f(punkt * wsk){ wsk -> rysuj();}

void rysuj_f(punkt & ref){ ref.rysuj();}
void pole_f(punkt & ref){ ref.pole();}

//////////////
main()
{

punkt * wsk;
cout << endl<< endl;



/*wsk = & p1;
wsk ->rysuj();
wsk = & k1;
wsk ->rysuj();
wsk ->pole();
wsk = & o1;
wsk ->rysuj();
wsk ->pole();
wsk = & el1;
wsk ->rysuj();
wsk ->pole();*/



  rysuj_f(p1);
  rysuj_f(k1);
  rysuj_f(pr1);
  rysuj_f(o1);
  rysuj_f(el1);

  cout << endl<< endl;

  pole_f(k1);
  pole_f(pr1);
  pole_f(o1);
  pole_f(el1);

   system("PAUSE");
//p1.rysuj();
//o1.rysuj();
//k1.rysuj();



}



