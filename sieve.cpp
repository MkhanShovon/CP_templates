const ll N = 300;
vll prime;
void sieve()
{
    vector<bool> is_prime(N + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (ll i = 2; i * i <= N; i++)
    {
        if (is_prime[i])
        {
            prime.pb(i);
            for (ll j = i * i; j <= N; j += i)
            {
                is_prime[j] = false;
            }
        }
    }
}
