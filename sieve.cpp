//Optimized sieve
vector<long long int> prime;    //List of primes
const int nx = 1e6 + 10;        // range of prime numbers

void generate_prime()           //For generating all primes within 10^6 using sieve of eratosthenes
{

    bool flag[nx]={};

    int rt = 1e3;               // because root of 10^6 is 10^3

    for(int i=3; i<rt; i+=2)
    {
        if(!flag[i])
        {
            for(int j=i*i; j<nx; j+=(i<<1))
            {
                flag[j] = true;
            }
        }
    }

    prime.push_back(2);
    for(int i=3; i<nx; i+=2)
    {
        if(!flag[i]) prime.push_back(i);
    }
}

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
