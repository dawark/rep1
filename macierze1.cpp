#include<iostream>
#include<cmath>

using namespace std;

class macierz
{  int wiersz,kolumna;
   float *wsk;
   public:
       macierz(int w,int k)                         //konstruktor macierzy w_na_k
          {  wiersz=w;
             kolumna=k;
             wsk=new float[wiersz*kolumna];
             for(int i=0;i<wiersz*kolumna;i++)      //wpisuje 0 do macierzy
             wsk[i]=0;
          }
       
       macierz(const macierz &a){                   //konstruktor kopiujacy
          wiersz=a.wiersz;
          kolumna=a.kolumna;
          for(int i=0;i<wiersz*kolumna;i++)
          wsk[i]=a.wsk[i];           
          }
       
       ~macierz(){                                  //destruktor macierzy
       delete wsk;           
       };   
          
   friend ostream& operator<<(ostream &wypisz, const macierz &a);        //funkcja wypisywania strumieniowego
   friend istream& operator>>(istream &wpisz, macierz &b);               //funkcja wpisywania strumieniowego
   friend macierz operator+(const macierz &a, const macierz &b);         //operator dodaj¹cy dwuargumentowy
   macierz& operator+(const macierz &a);                                 //operator dodajacy jednoargumentowy
   friend macierz operator-(const macierz &a, const macierz &b);         //operator odejmuj¹cy dwuargumentowy
   macierz& operator-(const macierz &a);                                 //operator odejmuj¹cy jednoargumentowy
   macierz& operator=(const macierz&a);                                  //operator przypisania - 
   friend float operator~(const macierz &a);                              //operator liczacy wyznacznik macierzy
   friend macierz trans(const macierz &a);                               //operator transponujacy macierz - funkcja
   friend macierz operator*(const macierz &a, const macierz &b);         //operator mno¿enia dwoch macierzy dwuargumentowy
   friend macierz operator*(const macierz &a, float b);                  //operator mno¿enia macierzy przez skalar dwuargumentowy
   macierz operator*(const macierz &a);                                 //operator mno¿enia dwoch macierzy jednoargumentowy 
   macierz& operator*(const float a);                                    //operator mno¿enia macierzy przez skalar jednoargumentowy   
   friend macierz dopelnienia(const macierz &a);                         //funkcja liczaca dopelnienia algebraiczne macierzy
   friend macierz odwroc(const macierz &a);                              //funkca odwracajaca macierz korzysta z[friend dopelnienia,friend trans, friend~,friend*(float)]
   
