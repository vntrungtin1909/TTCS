#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int maxn = 100001;

class GraphInput
{
public:
    int num_dinh; // số lượng đỉnh
    int num_canh; // số lượng cạnh
    int start;    // đỉnh bắt đầu
    int des;      // đỉnh đích

    GraphInput()
    {
        cin >> num_dinh >> num_canh >> start >> des;
    }
};

class Graph
{
private:
    int n, m;                         // số lượng đỉnh và số lượng cạnh
    vector<pair<int, int>> adj[maxn]; // danh sách kề

public:
    Graph(const GraphInput &input) : n(input.num_dinh), m(input.num_canh) {}

    void addEdge(int x, int y, int w)
    {
        adj[x].push_back({y, w});
        adj[y].push_back({x, w});
    }

    vector<pair<int, int>> *getAdjList()
    {
        return adj;
    }

    ~Graph() = default;
};

class Dijkstra
{
protected:
    int pre[maxn]; // mảng lưu đường đi đến đích
    int n, s, t;
    const int INF = 1e9;

public:
    Dijkstra(const GraphInput &input) : n(input.num_dinh), s(input.start), t(input.des) {}

    virtual void findShortestPath(Graph &graph)
    {
        vector<ll> d(n + 1, INF); // mảng lưu đường đi ngắn nhất
        d[s] = 0;
        pre[s] = s;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Q;
        Q.push({0, s});

        vector<pair<int, int>> *adj = graph.getAdjList();

        while (!Q.empty())
        {
            pair<int, int> top = Q.top();
            Q.pop();
            int u = top.second;
            int kc = top.first;
            if (kc > d[u])
                continue;
            for (auto it : adj[u])
            {
                int v = it.first;
                int w = it.second;
                if (d[v] > d[u] + w)
                {
                    d[v] = d[u] + w;
                    Q.push({d[v], v});
                    pre[v] = u;
                }
            }
        }
        // cout << d[t] << endl;
        // vector<int> path;
        // while (1)
        // {
        //     path.push_back(t);
        //     if (t == s)
        //         break;
        //     t = pre[t];
        // }
        // reverse(begin(path), end(path));
        // for (int x : path)
        // {
        //     cout << x << " ";
        // }

        for (int i = 0; i < n; i++) {
            vector<int> path;
            int j = i;
            while (1) {
                path.push_back(j);
                if (j == s) {
                    break;
                }
                j = pre[j];
            }
            reverse(begin(path), end(path));
            cout << "tu 0 den " << i << endl;
            for (int x : path)
            {
                cout << x << " ";
            }
            cout << endl;
        }
    }

    ~Dijkstra() = default;
};

class Astar : public Dijkstra
{
private:
    int heuristic(int from, int to)
    {
        return abs(from - to); 
    }

public:
    Astar(const GraphInput &input) : Dijkstra(input) {}

    void findShortestPath(Graph &graph) override
    {
        vector<ll> g(n + 1, INF); // đường đi ngắn nhất
        g[s] = 0;
        vector<ll> h(n + 1, INF); // heuristic
        h[s] = heuristic(s, t);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Q;
        Q.push({g[s] + h[s], s});
        vector<pair<int, int>> *adj = graph.getAdjList();
        while (!Q.empty())
        {
            int u = Q.top().second;
            int f = Q.top().first;
            Q.pop();
            if (f > g[u] + h[u])
                continue;
            for (auto it : adj[u])
            {
                int v = it.first;
                int w = it.second;
                if (g[v] > g[u] + w)
                {
                    g[v] = g[u] + w;
                    h[v] = heuristic(v, t);
                    Q.push({g[v] + h[v], v});
                    pre[v] = u;
                }
            }
        }
        cout << g[t] << endl;
        vector<int> path;
        while (1)
        {
            path.push_back(t);
            if (t == s)
                break;
            t = pre[t];
        }
        reverse(begin(path), end(path));
        for (int x : path)
        {
            cout << x << " ";
        }
    }
};

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input2.txt", "r", stdin);
    freopen("output2.txt", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    GraphInput userInput;
    Graph graph(userInput);
    for (int i = 0; i < userInput.num_canh; ++i)
    {
        int x, y, w;
        cin >> x >> y >> w;
        graph.addEdge(x, y, w);
    }

    Dijkstra dijkstra(userInput);
    cout << "dijkstra: " << endl;
    dijkstra.findShortestPath(graph);
    cout << endl;

    Astar astar(userInput);
    cout << "astar: " << endl;
    astar.findShortestPath(graph);
    cout << endl;

    return 0;
}
