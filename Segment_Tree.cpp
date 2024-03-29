struct Node{
    ll val;
    Node(ll _val = 0){
        val = _val;
    }
    friend Node operator+(const Node &l, const Node &r){
        Node ans = Node();
        ans.val = l.val + r.val;
        return ans;
    }
};

template<class T = Node>
struct SegTree {
    vector<T> tree;
    ll n;
    T id = T();
    SegTree(ll _n){
        n = _n;
        tree.resize(2*n, id);
    }

    void update(ll p, ll val){
        p += n;
        tree[p] = T(val);
        for(ll i = p; i > 1; i >>= 1)
            tree[i>>1] = tree[i] + tree[i^1];
    }

    T query(ll l, ll r){
        if(l > r)
            return id;
        ++r;
        T ans = id;
        for(l += n, r += n; l < r; l >>= 1, r >>= 1){
            if(l&1)
                ans = ans + tree[l++];
            if(r&1)
                ans = ans + tree[--r];
        }
        return ans;
    }
};
