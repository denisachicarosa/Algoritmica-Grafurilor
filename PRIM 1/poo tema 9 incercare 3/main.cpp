#include <iostream>
#include<typeinfo>
using namespace std;

class Complex                                                                   ///Clasa complex
{
protected:

    float Re,Im;                                                                ///Campurile specifice
public:
    Complex();                                                                  ///Constructor fara parametru
    Complex(float, float);                                                      ///Constructor cu 2 parametri
    Complex(Complex&);                                                          ///Constructor de copiere
    ~Complex();                                                                 ///Destructor
    bool operator!=(Complex&);                                                  ///Supraincarcarea operatorului !=
    bool operator==(Complex&);                                                  ///Supraincarcarea operatorului ==
    Complex operator=(const Complex&);                                          ///Supraincarcarea operatorului =
    Complex operator+(Complex&);                                                ///Supraincarcarea operatorului +
    Complex operator-(Complex&);                                                ///Supraincarcarea operatorului -
    Complex operator*(Complex&);                                                ///Supraincarcarea operatorului*
    Complex operator/(Complex&);                                                ///Supraincarcarea operatorului /
    friend istream& operator>>(istream&,Complex&);                              ///Supraincarcarea operatorului >>
    friend ostream& operator<<(ostream&,Complex&);                              ///Supraincarcarea operatorului <<
};

class Matrice                                                                   ///Clasa de baza Matrice
{
protected:
    Complex** v;                                                                ///Campul matricei
    static int n;                                                               ///Camp cu variabila statica n care va retine numarul de obiecte
public:
    Matrice();                                                                  ///Constructor neparametrizat
    ~Matrice();                                                                 ///Destructor
    Matrice(int l, int c);                                                      ///Constructor cu 2 parametri
    friend istream& operator>>(istream&, Matrice&);                             ///Supraincarcarea operatorului >>
    friend ostream& operator<<(ostream&, Matrice&);                             ///Supraincarcarea operatprului <<
    void operator=(Matrice&);                                                   ///Supraincarcarea operatorului =
    virtual Complex determinant(){Complex z(0,0); return z;};                   ///Functie virtuala pentru calcularea determiantului
    static void citeste_n(){cin>>n;};                                           ///Functie statica pentru citirea numarului de obiecte
    int get_n(){return n;};                                                     ///Getter pentru n
    virtual bool triunghiulara_superior(){};
    virtual bool triunghiulara_inferior(){}
    virtual bool triunghiulara(){}
    virtual void diagonala(){}
};

int Matrice::n=0;

class Matrice_oarecare:public Matrice                                           ///Clasa Matrice oarecare care mosteneste public clasa Matrice
{
    int linii, coloane;                                                         ///Numarul de linii si numarul de coloane pentru matrice
public:
    bool triunghiulara_superior();                                              ///Functie care verifica daca matricea e triunghiulara superior
    bool triunghiulara_inferior();                                              ///Functie care verifica daca matricea e triunghiulara inferior
    bool triunghiulara();                                                       ///Functie care verifica daca matricea e triunghiulara
    void diagonala();                                                           ///Functie care verifica daca matricea e diagonala
    Matrice_oarecare(Matrice_oarecare&);                                        ///Constructor de copiere
    ~Matrice_oarecare();                                                        ///Destructor
    friend istream& operator>>(istream&, Matrice_oarecare&);                    ///Supraincarcarea operatorului >>
    friend ostream& operator<<(ostream&, Matrice_oarecare&);                    ///Supraincarcarea operatorului <<
    Matrice_oarecare(int l=0,int c=0):Matrice(l,c){linii=l; coloane=c;};        ///Constructor de initializare cu 2 parametri

};

class Matrice_patratica:public Matrice                                          ///Clasa Matrice patratica ce mosteneste public clasa Matrice
{
    int dim;                                                                    ///Campul pentru dimensiune
public:
    Matrice_patratica(int d=0):Matrice(d,d){dim=d;};                            ///Costructor de initializare cu 2 parametri
    bool triunghiulara_superior ();                                             ///Functie care verifica daca matricea e triunghiulara superior
    bool triunghiulara_inferior();                                              ///Functie care verifica daca matricea e triunghiulara inferior
    bool triunghiulara();                                                       ///Functie care verifica daca matricea e triunghiulara
    Complex determinant();                                                      ///Functie de calculare a determinantului
    void diagonala();                                                           ///Functie care verifica daca matricea e diagonala
    Matrice_patratica(Matrice_patratica&);                                      ///Constructor de copiere
    ~Matrice_patratica();                                                       ///Destructor
    friend istream& operator>>(istream&, Matrice_patratica&);                   ///Supraincarcarea operatorului >>
    friend ostream& operator<<(ostream&, Matrice_patratica&);                   ///Supraincarcarea operatorului <<
};

