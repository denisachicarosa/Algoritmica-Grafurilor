#include <fstream>
#include<vector>
#include<iostream>
#include <queue>
using namespace std;

struct muchie
{
    int n1,n2,c;
};

vector<vector<pair<int,int> > > la;
vector<muchie> vm,E;
int n,m;
vector<int>d, tata,viz,culoare,reprez,h;
priority_queue<pair<int,int> > Q;
void citire()
{
    ifstream f("graf.in");
    f>>n>>m;
    viz.resize(n+1);
    tata.resize(n+1);
    reprez.resize(n+1);
    h.resize(n+1);
    culoare.resize(n+1);
    la.resize(n+1);
    d.resize(n+1);
    for(int i=0;i<m;i++)
    {
        int x,y,z;
        f>>x>>y>>z;
        muchie a;
        a.n1=x; a.n2=y; a.c=z;
        vm.push_back(a);
        la[x].push_back({y,z});
        la[y].push_back({x,z});
    }
}

void afisare()
{
//   for(int i=1;i<=n;i++)
//    { for(int j=0;j<la[i].size();j++) cout<<la[i][j].first<<" ";
//    cout<<endl;}
 for(int i=0;i<E.size();i++) cout<<E[i].n1<< " "<<E[i].n2<<" "<<E[i].c<<endl;
    for(int i=1;i<=n;i++) cout<<tata[i]<<" ";
}

void initializare()
{
    for(int i=1;i<=n;i++)
    {
        culoare[i]=i;
        reprez[i]=i;
        h[i]=0;
        d[i]=9999;
        tata[i]=0;
        viz[i]=0;
    }
}

void sortare()
{
    for(int i=0;i<m-1;i++)
        for(int j=i+1;j<m;j++)
        if(vm[i].c>vm[j].c) swap(vm[i],vm[j]);
}


int Reprezentant(int x)
{
    while(tata[x]!=0)
        x=tata[x];
    return x;
}

void reuneste(int u,int v)
{
    int rv,ru;
    rv=Reprezentant(v);
    ru=Reprezentant(u);
    if(h[rv]>h[ru]) tata[ru]=rv;
    else {tata[rv]=ru; if(h[rv]==h[ru]) h[ru]++;}
}

void kruskall2()
{
    int nrmsel=0;
    for(int i=0;i<m;i++)
    {
        if(Reprezentant(vm[i].n1)!=Reprezentant(vm[i].n2))
        {
            reuneste(vm[i].n1,vm[i].n2);
            E.push_back(vm[i]);
            nrmsel++;
            if(nrmsel==n-1) break;
        }
    }

}



int main()
{
    citire();
    initializare();
    sortare();

    kruskall2();
    afisare();
    return 0;
}