   private:
   friend float wyznacznik_2_na_2(const macierz &a);         //liczy wyznacznik 2na2 
   
};
///////////////////////////////////////////////////////
macierz dopelnienia(const macierz &a){
macierz dop(a.wiersz,a.kolumna);
macierz tmp((a.wiersz-1),(a.kolumna-1));        
int nr_wiersza_mac, nr_kolumny_mac,nr_wiersza_dop,nr_kolumny_dop;       
   
   for(int i=0;i<a.wiersz;i++){                                                 //zmieniam wybrany wiersz
      for(int j=0;j<a.wiersz;j++){                                              //zmieniam wybrana kolumne
         
         if((i<(a.wiersz-1))&&(j<(a.kolumna-1))){                                                                      //liczenie dopelnien dla wierszy i kolumn nie bed¹cych ostatnimi w maciezy
           for(nr_wiersza_mac=0,nr_wiersza_dop=0;nr_wiersza_mac<a.wiersz;nr_wiersza_mac++,nr_wiersza_dop++){  
             if(i==nr_wiersza_mac){nr_wiersza_mac++;}                                                                            
             for(nr_kolumny_mac=0,nr_kolumny_dop=0;nr_kolumny_mac<a.kolumna;nr_kolumny_mac++,nr_kolumny_dop++){                      
               if(j==nr_kolumny_mac){nr_kolumny_mac++;}
               tmp.wsk[(nr_wiersza_dop*tmp.kolumna)+nr_kolumny_dop]=a.wsk[(nr_wiersza_mac*a.kolumna)+nr_kolumny_mac];           
             }
           }
         }
         
          if((i==(a.wiersz-1))&&(j<(a.kolumna-1))){                                                                             //liczenie dopelnien dla ostatniego wiersza
            for(nr_wiersza_mac=0;nr_wiersza_mac<(a.wiersz-1);nr_wiersza_mac++){
              for(nr_kolumny_mac=0,nr_kolumny_dop=0;nr_kolumny_mac<a.kolumna;nr_kolumny_mac++,nr_kolumny_dop++){
              if(j==nr_kolumny_mac){nr_kolumny_mac++;}
              tmp.wsk[(nr_wiersza_mac*tmp.kolumna)+nr_kolumny_dop]=a.wsk[(nr_wiersza_mac*a.kolumna)+nr_kolumny_mac];
              }                                                                  
            }
          }                                        
          
          if((i<(a.wiersz-1))&&(j==(a.kolumna-1))){                                                                             //liczenie dopelnien dla ostatniej kolumny
            for(nr_wiersza_mac=0,nr_wiersza_dop=0;nr_wiersza_mac<a.wiersz;nr_wiersza_mac++,nr_wiersza_dop++){
              if(i==nr_wiersza_mac){nr_wiersza_mac++;}
              for(nr_kolumny_mac=0;nr_kolumny_mac<(a.kolumna-1);nr_kolumny_mac++){              
              tmp.wsk[(nr_wiersza_dop*tmp.kolumna)+nr_kolumny_mac]=a.wsk[(nr_wiersza_mac*a.kolumna)+nr_kolumny_mac];
              }                                                                  
            }
          }                                         
          
          if((i==(a.wiersz-1))&&(j==(a.kolumna-1))){                                                                            //liczenie dopelnien dla ostatniego elementu macierzy
            for(nr_wiersza_mac=0;nr_wiersza_mac<(a.wiersz-1);nr_wiersza_mac++){
               for(nr_kolumny_mac=0;nr_kolumny_mac<(a.kolumna-1);nr_kolumny_mac++){
               tmp.wsk[(nr_wiersza_mac*tmp.kolumna)+nr_kolumny_mac]=a.wsk[(nr_wiersza_mac*a.kolumna)+nr_kolumny_mac];
               }            
            }
          }        
         dop.wsk[(i*dop.kolumna)+j]=~tmp;                                                                            //liczy wyznacznik macierzy tmp powstalej(po skresleniu jednej kolumny i jednego wiersza)
      }                                                                                                                //i wpisuje go do macierzy dopelnien
   } 
   return dop;              
};
/////////////////////////////////////////////////
macierz odwroc(const macierz &a){
macierz dop(a.wiersz,a.kolumna);
macierz tmp((a.wiersz-1),(a.kolumna-1));        
macierz t(a.kolumna,a.wiersz);
int nr_wiersza_mac, nr_kolumny_mac,nr_wiersza_dop,nr_kolumny_dop;
float wyz;

wyz=~a;
if(wyz!=0){
       
   
   for(int i=0;i<a.wiersz;i++){                                                 //zmieniam wybrany wiersz
      for(int j=0;j<a.wiersz;j++){                                              //zmieniam wybrana kolumne
         
         if((i<(a.wiersz-1))&&(j<(a.kolumna-1))){                                                                      //liczenie dopelnien dla wierszy i kolumn nie bed¹cych ostatnimi w maciezy
           for(nr_wiersza_mac=0,nr_wiersza_dop=0;nr_wiersza_mac<a.wiersz;nr_wiersza_mac++,nr_wiersza_dop++){  
             if(i==nr_wiersza_mac){nr_wiersza_mac++;}                                                                            
             for(nr_kolumny_mac=0,nr_kolumny_dop=0;nr_kolumny_mac<a.kolumna;nr_kolumny_mac++,nr_kolumny_dop++){                      
               if(j==nr_kolumny_mac){nr_kolumny_mac++;}
               tmp.wsk[(nr_wiersza_dop*tmp.kolumna)+nr_kolumny_dop]=a.wsk[(nr_wiersza_mac*a.kolumna)+nr_kolumny_mac];           
             }
           }
         }
         
          if((i==(a.wiersz-1))&&(j<(a.kolumna-1))){                                                                             //liczenie dopelnien dla ostatniego wiersza
            for(nr_wiersza_mac=0;nr_wiersza_mac<(a.wiersz-1);nr_wiersza_mac++){
              for(nr_kolumny_mac=0,nr_kolumny_dop=0;nr_kolumny_mac<a.kolumna;nr_kolumny_mac++,nr_kolumny_dop++){
              if(j==nr_kolumny_mac){nr_kolumny_mac++;}
              tmp.wsk[(nr_wiersza_mac*tmp.kolumna)+nr_kolumny_dop]=a.wsk[(nr_wiersza_mac*a.kolumna)+nr_kolumny_mac];
              }                                                                  
            }
          }                                        
          
          if((i<(a.wiersz-1))&&(j==(a.kolumna-1))){                                                                             //liczenie dopelnien dla ostatniej kolumny
            for(nr_wiersza_mac=0,nr_wiersza_dop=0;nr_wiersza_mac<a.wiersz;nr_wiersza_mac++,nr_wiersza_dop++){
              if(i==nr_wiersza_mac){nr_wiersza_mac++;}
              for(nr_kolumny_mac=0;nr_kolumny_mac<(a.kolumna-1);nr_kolumny_mac++){              
              tmp.wsk[(nr_wiersza_dop*tmp.kolumna)+nr_kolumny_mac]=a.wsk[(nr_wiersza_mac*a.kolumna)+nr_kolumny_mac];
              }                                                                  
            }
          }                                         
          
          if((i==(a.wiersz-1))&&(j==(a.kolumna-1))){                                                                            //liczenie dopelnien dla ostatniego elementu macierzy
            for(nr_wiersza_mac=0;nr_wiersza_mac<(a.wiersz-1);nr_wiersza_mac++){
               for(nr_kolumny_mac=0;nr_kolumny_mac<(a.kolumna-1);nr_kolumny_mac++){
               tmp.wsk[(nr_wiersza_mac*tmp.kolumna)+nr_kolumny_mac]=a.wsk[(nr_wiersza_mac*a.kolumna)+nr_kolumny_mac];
               }            
            }
          }        
         dop.wsk[(i*dop.kolumna)+j]=~tmp;                                                                            //liczy wyznacznik macierzy tmp powstalej(po skresleniu jednej kolumny i jednego wiersza)
      }                                                                                                                //i wpisuje go do macierzy dopelnien
   } 
   for(int i=0;i<dop.wiersz*dop.kolumna;i++){
   if(i%2==1){dop.wsk[i]*=(-1);}             
   }
   for(int i=0;i<dop.wiersz;i++){
      for(int j=0;j<dop.kolumna;j++){
         t.wsk[(i*t.kolumna)+j]=dop.wsk[(j*dop.kolumna)+i];        
      }
   }
                                                                                                     //transponuje macierz dopelnien;
   t*(1/wyz);                                                                                                        //mnozy macierz dopelnien przez 1/wyznacznik macierzy a
   return t;
   }
else{
     cout<<"Macierz odwrotna nie istnieje"<<endl;
     macierz b(1,1);
     b.wsk[0]=0;
     return b;
     }
}