///METODE PENTRU CLASA MATRICE_PATRATICA
Complex Matrice_patratica::determinant()
{
    Complex det(1,0);
    Complex x;
    for(int i=0;i<dim;i++)
        for(int j=i+1;j<dim;j++)
    {
        x=v[i][j]/v[i][i];
        for(int k=i;k<dim;k++)
          { Complex y;
          y=v[k][i]*x;
            v[k][j]=v[k][j]-y;
          }
    }

    for(int i=0;i<dim;i++)
    {
        det=det*v[i][i];
        cout<<det;
        cout<<endl;
    }

    return det;

}
Matrice_patratica::Matrice_patratica(Matrice_patratica& m)
{
    dim=m.dim;
    v=new Complex* [dim];
    for(int i=0;i<dim;i++) v[i]=new Complex [dim];
    for(int i=0;i<dim;i++)
        for(int j=0;j<dim;j++) v[i][j]=m.v[i][j];

}
ostream& operator<<(ostream& out, Matrice_patratica& m)
{
    for(int i=0;i<m.dim;i++)
    {
        for(int j=0;j<m.dim;j++) out<<m.v[i][j]<<" ";
        out<<endl;
    }
    return out;
}

istream& operator>>(istream& in, Matrice_patratica& m)
{
    for(int i=0;i<m.dim;i++) delete[] m.v[i];
    delete[] m.v;
    cout<<"Dimensiunea este ";
    in>>m.dim;
    cout<<"Matricea este \n";
    m.v=new Complex* [m.dim];
    for(int i=0;i<m.dim;i++) m.v[i]=new Complex [m.dim];
    for(int i=0;i<m.dim;i++)
        for(int j=0;j<m.dim;j++) in>>m.v[i][j];
    return in;
}

Matrice_patratica::~Matrice_patratica()
{
    for(int i=0;i<dim;i++) delete[] v[i];
    delete[] v;
}
bool Matrice_patratica::triunghiulara_inferior()
{
    int ok=0;
    Complex z(0,0);
    for(int i=0;i<dim;i++)
        for(int j=0;j<dim;j++)
            if(i<j&&v[i][j]!=z) ok++;
        if(ok==0) return true;
        else return false;
}

bool Matrice_patratica::triunghiulara_superior()
{
    Complex z(0,0);
    int ok=0;
    for(int i=0;i<dim;i++)
        for(int j=0;j<dim;j++)
            if(i>j&&v[i][j]!=z ) ok++;
        if(ok==0) return true;
        else return false;
}
bool Matrice_patratica::triunghiulara()
{
    if(triunghiulara_inferior()&&triunghiulara_superior()) return true;
    return false;
}
void Matrice_patratica::diagonala()
{
    int x=0;
    if(!triunghiulara()) cout<<"Nu este triunghiulara, deci nici diagonala";
    else {
            Complex z(0,0);
            for(int i=0;i<dim;i++) if(v[i][i]!=z) x++;
            if(x==0) cout<<"Este diagonala";
            else cout<<"Nu este diagonala";
            }
}



///METODE PENTRU CLASA MATRICE_OARECARE
Matrice_oarecare::Matrice_oarecare(Matrice_oarecare& m)
{
    linii=m.linii;
    coloane=m.coloane;
    v=new Complex* [linii];
    for(int i=0;i<linii;i++) v[i]=new Complex [coloane];
    for(int i=0;i<linii;i++)
    for(int j=0;j<coloane;j++) v[i][j]=m.v[i][j];

}
ostream& operator<<(ostream& out, Matrice_oarecare& m)
{
    out<<"Matricea este:\n";
    for(int i=0;i<m.linii;i++)
    {
        for(int j=0;j<m.coloane;j++)
            out<<m.v[i][j]<<" ";
        out<<endl;
    }
    return out;
}
istream& operator>>(istream& in, Matrice_oarecare& m)
{
    for(int i=0;i<m.linii;i++) delete[] m.v[i];
    delete[] m.v;
    cout<<"\nNumarul de linii este ";
    in>>m.linii;
    m.v=new Complex* [m.linii];
    cout<<"\nNumarul de coloane este ";
    in>>m.coloane;
    for(int i=0;i<m.linii;i++) m.v[i]=new Complex [m.coloane];
    cout<<"\nMatricea este: \n";
    for(int i=0;i<m.linii;i++)
        for(int j=0;j<m.coloane;j++) in>>m.v[i][j];
    return in;
}

