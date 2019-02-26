// Fenwick tree with O(log n) lower_bound
// Inverse operation not required to support only prefix queries

struct fenwick {
    vector<int> a; // 0-index interface but 1-index implementation
    int n;

    fenwick(int sz) : n(sz+1), a(sz+1) {}
    fenwick(vector<int>& v) : fenwick(v.size()) {
        for (int i=0; i < v.size(); i++) update(i, v[i]);
    }

    void update(int i, int delta) {
        for (i++; i < n; i += i&-i) {
            a[i] = a[i] + delta;
        }
    }
    
    int query(int i) { // a[0] + ... + a[i]
        int ret = 0;
        for (i++; i > 0; i -= i&-i) {
            ret = ret + a[i];
        }
        return ret;
    }
    
    int query(int l, int r) { // a[l] + ... + a[r]
        return query(r) - query(l-1);
    }
    
    int lower_bound(int v) { // smallest i where v <= a[0] + ... + a[i]
        int k = 0;
        while (1<<(k+1) <= n) k++;
        int index = 0;
        for (; k >= 0; k--) {
            int next_index = index + (1<<k);
            if (next_index < n && a[next_index] < v) {
                index = next_index;
                v -= a[index];
            }
        }
        return index;
    }
};

struct rupq_fenwick : fenwick {
    rupq_fenwick(int n) : fenwick(n) {}
    int point_query(int r) {
        return query(r);
    }
    void range_update(int l, int r, int delta) {
        update(l, delta);
        update(r+1, -delta);
    }
}

struct rurq_fenwick {
    fenwick a, b;
    rurq_fenwick(int n) : a(n), b(n) {}
    void update(int l, int r, int delta) {
        a.update(l, delta);
        a.update(r+1, -delta);
        b.update(l, delta*(l-1));
        b.update(r+1, -delta*r);
    }
    int query(int r) {
        return a.query(r)*r - b.query(r)
    }
}
