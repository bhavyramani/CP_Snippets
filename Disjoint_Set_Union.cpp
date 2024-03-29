struct dsu{
    vector<ll> par, sz;
    ll n;
    dsu(ll _n){
        n = _n+1;
        par.resize(n, 0);
        sz.resize(n, 1);
        iota(par.begin(), par.end(), 0);
    }

    ll find(ll v){
        if(v == par[v])
            return v;
        return par[v] = find(par[v]);
    }

    void merge(ll v, ll u){
        v = find(v);
        u = find(u);
        if(sz[u] > sz[v])
            swap(u, v);
        if(v != u){
            par[u] = v;
            sz[v] += sz[u];
        }
    }
};
