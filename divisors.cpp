vll divisors(ll n)
{
    vll v;
    for (ll i = 1; i <= sqrt(n); i++)
    {
        if (n % i == 0)
        {
            if (n / i == i)
            {
                v.pb(i);
            }
            else
            {
                v.pb(i);
                v.pb(n / i);
            }
        }
    }
    sort(vr(v));
    return v;
}
