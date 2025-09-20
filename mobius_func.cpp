#include <bits/stdc++.h>
using namespace std;

using ll = long long;


const ll VALMAX = 1e7;
ll mobius[VALMAX];

void mob_init()
{
    mobius[1] = -1;
    for (ll i = 1; i < VALMAX; i++)
    {
        if (mobius[i])
        {
            mobius[i] = -mobius[i];
            for (ll j = 2 * i; j < VALMAX; j += i)
            {
                mobius[j] += mobius[i];
            }
        }
    }
}

int main()
{
   
}