bool Matrice_oarecare::triunghiulara_inferior()
{
    int ok=0;
    Complex z(0,0);
    if(linii!=coloane) return false;
    for(int i=0;i<linii;i++)
        for(int j=0;j<coloane;j++)
            if(i<j&&v[i][j]!=z) ok++;
        if(ok==0) return true;
        else return false;
}

bool Matrice_oarecare::triunghiulara_superior()
{
    Complex z(0,0);
    int ok=0;
    if(linii!=coloane) return false;
    for(int i=0;i<linii;i++)
        for(int j=0;j<coloane;j++)
            if(i>j&&v[i][j]!=z) ok++;
        if(ok==0) return true;
        else return false;
}

bool Matrice_oarecare::triunghiulara()
{
    if(triunghiulara_inferior()&&triunghiulara_superior()) return true;
    return false;
}
void Matrice_oarecare::diagonala()
{
    int x=0;
    if(!triunghiulara()) cout<<"Nu este triunghiulara, deci nici diagonala";
    else {
            Complex z(0,0);
            for(int i=0;i<linii;i++) if(v[i][i] !=z) x++;
            if(x!=0) cout<<"Este diagonala";
            else cout<<"Nu este diagonala";
            }
}

Matrice_oarecare::~Matrice_oarecare(){for(int i=0;i<linii;i++) delete[] v[i]; delete[] v;}

///METODE PENTRU CLASA MATRICE
void Matrice:: operator=(Matrice& m) {}
ostream& operator<<(ostream& out,Matrice&) {return out;}
istream& operator>>(istream& in, Matrice& m){ return in;}
Matrice::Matrice(int l, int c)
{
    n++;
    v=new Complex* [l];
    for(int i=0;i<l;i++) v[i]=new Complex [c];
}
Matrice::~Matrice(){delete v;}
Matrice::Matrice(){v=NULL; n++;}

///METODE PENTRU CLASA COMPLEX
Complex Complex::operator/(Complex&a)
{Complex z(0,0); if(a==z) return z;
Complex imp(0,0); imp.Re=((Re*a.Re)+(Im*a.Im))/(a.Re*a.Re+a.Im*a.Im); imp.Im=(a.Re*Im-Re*a.Im)/(a.Re*a.Re+a.Im*a.Im); return imp; }
Complex Complex::operator*(Complex&a){Complex inm(0,0); inm.Re=Re*a.Re-Im*a.Im; inm.Im=Re*a.Im+Im*a.Re; return inm; }
Complex Complex::operator-(Complex&a){Complex dif(0,0); dif.Re=Re-a.Re; dif.Im=Im-a.Im; return dif; }
Complex Complex::operator+(Complex& a){Complex sum(0,0); sum.Re=Re+a.Re; sum.Im=Im+a.Im; return sum; }
bool Complex::operator==(Complex& a) {if(Im==a.Im&&Re==a.Re) return true; return false;}
bool Complex::operator!=(Complex& a) {if(Im!=a.Im||Re!=a.Re) return true; return false;}
ostream& operator<<(ostream& out,Complex& a){out<<a.Re; out<<"+"; out<<a.Im; out<<"*i"; return out;}
istream& operator>>(istream& in, Complex& a){cout<<"Re= ";in>>a.Re;cout<<"Im= "; in>>a.Im; return in;}
Complex Complex::operator=(const Complex& a){Im=a.Im; Re=a.Re; return *this;}
Complex::Complex(Complex& a){Im=a.Im; Re=a.Re;}
Complex::Complex(float r, float i){Im=i; Re=r;}
Complex::Complex(){Im=Re=0;}
Complex::~Complex(){Im=Re=0;}

