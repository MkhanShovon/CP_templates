vector<ll> nextSmaller(vector<ll> v)
{
    stack<ll> s;
    ll i = 0;
    ll n = v.size();
    // debug(v);
    vector<ll> ans(n, n);
    while (i < n)
    {
        while (!s.empty() and v[s.top()] > v[i])
        {
            ans[s.top()] = i;
            // debug(s.top(), i, v[i]);
            s.pop();
        }
        s.push(i);
        i++;
    }
    return ans;
}

vector<ll> prvSmaller(vector<ll> v)
{
    stack<ll> s;
    ll i = 0;
    ll n = v.size();
    reverse(v.begin(), v.end());
    vector<ll> ans(n, -1);
    while (i < n)
    {
        while (!s.empty() and v[s.top()] > v[i])
        {
            ans[n - 1 - s.top()] = n - i - 1;
            s.pop();
        }
        s.push(i++);
    }
    // reverse(ans.begin(), ans.end());
    return ans;
}

vector<ll> nextGreater(vector<ll> v)
{
    stack<ll> s;
    ll i = 0;
    ll n = v.size();
    // debug(v);
    vector<ll> ans(n, n);
    while (i < n)
    {
        while (!s.empty() and v[s.top()] < v[i])
        {
            ans[s.top()] = i;
            // debug(s.top(), i, v[i]);
            s.pop();
        }
        s.push(i);
        i++;
    }
    return ans;
}
