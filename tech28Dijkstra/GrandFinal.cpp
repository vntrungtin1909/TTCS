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

class Dinh
{
public:
    int so_canh_ke;
    Canh c[1000];
    Dinh() : so_canh_ke(0) {}
    Dinh(int so_canh) : so_canh_ke(so_canh) {}
};

class GraphNhapXuat
{
public:
    int so_luong_dinh; // số lượng đỉnh
    int so_luong_canh; // số lượng cạnh
    int dinh_batdau;   // đỉnh bắt đầu
    int dinh_dich;     // đỉnh đích

    GraphNhapXuat(const string& input, const string& output)
    {
        #ifndef ONLINE_JUDGE
            freopen(input.c_str(), "r", stdin);
            freopen(output.c_str(), "w", stdout);
        #endif

        cin >> so_luong_dinh >> so_luong_canh >> dinh_batdau >> dinh_dich;
    }

    static Dinh* dothi(Dinh* adj, int n) {
        for (int i = 0; i < n; ++i)
        {
            int dinh, dinh_ke, trong_so, so_canh_ke;
            cin >> dinh >> so_canh_ke;
            for (int j = 0; j < so_canh_ke; j++)
            {
                cin >> dinh_ke >> trong_so;
                adj[dinh].c[i].dinh = dinh_ke;
                adj[dinh].c[i].trong_so = trong_so;
                adj[dinh].so_canh_ke++;
            }
        }
        return adj;
    }

    static void duongdi(vector<ll> &khoang_cach, int path[], int batdau, int dich = 0, bool dijkstra = true)
    {
        int n;
        int i;
        if (dijkstra) {
            n = khoang_cach.size();
            i = 0;
        }
        else {
            n = 1;
            i = dich;
        }
        cout << (dijkstra == true ? "dijkstra: ": "astar: ") << endl;
        while (n > 0) {
            stack<int> ans;
            int j = i;
            while (1) {
                ans.push(j);
                if (j == batdau) break;
                j = path[j];
            }
            cout << "khoang cach tu " << batdau << " den " << i << " la: " << khoang_cach[i] << endl;
            while (!ans.empty()) {
                cout << ans.top() << " ";
                ans.pop();
            }
            cout << endl;
            i++;
            n--;
        }
    }
};

class Graph
{
protected:
    int n, m, batdau, dich;      // số lượng đỉnh và số lượng cạnh
    Dinh adj[100]; // danh sách kề

public:
    Graph(const GraphNhapXuat &input) : n(input.so_luong_dinh), m(input.so_luong_canh), batdau(input.dinh_batdau), dich(input.dinh_dich) {
        
    }

    void nhap()
    {
        for (int i = 0; i < n; ++i)
        {
            int dinh, dinh_ke, trong_so, so_canh_ke;
            cin >> dinh >> so_canh_ke;
            for (int j = 0; j < so_canh_ke; j++)
            {
                cin >> dinh_ke >> trong_so;
                themCanh(dinh, dinh_ke, trong_so, j);
            }
        }
    }

    void themCanh(int dinh, int dinh_ke, int trong_so, int i)
    {
        adj[dinh].c[i].dinh = dinh_ke;
        adj[dinh].c[i].trong_so = trong_so;
        adj[dinh].so_canh_ke++;
    }

    Dinh *TT_dothi()
    {
        return adj;
    }

    ~Graph() = default;
};

class Dijkstra : public Graph
{
protected:
    int pre[maxn]; // mảng lưu đường đi đến đích

public:
    Dijkstra(const GraphNhapXuat &input) : Graph(input) {}

    virtual void NganNhat(Graph &graph )
    {
        vector<ll> d(n, INF); // mảng lưu đường đi ngắn nhất
        d[batdau] = 0;
        pre[batdau] = batdau;
        Dinh *adj = graph.TT_dothi();
        Canh a[1000];
        a[0].trong_so = 0;
        a[0].dinh = batdau;
        bool first = true;
        while (a[0].dinh != INF)
        {
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
                    for (int i = 0; i < 1000; i++)
                    {
                        for (int j = i + 1; j < 1000; j++)
                        {
                            if (a[i].trong_so > a[j].trong_so)
                            {
                                Canh c = a[i];
                                a[i] = a[j];
                                a[j] = c;
                            }
                        }
                    }
                    pre[v] = u;
                }
            }
        }
        GraphNhapXuat::duongdi(d, pre, batdau);
    }

    ~Dijkstra() = default;
};

class Astar : public Graph
{
private:
    int heuristic(int from, int to)
    {
        return abs(from - to); 
    }

protected:
    int pre[maxn];
public:
    Astar(const GraphNhapXuat &input) : Graph(input) {}

    void NganNhat(Graph &graph) 
    {
        vector<ll> g(n, INF); // đường đi ngắn nhất
        g[batdau] = 0;
        vector<ll> h(n, INF); // heuristic
        h[batdau] = heuristic(batdau, dich);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Q;
        Q.push({g[batdau] + h[batdau], batdau});
        Dinh *adj = graph.TT_dothi();
        while (Q.top().second != dich)
        {
            int u = Q.top().second;
            int f = Q.top().first;
            Q.pop();
            if (f > g[u] + h[u])
                continue;
            for (int i = 0; i < adj[u].so_canh_ke; i++)
            {
                int v = adj[u].c[i].dinh;
                int w = adj[u].c[i].trong_so;
                if (g[v] > g[u] + w)
                {
                    g[v] = g[u] + w;
                    h[v] = heuristic(v, dich);
                    Q.push({g[v] + h[v], v});
                    pre[v] = u;
                }
            }
        }
        GraphNhapXuat::duongdi(g, pre, batdau, dich, false);
    }
};

int main()
{
   
    GraphNhapXuat userInput("input1.txt", "output2612.txt");
    Graph graph(userInput);
    graph.nhap();

    Dijkstra dijkstra(userInput);
    // dijkstra.nhap();
    dijkstra.NganNhat(graph);

    // Astar astar(userInput);
    // astar.nhap();
    // astar.NganNhat(graph);

    return 0;
}