void patratica()
{
    int comanda;
    cout<<"Pentru citire si afisare tastati 1\n";
    cout<<"Pentru a verifica daca o matrice este diagonala tastati 2\n";
    cout<<"Pentru a calcula determinantul unei matrice tastati 3\n";
    cout<<"Pentru citirea,memorarea si afisarea a n obiecte tastati 4\n";
    cout<<"Pentru iesire tastati 0\n";
    cout<<"\n Comanda dumneavoastra este ";
    cin>>comanda;
    while(comanda)
       {
        switch(comanda)
        {
        case 1:
            {
                Matrice_patratica m;
                cin>>m;
                cout<<m;
                break;
            }
        case 2:
            {
                Matrice_patratica m;
                cin>>m;
                m.diagonala();
                break;
            }
        case 3:
            {
                Matrice_patratica m;
                cin>>m;
                Complex det;
                det=m.determinant();
                cout<<"\nDeterminantul este ";
                cout<<det;
                break;
            }
        case 4:
            {
                cout<<"Numarul de obiecte este ";
                int no;
                cin>>no;
                Matrice_patratica *obiecte[no];
                for(int i=0;i<no;i++)
                {
                    obiecte[i]=new Matrice_patratica;
                    cin>>*(obiecte[i]);
                }
                 for(int i=0;i<no;i++) cout<<*(obiecte[i]);
                 break;
            }
    }
    cout<<"\nComanda dumneavoastra este ";
    cin>>comanda;
       }
}
void oarecare()
{
    int comanda;
    cout<<"Pentru citire si afisare tastati 1\n";
    cout<<"Pentru a verifica daca o matrice este diagonala tastati 2\n";
    cout<<"Pentru citirea,memorarea si afisarea a n obiecte tastati 3\n";
    cout<<"Pentru iesire tastati 0\n";
    cout<<"\n Comanda dumneavoastra este ";
    cin>>comanda;
    while(comanda)
    {
    switch(comanda)
        {
        case 1:
            {
                Matrice_oarecare m;
                cin>>m;
                cout<<m;
                break;
            }
        case 2:
            {
                Matrice_oarecare m;
                cin>>m;
                m.diagonala();
                break;
            }
        case 3:
            {
                cout<<"Numarul de obiecte este ";
                int no;
                cin>>no;
                Matrice_oarecare *obiecte[no];
                for(int i=0;i<no;i++)
                {
                    obiecte[i]=new Matrice_oarecare;
                    cin>>*(obiecte[i]);
                }
                 for(int i=0;i<no;i++) cout<<*(obiecte[i]);
                 break;
            }
        }
        cout<<"\nComanda dumneavoastra este ";
        cin>>comanda;
       }
}
void nr_Complexe()
{
    cout<<"Constructor de initializare: ";
    Complex x (0,0);
    cout<<x;
    cout<<"\nConstructor de copiere: ";
    Complex y(x) ;
    cout<<y;
    Complex z;
    z=y;
    cout<<" "<<z;
    cout<<"\nNumarul de obiecte este ";
    int n;
    cin>>n;
    Complex* v;
    v=new Complex[n];
    for(int i=0;i<n;i++)
     cin>>v[i];
    for(int i=0;i<n;i++)  cout<<v[i]<<" ";
}

void upcast()
{
    int n;
    cout<<"\n Dati numarul de obiecte ";
    cin>>n;
    Matrice *m[n];
    for(int i=0;i<n;i++)
    {
        cout<<" Daca tastati 1 se va introduce o matrice oarecare, iar daca tastati 2 se va introduce o matrice patratica";
        int comanda;
        cin>>comanda;
        switch(comanda)
        { case 1:
            {m[i]=new Matrice_oarecare();
            cin>>*(Matrice_oarecare*)m[i];
            break;
            }
        case 2:
            {
                m[i]=new Matrice_patratica();
                cin>>*(Matrice_patratica*)m[i];
                break;
            }
        }
    }
    Matrice_oarecare mo;
    for(int i=0;i<n;i++)
        if(typeid (*m[i])==typeid(mo))
         cout<<*(Matrice_oarecare*)(m[i])<<endl;
    else cout<<*(Matrice_patratica*)(m[i])<<endl;
}

int main()
{
    cout<<"             Buna ziua! :)\n";
    for(int i=0;i<120;i++) cout<<"-";
    cout<<endl;
    cout<<"Pentru a lucra cu matrice patratica tastati 1\n";
    cout<<"Pentru a lucra cu matrice oarecare tastati 2\n";
    cout<<"Pentru a citi, memora si afisa n numere complexe tastati 3\n";
    cout<<"Pentru n obiecte de tip matrice folosind upcasting tastati 4\n";
    cout<<"Pentru iesirea din meniu tastati 0\n";
    cout<<endl;
    for(int i=0;i<120;i++) cout<<"-";
    cout<<endl;
    int com;
    cin>>com;
    while(com)
    {
     switch(com){
     case 1:{patratica(); break;}
     case 2:{oarecare(); break;}
     case 3:{nr_Complexe(); break;}
     case 4:{upcast(); break;}
     }
     cout<<"\nComanda dumneavoastra este ";
     cin>>com;
     }

    return 0;
}
