struct tree{
    ll N;
    vector<vector<ll>> g, parent;
    vector<ll> dep;
    tree(ll n){
        N = n+7;
        g.resize(N);
        parent.resize(N);
        dep.resize(N);
        for(ll i = 0; i < N; i++)
            parent[i].resize(21);
    }
    vector<ll> & operator[](ll i){
        return g[i];
    }
    void dfs(ll ver, ll p = 0){
        parent[ver][0] = p;
        dep[ver] = dep[p] + 1;
        for(auto &ch:g[ver]){
            if(ch == p)
                continue;
            dfs(ch, ver);
        }
    }
    void build(ll src){
        dep[0] = -1;
        dfs(src);
        for(ll j = 1; j < 21; j++)
            for(ll i = 1; i < N; i++)
                parent[i][j] = parent[parent[i][j-1]][j-1];
    }
    ll par(ll n, ll i){
        ll cur = n;
        for(ll j = 0; j < 21; j++)
            if(i & (1 << j))
                cur = parent[cur][j];
        return cur;
    }
    ll lca(ll a, ll b){
        if(dep[a] < dep[b])
            swap(a, b);
        ll dif = abs(dep[a]-dep[b]);
        a = par(a, dif);
        if(a == b)
            return a;
        for(ll i = 20; i >= 0; i--){
            if(parent[a][i] != parent[b][i]){
                a = parent[a][i];
                b = parent[b][i];
            }
        }
        return parent[a][0];
    }
};
