#include <iostream>
#include<fstream>
#include<vector>
#include <algorithm>


using namespace std;

vector < pair < int,int > > grade;

bool continua()
{
    for (int i = 0; i < grade.size(); i++)
        if (grade[i].first! = 0) return true;
    return false;
}

int main()
{
   ifstream f("graf.in");
   int n, sum = 0;
   f>>n;
   grade.resize(n + 1);
   for (int i = 1; i <= n; i++)
    {
        f>>grade[i].first;
        grade[i].second = i;
        if(grade[i].first > n - 1)
        {
            cout<<"Nu exista graf ";
            return 0;
        }
        sum += grade[i].first;
    }
    if (sum % 2 != 0)
    {
        cout<<"Nu exista graf";
        return 0;
    }
    for (int i = 1; i < n; i++)
        for (int j = i + 1; j <= n; j++)
            if (grade[i].first < grade[j].first)
                swap(grade[i],grade[j]);
    int i = 1;
    while(grade[i].first > 0)
    {
        pair < int, int > v;
        v.first = grade[i].first;
        v.second = grade[i].second;
        for (int j = 1; j <= v.first; j++)
        {
            grade[i + j].first--;
            if (grade[i + j].first < 0)
            {
                cout<<"Nu exista graf ";
                return 0;
            }
            cout<<v.second<<" "<<grade[i + j].second<<endl;
        }
        int k = i + v.first;
        if(k + 1 <= n && grade[k].first < grade[k + 1].first)
        {
            int poz1 = k - 1;
            while (poz1 >= 1 && grade[poz1].first == grade[k].first)
                poz1--;
            poz1++;
            int poz2 = k + 2;
            while(poz1 <= n && grade[poz2].first == grade[k + 1].first)
                poz2++;
           reverse(grade.begin() + poz1,grade.begin() + poz2);
        }
        grade[i].first = 0;
        i++;
    }


    return 0;
}
