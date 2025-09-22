ll mex(vll v)
{
    sort(vr(v));
    ll mx = 0;
    fl(i, v.size())
    {
        if (v[i] == mx)
        {
            mx++;
        }
    }
    return mx;
}
