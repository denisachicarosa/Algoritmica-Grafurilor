#include <iostream>
#include <fstream>
#include<vector>

using namespace std;

int n,m,infinit=9999;
vector<vector<pair<int, int> > > la;
vector<vector<int> > d,p;
vector<int> exc;



void initializare()
{
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
    if(i==j) d[i][j]=0;
    else d[i][j]=infinit;
}

void citire()
{
    ifstream f("graf.in");
    f>>n>>m;
    la.resize(n+1);
    p.resize(n+1);
    d.resize(n+1);
    for(int i=1;i<=n;i++)
    {
        d[i].resize(n+1);
        p[i].resize(n+1);
    }
    initializare();
    for(int i=0;i<m;i++)
    {
        int x,y,z;
        f>>x>>y>>z;
        d[x][y]=z;
        //la[x].push_back({y,z});
        //la[y].push_back({x,z});
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        if(d[i][j]==infinit||i==j) p[i][j]=0;
    else p[i][j]=i;
    f.close();
}

void afisare()
{
   for(int i=1;i<=n;i++)
     {
         for(int j=1;j<=n;j++)
           if(d[i][j]==infinit) cout<<"inf ";
           else  cout<<d[i][j]<<" ";
         cout<<endl;
     }
     cout<<endl;
       for(int i=1;i<=n;i++)
     {
         for(int j=1;j<=n;j++)
            cout<<p[i][j]<<" ";
         cout<<endl;
     }
}


void floyd_warshall()
{
    for(int k=1;k<=n;k++)
        for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
    {
        if(d[i][j]>d[i][k]+d[k][j])
        {
            d[i][j]=d[i][k]+d[k][j];
           p[i][j]=p[k][j];
        }
    }
}

int main()
{
   citire();
   floyd_warshall();
   afisare();
    return 0;
}