//////////////////////////////////////////////////
macierz& macierz::operator*(float b){
for(int i=0;i<wiersz*kolumna;i++)
  {wsk[i]=wsk[i]*b;}
return *this;
};



//////////////////////////////////////////////////
macierz operator*(const macierz &a, float b){
macierz c(a.wiersz,a.kolumna);
for(int i=0;i<a.wiersz*a.kolumna;i++)
  {c.wsk[i]=a.wsk[i]*b;}

return c;
};

////////////////////////////////////////////////
macierz macierz::operator*(const macierz &a){
  macierz c(wiersz,a.kolumna);
  int i,j,k,l;
  
  if(kolumna==a.wiersz){
     for(i=0;i<wiersz;i++){
        for(j=0;j<a.kolumna;j++){
           l=(j*a.kolumna);
           for(int pom=0,k=(i*kolumna),l=j;k<((i*kolumna)+kolumna);k++,pom++,l=((pom*a.kolumna)+j)){
             
             //cout<<wsk[k]<<" "<<a.wsk[l]<<endl;
             c.wsk[(i*c.kolumna)+j]+=(wsk[k]*a.wsk[l]);                          
             //cout<<c.wsk[(i*c.kolumna)+j]<<endl;
           }
           cout<<endl;   
        }
     }          
     return c;                                
  }
  else{
    cout<<"Mno¿enie niemozliwe do wykonania"<<endl;
    macierz d(1,1);
    d.wsk[0]=0;
    return d;
    }         
}

