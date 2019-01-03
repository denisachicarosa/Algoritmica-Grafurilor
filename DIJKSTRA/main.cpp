#include <fstream>
#include<vector>
#include<iostream>
#include <queue>
#define MAX_VALUE 9999

using namespace std;

vector< vector < pair < int, int > > > la;
int n, m, s;
vector< int > d, tata, viz, culoare;

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
        int x, y, z;
        f>>x>>y>>z;
        la[x].push_back({y, z});
        la[y].push_back({x, z});
    }
    s = 1;
}

void afisare()
{
   for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < la[i].size(); j++)
            cout<<la[i][j].first<<" ";
        cout<<endl;
    }
    for (int i = 1; i <= n; i++)
        cout<<tata[i]<<" ";
}

void initializare()
{
    for (int i = 1; i <= n; i++)
    {
        culoare[i] = i;
        d[i] = MAX_VALUE;
        tata[i] = 0;
        viz[i] = 0;
    }
}

int caut_min()
{
    int min = MAX_VALUE;
    int u = 0;
    for (int i = 1; i <= n; i++)
    if (d[i] < min && viz[i] == 0)
    {
        min = d[i];
        u = i;
    }
    return u;
}

void dijkstra()
{
    initializare();
    d[s] = 0;
    for (int i = 1; i <= n; i++)
    {
        int u;
        u = caut_min();
        viz[u] = 1;
        for (int j = 0; j < la[u].size(); j++)
        {
            int v = la[u][j].first;
            if (d[v] > d[u] + la[u][j].second)
            {
                tata[v] = u;
                d[v] = d[u] + la[u][j].second;
            }
        }
    }
    for (int i = 1; i <= n; i++)
        cout<<tata[i]<<" ";
    cout<<endl;
    for (int i = 1; i <= n; i++)
        cout<<d[i]<<" ";
}

int main()
{
    citire();
    dijkstra();
    return 0;
}
