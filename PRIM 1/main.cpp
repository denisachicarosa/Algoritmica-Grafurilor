#include <fstream>
#include<vector>
#include<iostream>
#include <queue>
using namespace std;

vector<vector<pair<int,int> > > la;
int n,m;
vector<int>d, tata,viz,culoare;

void citire()
{
    ifstream f("graf.in");
    f>>n>>m;
    viz.resize(n+1);
    tata.resize(n+1);
    culoare.resize(n+1);
    la.resize(n+1);
    d.resize(n+1);
    for(int i=0;i<m;i++)
    {
        int x,y,z;
        f>>x>>y>>z;
        la[x].push_back({y,z});
        la[y].push_back({x,z});
    }
}

void afisare()
{
   for(int i=1;i<=n;i++)
    { for(int j=0;j<la[i].size();j++) cout<<la[i][j].first<<" ";
    cout<<endl;}
    for(int i=1;i<=n;i++) cout<<tata[i]<<" ";
}

void initializare()
{
    for(int i=1;i<=n;i++)
    {
        culoare[i]=i;
        d[i]=9999;
        tata[i]=0;
        viz[i]=0;
    }
}

int caut_min()
{
    int min=99999,u=0;
    for(int i=1;i<=n;i++)
        if(min>d[i]&&viz[i]==0)
    {
        min=d[i];
        u=i;
    }
    return u;
}

bool continua()
{
    for(int i=1;i<=n;i++)
        if(viz[i]==0) return true;
    return false;
}

void actualizez(int x)
{
    for(int i=0;i<la[x].size();i++)
    {
        int y=la[x][i].first;
        if(viz[y]==0&&d[y]>la[x][i].second)
        {
            d[y]=la[x][i].second;
            tata[y]=x;
        }
    }
}

void prim(int s)
{//cout<<"prim ";
    if(continua()==true)
    {   viz[s]=1;
        actualizez(s);
        cout<<s<<" ";
         s=caut_min();
        prim(s);
    }

}

int main()
{
   citire();
   initializare();
   d[1]=0;
   tata[1]=0;
   prim(1);
   afisare();
    return 0;
}
