#include <fstream>
#include<vector>
#include<iostream>
#include <queue>
#include<utility>
using namespace std;

vector<vector<pair<int,int> > > la;
int n,m;
vector<int>d, tata,viz,culoare;
class compar
{
public:
    bool operator()(const pair<int,int> &o1,const pair<int,int>& o2)
    {
        return o1.second>o2.second;
    }
};

priority_queue<pair<int,int> ,vector<pair<int,int> > ,compar> Q;

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
//   for(int i=1;i<=n;i++)
//    { for(int j=0;j<la[i].size();j++) cout<<la[i][j].first<<" ";
//    cout<<endl;}
   cout<<endl; for(int i=1;i<=n;i++) cout<<tata[i]<<" ";
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

void prim2(int s)
{
    d[s]=0;
    Q.push({s,d[s]});
    while(!Q.empty())
    {
        int u=Q.top().first;
        cout<<u<<" ";
        Q.pop();
        viz[u]++;
        if(viz[u]==1)
        {
        for(int i=0;i<la[u].size();i++)
        {
            int v,cost;
            v=la[u][i].first;
            cost=la[u][i].second;
            if(viz[v]==0)
            {
                if(d[v]>cost) {d[v]=cost; tata[v]=u; Q.push({v,d[v]});}
            }
        }
    }

}}


int main()
{citire();
initializare();
prim2(1);
afisare();
    return 0;
}
