// min/max sparse table
// O(n log n) construction, O(1) queries

template<typename Op>
struct sparsetable {
    Op op;
    vvi st;
    sparsetable(vi& a) {
        int n = a.size();
        int m = 32-__builtin_clz(n);
        st = vvi(n, vi(m));
        for (int i=0; i < n; i++) st[i][0] = a[i];
        for (int j=1; j <= m; j++)
            for (int i=0; i+(1<<j) <= n; i++)
                st[i][j] = op(st[i][j-1], st[i+(1<<(j-1))][j-1]);
    }
    int query(int l, int r){
        int i = 31-__builtin_clz(r-l+1);
        return op(st[l][i], st[r-(1<<i)+1][i]);
    }
};
struct max_op {
    int operator()(auto a, auto b) { return max(a, b); }
};
struct min_op {
    int operator()(auto a, auto b) { return min(a, b); }
};
