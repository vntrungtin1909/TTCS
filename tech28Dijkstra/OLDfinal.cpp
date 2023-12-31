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
    void virtual findShortestPath(Graph &graph)
    {
        vector<ll> d(n + 1, INF); // mảng lưu đường đi ngắn nhất
        d[s] = 0;
        pre[s] = s;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Q;
        int a[1000][1000];
        
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
        cout << d[t] << endl;
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
    void
    findShortestPath(Graph &graph) override
    {
        vector<ll> g(n + 1, INF); // duong di ngan nhat
        g[s] = 0;
        // vector<ll> h(n + 1, INF); // vector tinh heuristic
        // h[s] = heuristic(s, t);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Q;
        Q.push({heuristic(s, t), s});
        vector<pair<int, int>> *adj = graph.getAdjList();
        while (!Q.empty())
        {
            int u = Q.top().second;
            int kc = Q.top().first;
            Q.pop();
            if (kc > g[u])
                continue;
            for (auto it : adj[u])
            {
                int v = it.first;
                int w = it.second;
                if (g[v] > g[u] + w)
                {
                    g[v] = g[u] + w;
                    Q.push({g[v] + heuristic(v, t), v});
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
    freopen("input1.txt", "r", stdin);
    freopen("output1.txt", "w", stdout);
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
    dijkstra.findShortestPath(graph);
    cout << endl;

    // Astar astar(userInput);
    // astar.findShortestPath(graph);
    // cout << endl;

    return 0;
}