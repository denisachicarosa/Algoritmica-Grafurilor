#include <iostream>
#include <fstream>
#include<vector>
#include <queue>
using namespace std;

vector<vector<int> > la;
int n,m;
vector<int> tata,viz,culoare;

void citire()
{
    ifstream f("graf.in");
    f>>n>>m;
    viz.resize(n+1);
    tata.resize(n+1);
    culoare.resize(n+1);
    la.resize(n+1);
    for(int i=0;i<m;i++)
    {
        int x,y;
        f>>x>>y;
        la[x].push_back(y);
        la[y].push_back(x);
    }
}

void afisare()
{
   for(int i=1;i<=n;i++)
    { for(int j=0;j<la[i].size();j++) cout<<la[i][j]<<" ";
    cout<<endl;}
}

void initializare()
{
    for(int i=1;i<=n;i++)
    {
        culoare[i]=i;
        tata[i]=0;
        viz[i]=0;
    }
}

void dfs(int x)
{
    cout<<x<<" ";
    viz[x]=1;
    for(int i=0;i<la[x].size();i++)
        {if(viz[la[x][i]]==0) dfs(la[x][i]); tata[la[x][i]]=x;}
}

int main()
{
    citire();
    initializare();
    dfs(1);

    return 0;
}
