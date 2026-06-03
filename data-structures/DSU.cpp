class DSU
{
private:
    vector<ll> parent, size, minElement, maxElement;
    ll n;
    ll num, largest;

public:
    DSU(ll nn)
    {
        this->n = nn;
        parent.resize(n + 1);
        size.resize(n + 1, 1); // Each element is its own set initially, so size is 1
        minElement.resize(n + 1);
        maxElement.resize(n + 1);
        num = nn;
        largest = 1;

        for (ll i = 1; i <= n; ++i)
        {
            parent[i] = i;
            minElement[i] = i;
            maxElement[i] = i;
        }
    }

    ll find(ll u)
    {
        if (parent[u] != u)
        {
            parent[u] = find(parent[u]); // Path Compression
        }
        return parent[u];
    }

    void unite(ll u, ll v)
    {
        ll rootU = find(u);
        ll rootV = find(v);

        if (rootU != rootV)
        {
            // Union by Size
            if (size[rootU] < size[rootV])
            {
                swap(rootU, rootV); // Ensure rootU is always the larger set
            }

            parent[rootV] = rootU; // Merge the smaller set into the larger set
            size[rootU] += size[rootV];
            largest = max(largest, size[rootU]);
            minElement[rootU] = min(minElement[rootU], minElement[rootV]);
            maxElement[rootU] = max(maxElement[rootU], maxElement[rootV]);
            num--;
        }
    }

    tuple<int, int, int> get(int v)
    {
        int rootV = find(v);
        return {minElement[rootV], maxElement[rootV], size[rootV]};
    }

    int getNum()
    {
        return num;
    }

    int getLarg()
    {
        return largest;
    }
};