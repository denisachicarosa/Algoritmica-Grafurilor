#include <iostream>
#include <fstream>
#include<vector>
#include <queue>

using namespace std;

vector< vector < int > > la;
int n, m;
vector< int > tata, vizitat, culoare;

void citire()
{
    ifstream f("graf.in");
    f>>n>>m;
    vizitat.resize(n+1);
    tata.resize(n+1);
    culoare.resize(n+1);
    la.resize(n+1);
    for (int i = 0; i < m; i++)
    {
        int x, y;
        f>>x>>y;
        la[x].push_back(y);
        la[y].push_back(x);
    }
}

void afisare()
{
   for (int i = 1; i <= n ; i++)
    {
        for (int j =0; j < la[i].size(); j++)
            cout<<la[i][j]<<" ";
        cout<<endl;
    }
}

void initializare()
{
    for (int i = 1; i <= n; i++)
    {
        culoare[i] = i;
        tata[i] = 0;
        vizitat[i] = 0;
    }
}

void bfs(int s)
{
    queue<int> q;
    q.push(s);
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        cout<<u<<" ";
        vizitat[u] = 1;
        for (int i = 0; i < la[u].size(); i++)
        {
            int v = la[u][i];
            if (vizitat[v] == 0)
            {
                vizitat[v] = 1;
                tata[v] = u;
                q.push(v);
            }
        }
    }
}

int main()
{
    citire();
    initializare();
    afisare();
    cout<<endl;
    bfs(1);
    cout<<endl;
    for (int i = 1; i <= n; i++)
        cout<<tata[i]<<" ";
    return 0;
}
