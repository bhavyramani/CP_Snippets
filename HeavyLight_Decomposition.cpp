struct HeavyLight{
    ll n, ind = 1, id = INT64_MIN;
    vector<vector<ll>> g;
    vector<ll> size, heavy, parent, depth, head, lt, tree, pos, value;
    
    HeavyLight(ll _n){
    n = _n;
    g.resize(n+1);
    size.resize(n+1);
    heavy.resize(n+1);
    parent.resize(n+1);
    depth.resize(n+1);
    head.resize(n+1);
    lt.resize(n+1);
    pos.resize(n+1);
    value.resize(n+1);
    tree.resize(2*(n+1), id);
    }

    void add(ll u, ll v){
        g[u].push_back(v);
        g[v].push_back(u);
    }

    inline ll fun(ll a, ll b){
        return max(a, b);
    }

    void route_dfs(ll ver){
        for(auto &ch:g[ver]){
            if(ch == parent[ver])
                continue;
            depth[ch] = depth[ver] + 1;
            parent[ch] = ver;
            route_dfs(ch);
            size[ver] += size[ch];
            if(size[ch] > size[heavy[ver]])
                heavy[ver] = ch;
        }
        size[ver]++;
    }

    void dfsHLD(ll ver, ll chain){
        head[ver] = chain;
        lt[ind] = value[ver];
        pos[ver] = ind++;

        if(heavy[ver] != 0)
            dfsHLD(heavy[ver], chain);
        
        for(auto &ch:g[ver]){
            if(heavy[ver] != ch && ch != parent[ver]){
                dfsHLD(ch, ch);
            }
        }
    }

    void build(ll ver){
        route_dfs(ver);
        dfsHLD(ver, ver);
        for(ll i = 1; i <= n; i++)
            update(i, value[i]);
    }

    ll lca(ll a, ll b){
        while(head[a] != head[b]){
            if(depth[head[a]] < depth[head[b]])
                swap(a, b);
            a = parent[head[a]];
        }
        if(depth[a] < depth[b])
            swap(a, b);
        return b;
    }

    void update(ll p, ll val){
        value[p] = val;
        p = pos[p];
        lt[p] = val;
        p += n;
        tree[p] = val;
        for(ll i = p; i > 1; i >>= 1)
            tree[i>>1] = fun(tree[i], tree[i^1]);
    }

    ll qry(ll l, ll r){
        if(l > r)
            return 0;
        ++r;
        ll res = id;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1){
            if (l&1)
                res = fun(res, tree[l++]);
            if (r&1)
                res = fun(res, tree[--r]);
        }
        return res;
    }

    ll query(ll u, ll v){
        ll ans = id;
        while(head[u] != head[v]){
            if(depth[head[u]] < depth[head[v]])
                swap(u, v);
            ans = fun(ans, qry(pos[head[u]], pos[u]));
            u = parent[head[u]];
        }
        if(depth[u] < depth[v])
            swap(u, v);
        ans = fun(ans, qry(pos[v], pos[u]));
        return ans;
    }
};
