template<typename T = ll>
struct SparseTable{
    ll n, lg;
    vector<ll> pw;
    vector<vector<T>> table;

    SparseTable(vector<T> &arr){
        n = arr.size();
        lg = ceil(log2(n+1));
        pw.resize(n+1);
        for(ll i = 2; i <= n; i++)
            pw[i] = pw[(i>>1)] + 1;
        table.resize(n, vector<T>(lg));

        for(ll i = 0; i < n; i++)
            table[i][0] = arr[i];

        for(ll j = 1; j < lg; j++)
            for(ll i = 0; i < n; i++)
                table[i][j] = merge(table[i][j-1], table[min(n-1, i + (1ll << (j-1)))][j-1]);
    }

    T merge(T &a, T &b){
        return __gcd(a, b);
    }

    T query(ll l, ll r){
        ll p = pw[r-l+1];
        return merge(table[l][p], table[r+1-(1ll << p)][p]);
    }
};