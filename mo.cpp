// Mo's algorithm
// O((N+Q) F sqrt(N)) where add/remove takes O(F)
// Example: CF 86D - Powerful Array

struct query {
    static constexpr int S = sqrt(200000); // set block size to sqrt(MAXN)
    int l, r, idx;
    bool operator<(query other) const {
        if (l / S != other.l / S) return l < other.l;
        return l / S % 2 ? r > other.r : r < other.r;
    }
};

struct mo {
    using answer = ll;
    answer sum = 0;
    vi k = vi(1000001);
    
    inline void add(int i) {
        sum += a[i]*(2*k[a[i]]+1);
        k[a[i]]++;
    }

    inline void remove(int i) {
        k[a[i]]--;
        sum -= a[i]*(2*k[a[i]]+1);
    }

    vector<query> queries;
    vi a;
    mo(vi& a) : a(a) {}

    void add_query(int l, int r) {
        queries.push_back({l, r, (int)queries.size()});
    }

    // returns answers in orginal order
    vector<answer> solve() {
        vector<answer> answers(queries.size());
        sort(queries.begin(), queries.end());
        int l = 0, r = -1;
        for (query& q : queries) {
            while (l > q.l) add(--l);
            while (r < q.r) add(++r);
            while (l < q.l) remove(l++);
            while (r > q.r) remove(r--);
            answers[q.idx] = sum; // set answer
        }
        return answers;
    }
};
