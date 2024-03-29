const ll MOD = 1e9 + 7;

struct Mint{
    ll v;
    explicit operator ll() const { return v; }
    Mint(ll _v = 0){
        v = (-MOD < _v && _v < MOD) ? _v : _v % MOD;
        if (v < 0)
            v += MOD;
    }

    friend Mint operator^(Mint a, ll p){
        Mint ans = 1;
        assert(p >= 0);
        for (; p; p /= 2, a *= a)
            if (p & 1)
                ans *= a;
        return ans;
    }

    friend bool operator==(const Mint &a, const Mint &b){
        return a.v == b.v;
    }
    friend bool operator!=(const Mint &a, const Mint &b){
        return !(a == b);
    }

    Mint &operator+=(const Mint &m){
        if ((v += m.v) >= MOD)
            v -= MOD;
        return *this;
    }
    Mint &operator-=(const Mint &m){
        if ((v -= m.v) < 0)
            v += MOD;
        return *this;
    }
    Mint &operator*=(const Mint &m){
        v = v * m.v % MOD;
        return *this;
    }
    Mint &operator/=(const Mint &m){ 
        assert(m.v != 0);
        return (*this) *= m ^ (MOD-2); 
    }

    friend Mint operator+(Mint a, const Mint &b) { return a += b; }
    friend Mint operator-(Mint a, const Mint &b) { return a -= b; }
    friend Mint operator*(Mint a, const Mint &b) { return a *= b; }
    friend Mint operator/(Mint a, const Mint &b) { return a /= b; }
    
    Mint operator-() const { return Mint(-v); }
    
    friend ostream &operator<<(ostream &, const Mint &m){
        cout << m.v;
        return cout;
    }
    friend istream &operator>>(istream &, Mint &m){
        ll x;
        cin >> x;
        m = Mint(x);
        return cin;
    }
};
vector<Mint> fac, inv;
void init(ll n){
    if(fac.size())
        return;
    fac.resize(n);
    inv.resize(n);
    fac[0] = inv[0] = 1;
    f(i, 1, n){
        fac[i] = i * fac[i-1];
        inv[i] = 1 / fac[i];
    }
}
Mint ncr(ll n, ll r){
    if(n < r || n < 0)
        return 0;
    return fac[n] * inv[r] * inv[n-r];
}