///////////////////////////////////////////////////////
macierz operator*(const macierz &a, const macierz &b){
  macierz c(a.wiersz,b.kolumna);
  int i,j,k,l;
  
  if(a.kolumna==b.wiersz){
     for(i=0;i<a.wiersz;i++){
        for(j=0;j<b.kolumna;j++){
           l=(j*b.kolumna);
           for(int pom=0,k=(i*a.kolumna),l=j;k<((i*a.kolumna)+a.kolumna);k++,pom++,l=((pom*b.kolumna)+j)){
             
             //cout<<a.wsk[k]<<" "<<b.wsk[l]<<endl;
             c.wsk[(i*c.kolumna)+j]+=(a.wsk[k]*b.wsk[l]);                          
             //cout<<c.wsk[(i*c.kolumna)+j]<<endl;
           }
           cout<<endl;   
        }
     }          
     return c;                                
  }
  else{
    cout<<"Mno¿enie niemozliwe do wykonania"<<endl;
    macierz d(1,1);
    d.wsk[0]=0;
    return d;
    }        
};




///////////////////////////////////////////////////////////////////////////////////

macierz trans(const macierz &a){                             ///transponuje macierz, odwraca wiersz z kolumnami
       macierz a2(a.kolumna,a.wiersz);     
       int i,j;
          for(i=0;i<a2.wiersz;i++){
               for(j=0;j<a2.kolumna;j++){

                   a2.wsk[(i*a2.kolumna)+j]=a.wsk[(j*a.kolumna)+i];
                   //a2.wiersz=a.kolumna;
                   //a2.kolumna=a.wiersz;
                   
                   
               }
          }
       return a2;     
       };


////////////////////////////////////////////////////////            rekurencyjne obliczanie wyznacznika, w funkcji odwolanie do tej samej funkcji
float operator~(const macierz &a){

        float det=0;
        int nr_wiersza, nr_kolumny;
        int nr_kolumny_dop, nr_kolumny_mac;
        macierz dopelnienie(a.wiersz-1,a.kolumna-1);

        if((a.wiersz==1)&&(a.kolumna==1))                             //liczy wyznacznik macierzy 1na1
          return a.wsk[0];
          
        else if((a.wiersz==2)&&(a.kolumna==2))               ///liczy wyznacznik macierzy 2na2
          return(wyznacznik_2_na_2(a));
          
        else                                                 //liczy wyznacznik wiekszej macierzy niz 2na2
          {
            for (nr_kolumny = 0; nr_kolumny < a.kolumna; nr_kolumny++)
            {
              for (nr_kolumny_dop = 0, nr_kolumny_mac = 0; nr_kolumny_dop < a.kolumna-1; nr_kolumny_dop++, nr_kolumny_mac++)
              {                                   
                  nr_kolumny_mac += (nr_kolumny_mac == nr_kolumny ? 1 : 0);
                  for (nr_wiersza = 0; nr_wiersza < a.wiersz-1; nr_wiersza++)
                    dopelnienie.wsk[(nr_wiersza*dopelnienie.kolumna)+nr_kolumny_dop] = a.wsk[((nr_wiersza+1)*a.kolumna)+nr_kolumny_mac];            
              }
              det += (a.wsk[nr_kolumny] * ((nr_kolumny%2)==0 ? 1 : (-1)) * (~(dopelnienie)));   
              //cout<<dopelnienie;
            }            
          }        
          return det;
                             
        };


//////////////////////////////////////////////////////
   float wyznacznik_2_na_2(const macierz &a){                              //funkcja liczy wyznacznik macierzy 2na2
         float wyznacznik;
         wyznacznik=(a.wsk[0]*a.wsk[3])-(a.wsk[1]*a.wsk[2]);
         return wyznacznik;
         }

