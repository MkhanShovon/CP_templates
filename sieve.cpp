const ll N = 2e5;
vll prime;
void sieve()
{
    vector<bool> is_prime(N + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (ll i = 2; i * i <= N; i++)
    {
        if (is_prime[i])
        {
            for (ll j = i * i; j <= N; j += i)
            {
                is_prime[j] = false;
            }
        }
    }

    fls(i, 1, N)
    {
        if(is_prime[i])
        {
            prime.pb(i);
        }
    }
}

//collecting prime factors
const ll N = 2e5 + 10;
vll prime;
vector<vll> pf(N + 10);
void sieve()
{
    fls(i, 2, N)
    {
        if(!pf[i].empty()) continue;
        for(ll j = i; j <= N; j += i)
        {
            pf[j].pb(i);
        }
    }
}
