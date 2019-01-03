#include <fstream>
#include<vector>
#include<iostream>
#include <queue>
using namespace std;

struct muchie
{
    int n1, n2, c;
};

vector < vector < pair < int, int > > > la;
vector < muchie > vm;
int n, m;
vector < int > d, tata, viz, culoare;

void citire()
{
    ifstream f("graf.in");
    f>>n>>m;
    viz.resize(n+1);
    tata.resize(n+1);
    culoare.resize(n+1);
    la.resize(n+1);
    d.resize(n+1);
    for (int i = 0; i < m; i++)
    {
        int x,y,z;
        f>>x>>y>>z;
        muchie a;
        a.n1 = x;
        a.n2 = y;
        a.c = z;
        vm.push_back(a);
        la[x].push_back({y, z});
        la[y].push_back({x, z});
    }
}

void afisare()
{
    for (int i = 0; i < m; i++)
        cout<<vm[i].n1<< " "<<vm[i].n2<<" "<<vm[i].c<<endl;
    for (int i = 1; i <= n; i++)
        cout<<tata[i]<<" ";
}

void initializare()
{
    for (int i = 1; i <= n; i++)
    {
        culoare[i] = i;
        d[i] = 9999;
        tata[i] = 0;
        viz[i] = 0;
    }
}

void reuneste(int x, int y)
{
    int c1 ,c2;
    c1 = culoare[x];
    c2 = culoare[y];
    for (int i = 1; i <= n; i++)
        if (culoare[i] == c2) culoare[i] = c1;
}

void sorteaza()
{
    for (int i = 0; i < m - 1; i++)
        for (int j = i + 1; j < m; j++)
        if (vm[i].c > vm[j].c) swap(vm[i], vm[j]);
}


void kruskall()
{
    int nrmsel = 0;
    for (int i = 0; i < m; i++)
    {
        if (culoare[vm[i].n1] != culoare[vm[i].n2])
        {
            cout<<"adaug muchia "<<vm[i].n1<<" "<<vm[i].n2<<" "<<vm[i].c<<endl;
            reuneste(vm[i].n1, vm[i].n2);
            nrmsel++;
            if (nrmsel == n-1) break;
        }
    }
}


int main()
{
    citire();
    initializare();
    sorteaza();
    kruskall();
    return 0;
}
