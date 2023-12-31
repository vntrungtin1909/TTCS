#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int maxn = 100001;
const int INF = 1e9;

struct Canh
{
    int dinh;
    int trong_so;
    Canh() : trong_so(INF), dinh(INF) {}
    Canh(int w, int v) : trong_so(w), dinh(v) {}
};
bool SS_trong_so(const Canh &a, const Canh &b)
{
    return a.trong_so < b.trong_so;
}

class Dinh
{
public:
    int so_canh_ke;
    Canh c[1000];
    Dinh() : so_canh_ke(0) {}
    Dinh(int so_canh) : so_canh_ke(so_canh) {}
};

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
    int n, m;      // số lượng đỉnh và số lượng cạnh
    Dinh adj[100]; // danh sách kề

public:
    Graph(const GraphInput &input) : n(input.num_dinh), m(input.num_canh) {}

    // void nhap()
    // {
    //     for (int i = 0; i < n; ++i)
    //     {
    //         int dinh, dinh_ke, trong_so, so_canh_ke;
    //         cin >> dinh >> so_canh_ke;
    //         for (int j = 0; j < so_canh_ke; j++)
    //         {
    //             cin >> dinh_ke >> trong_so;
    //             addEdge(dinh, dinh_ke, trong_so, j);
    //         }
    //     }
    // }

    void addEdge(int dinh, int dinh_ke, int trong_so, int i)
    {
        adj[dinh].c[i].dinh = dinh_ke;
        adj[dinh].c[i].trong_so = trong_so;
        adj[dinh_ke].c[i].dinh = dinh;
        adj[dinh_ke].c[i].trong_so = trong_so;
        adj[dinh].so_canh_ke++;
    }

    Dinh *getAdjList()
    {
        return adj;
    }

    ~Graph() = default;
};

class Dijkstra
{
protected:
    int pre[maxn]; // mảng lưu đường đi đến đích
    int n, m, s, t;
    vector<ll> d; // mảng lưu đường đi ngắn nhất

public:
    Dijkstra(const GraphInput &input) : n(input.num_dinh), m(input.num_canh), s(input.start), t(input.des) {}

    virtual void NganNhat(Graph &graph)
    {
        d.assign(n + 1, INF);
        int tong_so_canh = m;
        d[s] = 0;
        pre[s] = s;
        Dinh *adj = graph.getAdjList();
        Canh a[1000];
        a[0].trong_so = 0;
        a[0].dinh = s;
        bool first = true;
        while (tong_so_canh != 0)
        {
            // if (a[0].dinh == t)
            // {
            //     stack<int> path;
            //     while (1)
            //     {
            //         path.push(t);
            //         if (t == s)
            //             return path;
            //         t = pre[t];
            //     }
            // }
            int i = 0;
            int u = a[0].dinh;
            int kc = a[0].trong_so;
            while (1)
            {
                if (first)
                {
                    a[i].dinh = a[i + 1].dinh;
                    a[i].trong_so = a[i + 1].trong_so;
                    first = false;
                }
                else if (a[i].dinh == INF && a[i].trong_so == INF)
                    break;
                else
                {
                    a[i].dinh = a[i + 1].dinh;
                    a[i].trong_so = a[i + 1].trong_so;
                }
                i++;
            }
            if (kc > d[u])
                continue;
            for (int i = 0; i < adj[u].so_canh_ke; i++)
            {
                int v = adj[u].c[i].dinh;
                int w = adj[u].c[i].trong_so;
                if (d[v] > d[u] + w)
                {
                    d[v] = d[u] + w;
                    a[999].dinh = v;
                    a[999].trong_so = d[v];
                    sort(a, a + 1000, SS_trong_so);
                    pre[v] = u;
                }
            }
            tong_so_canh--;
        }
    }
    vector<ll> get() {
        return d;
    }
    ~Dijkstra() = default;
};

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input1.txt", "r", stdin);
    // freopen("output1.txt", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    GraphInput userInput;
    Graph graph(userInput);
    for (int i = 0; i < userInput.num_dinh; ++i)
    {
        int dinh, dinh_ke, trong_so, so_canh_ke;
        cin >> dinh >> so_canh_ke;
        for (int j = 0; j < so_canh_ke; j++)
        {
            cin >> dinh_ke >> trong_so;
            graph.addEdge(dinh, dinh_ke, trong_so, j);
        }
    }

    Dijkstra dijkstra(userInput);
    cout << "dijkstra: " << endl;
    dijkstra.NganNhat(graph);
    vector<ll> ans = dijkstra.get();
    for (int i = 0; i < userInput.num_dinh; i++)
    {
        cout << ans[i] << " ";
    }
    // while (!ans.empty())
    // {
    //     cout << ans.top() << " ";
    //     ans.pop();
    // }
    cout << endl;
    return 0;
}
