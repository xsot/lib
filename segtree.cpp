// Lazy segment tree
// O(n) construction, O(log n) updates, O(n) queries
// Commented lines need to be customised
// Example: range increment update with range sum query (SPOJ HORRIBLE)

struct segtree {
    int n;
    vector<ll> t, lazy;

    segtree(int sz) : n(sz), t(n*4), lazy(n*4) {}
    segtree(vector<ll>& a) : segtree(a.size()) {
        build(a, 1, 0, n-1);
    }

    ll combine(ll a, ll b) { // monoid operation
        return a + b;
    }

    void build(vector<ll>& a, int v, int l, int r) {
        if (l == r) {
            t[v] = a[l]; // init
        } else {
            build(a, v*2, l, (l+r)/2);
            build(a, v*2+1, (l+r)/2+1, r);
            t[v] = combine(t[v*2], t[v*2+1]);
        }
    }

    void push(int v, int l, int r) {
        if (lazy[v]) {
            t[v] += lazy[v]*(r-l+1); // apply lazy
            if (l != r) {
                lazy[v*2] += lazy[v]; // compose lazy
                lazy[v*2+1] += lazy[v];
            }
            lazy[v] = 0; // lazy identity
        }
    }

    void update(int ql, int qr, ll val) { update(ql, qr, val, 1, 0, n-1); }
    void update(int ql, int qr, ll val, int v, int l, int r) {
        push(v, l, r);
        if (ql > qr) return;
        if (ql == l && qr == r) {
            lazy[v] = val;
            push(v, l, r);
        } else {
            int m = (l+r)/2;
            update(ql, min(qr, m), val, v*2, l, m);
            update(max(ql, m+1), qr, val, v*2+1, m+1, r);
            t[v] = combine(t[v*2], t[v*2+1]);
        }
    }

    ll query(int ql, int qr) { return query(ql, qr, 1, 0, n-1); }
    ll query(int ql, int qr, int v, int l, int r) {
        push(v, l, r);
        if (ql > qr) return 0; // identity
        if (ql == l && r == qr) return t[v];
        int m = (l+r)/2;
        return combine(query(ql, min(qr, m), v*2, l, m), query(max(ql, m+1), qr, v*2+1, m+1, r));
    }
};