/////////////////////////////////////////////////
   macierz& macierz::operator=(const macierz& a){
   
   wiersz=a.wiersz;
   kolumna=a.kolumna;
   float *tmp= new float(wiersz*kolumna);   //poradzi sobie z pseudo-przypisaniem :)))) yeah! to byl duzy problem
   for(int i=0;i<wiersz*kolumna;i++)
       tmp[i]=a.wsk[i];

   for(int i=0;i<wiersz*kolumna;i++)
   wsk[i]=tmp[i]; 
   
   /*
     delete wsk;                               //wczesniej najpierw usuwal a potem tworzyl, teraz tworzy kopie elementu wsk, usuwa wsk, a potem do wsk przypisuje kopie i zwraca this;
     wiersz=a.wiersz;
     kolumna=a.kolumna;
     wsk=new float[wiersz*kolumna]; 
     for(int i=0;i<a.wiersz*a.kolumna;i++){
       wsk[i]=a.wsk[i];
     };   
    */ 
   return *this;
   
   };
////////////////////////////////////////////////////////            DODAWANIE Z JEDNYM ARGUMENTEM
   macierz& macierz::operator+(const macierz& a){
            if((wiersz==a.wiersz)&&(kolumna==a.kolumna)){
              for(int i=0;i<a.wiersz*a.kolumna;i++){
                wsk[i]+a.wsk[i];
              };
            }
            else{
              cout<<"MACIERZE O ROZNYCH WYMIARACH!"<<endl;
            };
            
            return *this;
            }   
/////////////////////////////////////////////////////////           ODEJMOWANIE Z JEDNYM ARGUMENTEM
   macierz& macierz::operator-(const macierz& a){
            if((wiersz==a.wiersz)&&(kolumna==a.kolumna)){
              for(int i=0;i<a.wiersz*a.kolumna;i++){
                wsk[i]-a.wsk[i];
              };
            }
            else{
              cout<<"MACIERZE O ROZNYCH WYMIARACH!"<<endl;
            };
            
            return *this;
            }

////////////////////////////////////////////////////////
macierz operator-(const macierz &a, const macierz &b){
  macierz c(a.wiersz,a.kolumna);
  if((a.wiersz==b.wiersz)&&(a.kolumna==b.kolumna)){
    for(int i=0;i<a.wiersz*a.kolumna;i++){
    c.wsk[i]=a.wsk[i]-b.wsk[i];
    };
  }
  else{
    cout<<"MACIERZE O ROZNYCH WYMIARACH!"<<endl;
  };
     return c;
};
///////////////////////////////////////////////
macierz operator+(const macierz &a, const macierz &b){
  macierz c(a.wiersz,a.kolumna);
  if((a.wiersz==b.wiersz)&&(a.kolumna==b.kolumna)){
    for(int i=0;i<a.wiersz*a.kolumna;i++){
    c.wsk[i]=a.wsk[i]+b.wsk[i];
    };
  }
  else{
    cout<<"MACIERZE O ROZNYCH WYMIARACH!"<<endl;
  };
     return c;
};
///////////////////////////////////////////////
ostream& operator<<(ostream &wypisz, const macierz &a)
{wypisz <<" Macierz o wymiarach "<<a.wiersz <<" X "<< a.kolumna<<endl;
for(int i=0;i<a.wiersz;i++)
  for(int j=0;j<a.kolumna;j++)
    { wypisz << " [" << i+1 << " , " << j+1 << "] = " ;
      wypisz << a.wsk[(i*a.kolumna)+j] << endl;}
return wypisz;
}
////////////////////////////////
istream& operator>>(istream &wpisz, macierz &b)
{for(int i=0;i<b.wiersz;i++)
  for(int j=0;j<b.kolumna;j++)
    { cout << " Podaj element tablicy: ";
      cout << " [" << i+1 << " , " << j+1 << "] = " ;
      wpisz >> b.wsk[(i*b.kolumna)+j] ;
     }
}
  
//////////////////////////////////

macierz A(3,3);
macierz B(3,3);
macierz C(2,6);

int main()
{
cin>>A;    
B=odwroc(A);
cout<<B;	
system("PAUSE");
}
