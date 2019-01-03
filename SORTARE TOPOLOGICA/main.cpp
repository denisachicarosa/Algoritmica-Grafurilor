#include <iostream>
#include <fstream>
#include <vector>
#include<queue>

using namespace std;

int n, m;
vector<int> din, dout, sortare, viz;
vector<vector<int> > la;



void citire ()
{
    ifstream f ("graf.in");
    f>>n>>m;
    din.resize (n+1);
    dout.resize (n+1);
    viz.resize (n+1);
    la.resize (n+1);
    for (int i = 1; i < = n; i++) viz[i] = din[i] = dout[i] = 0;
    for (int i = 0; i < m; i++)
    {
        int x, y;
        f>>x>>y;
        la[x].push_back (y);
        dout[x]++;
        din[y]++;
    }
}

queue<int> Q;

void cauta ()
{
    for (int i = 1; i <= n; i++)
        if (din[i] == 0 && viz[i] == 0)
        {
            Q.push (i);
            viz[i] = 1;
        }
}


void sortare_topologica ()
{

    cauta ();
    while (!Q.empty ())
    {
        int u = Q.front ();
        Q.pop ();
        cout<<u<<" ";
        sortare.push_back (u);
        for (int i = 0; i < la[u].size (); i++)
            din[la[u][i]]--;
        cauta ();
    }
}

int main ()
{
    citire ();
    sortare_topologica ();
    return 0;
}
