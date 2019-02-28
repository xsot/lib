// Dinic's algorithm
// O(E V^2), O(E sqrt(V)) for unit networks
// Adapted from: https://cp-algorithms.com/graph/dinic.html

template<typename T>
struct dinic {
    struct edge {
        int u, v;
        T cap, flow = 0;
    };
    const T FLOW_INF = numeric_limits<T>::max();
    vector<edge> edges;
    vector<vector<int>> g;
    int n, m = 0;
    int s, t;
    vector<int> level, ptr;
    queue<int> q;

    dinic(int n, int s, int t) : n(n), s(s), t(t), g(n), level(n), ptr(n) {}

    void add_edge(int u, int v, T cap) {
        edges.push_back({u, v, cap, 0});
        edges.push_back({v, u, 0, 0});
        g[u].push_back(m);
        g[v].push_back(m+1);
        m += 2;
    }

    bool bfs() {
        fill(level.begin(), level.end(), -1);
        level[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int i : g[u]) {
                int v = edges[i].v;
                if (edges[i].cap - edges[i].flow < 1 || level[v] != -1) continue;
                level[v] = level[u] + 1;
                q.push(v);
            }
        }
        return level[t] != -1;
    }

    T dfs(int u, T pushed) {
        if (pushed == 0 || u == t) return pushed;
        for (int& cid = ptr[u]; cid < g[u].size(); cid++) {
            int i = g[u][cid];
            int v = edges[i].v;
            if (level[u]+1 != level[v] || edges[i].cap - edges[i].flow < 1) continue;
            T tr = dfs(v, min(pushed, edges[i].cap - edges[i].flow));
            if (tr > 0) {
                edges[i].flow += tr;
                edges[i^1].flow -= tr;
                return tr;
            }
        }
        return 0;
    }

    T flow() {
        T flow = 0;
        while (bfs()) {
            fill(ptr.begin(), ptr.end(), 0);
            while (T pushed = dfs(s, FLOW_INF)) flow += pushed;
        }
        return flow;
    }
};
