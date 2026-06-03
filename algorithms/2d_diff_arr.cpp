vector<vll> dif(N + 3, vll(N + 3));
    auto cov = dif, pf = dif;
    fl(i, n){
        ll u = v[i][0], d = v[i][1];
        ll l = v[i][2], r = v[i][3];
        dif[u][l]++;
        dif[u][r + 1]--;
        dif[d + 1][l]--;
        dif[d + 1][r + 1]++;
    }

    fls(r, 1, N){
        fls(c, 1, N){
            cov[r][c] = dif[r][c] + cov[r][c - 1] + cov[r - 1][c] - cov[r - 1][c - 1];
        }
    }

    fls(r, 1, N){
        fls(c, 1, N)
        {
            pf[r][c] = pf[r - 1][c] + pf[r][c - 1] - pf[r - 1][c - 1] + (cov[r][c] == 1);
        }
    }

    ll nz = 0;
    fls(r, 1, N){
        fls(c, 1, N)
        {
            nz += (cov[r][c] > 0);
        }
    }

    ll tot = 2000 * 2000;
    fls(k, 1, n) {
        ll u = v[k - 1][0], d = v[k - 1][1];
        ll l = v[k - 1][2], r = v[k - 1][3];
        ll ans = nz - (pf[d][r] - pf[u - 1][r] - pf[d][l - 1] + pf[u - 1][l - 1]);
        ans = tot - ans;
        print(ans);
    }
