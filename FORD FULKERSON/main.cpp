#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

vector<vector<int> > N,gr,linit;
vector<int> tata, viz;
int n,m,s,t;
int flux;

void citire()
{

    ifstream f("graf.in");
    f>>n>>s>>t>>m;
    flux=1;
    tata.resize(n+1);
    viz.resize(n+1);
    N.resize(n+1);
    gr.resize(n+1);
    linit.resize(n+1);
    for(int i=1;i<=n;i++)
    {   tata[i]=viz[i]=0;
        N[i].resize(n+1);
        gr[i].resize(n+1);
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        N[i][j]=gr[i][j]=0;

   for(int k=0;k<m;k++)
   {    int i,j,c,fl;
       f>>i>>j>>c>>fl;
       if(fl>c)
       flux=0;
       N[i][j]=c;
       linit[i].push_back(j);
       gr[i][j]=c-fl;
       gr[j][i]=fl;
   }

    for(int i=1;i<=n&&flux;i++)
     if(s!=i&&t!=i)
      {
        int s1,s2; s1=s2=0;
        for(int j=1;j<=n;j++)
        {
            if(N[i][j]>0) s1+=gr[j][i];
            if(N[j][i]>0) s2+=gr[i][j];
        }

        if(s1!=s2) flux=0;
    }

}

bool bfs()
{
     for(int i=1;i<=n;i++) viz[i]=tata[i]=0;
    queue<int> Q;
    Q.push(s);
    viz[s]=1;
    while(!Q.empty())
    {
        int u=Q.front();
        Q.pop();
        viz[u]=1;
        for(int i=1;i<=n;i++)
            if(viz[i]==0&&gr[u][i]>0)
        {
            tata[i]=u;
            Q.push(i);

            if(i==t) return true;
        }
    }
 return false;
}

void ford_fulkerson()
{
    citire();
    if(flux==0) cout<<"Nu exista ";
    else
    { cout<<"exista\n";
        while(bfs())
        {int min=9999;
        int x=t;
        while(tata[x]>0)
        {
            if(min>gr[tata[x]][x])min=gr[tata[x]][x];
            x=tata[x];
        }
        x=t;
        while(tata[x]>0)
        {
            gr[tata[x]][x]-=min;
            gr[x][tata[x]]+=min;
            x=tata[x];
        }
        }


    }

}
int main()
{
   citire();
   ford_fulkerson();

 for(int i=1;i<=n;i++)
            for(int j=0;j<linit[i].size();j++)
            cout<<i<<" "<<linit[i][j]<<" "<<gr[linit[i][j]][i]<<endl;
    return 0;
}
