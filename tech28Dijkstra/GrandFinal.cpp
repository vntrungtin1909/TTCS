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

class GraphNhapXuat
{
public:
    int so_luong_dinh; // số lượng đỉnh
    int so_luong_canh; // số lượng cạnh
    int dinh_batdau;   // đỉnh bắt đầu
    int dinh_dich;     // đỉnh đích

    GraphNhapXuat()
    {
#ifndef ONLINE_JUDGE
        freopen("input1.txt", "r", stdin);
        freopen("output2612.txt", "w", stdout);
#endif
        cin >> so_luong_dinh >> so_luong_canh;
        // Graph graph();
        // ifstream fileNhap("input1.txt");
        // if (fileNhap.is_open())
        // {
        //     fileNhap >> so_luong_dinh >> so_luong_canh;
        //     for (int i = 0; i < so_luong_dinh; ++i)
        //     {
        //         int dinh, dinh_ke, trong_so, so_canh_ke;
        //         cin >> dinh >> so_canh_ke;
        //         for (int j = 0; j < so_canh_ke; j++)
        //         {
        //             cin >> dinh_ke >> trong_so;
        //             graph.(dinh, dinh_ke, trong_so, j);
        //         }
        //     }
        //     fileNhap.close();
        // }
    }
    void duongdi(vector<ll>& khoang_cach, int path[])
    {
        
    }
};

class Graph
{
protected:
    int n, m;      // số lượng đỉnh và số lượng cạnh
    Dinh adj[100]; // danh sách kề

public:
    Graph(const GraphNhapXuat &input) : n(input.so_luong_dinh), m(input.so_luong_canh) {}

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

class Dijkstra
{
protected:
    int pre[maxn]; // mảng lưu đường đi đến đích
    int n;

public:
    Dijkstra(const GraphNhapXuat &input) : n(input.so_luong_dinh) {}

    virtual void NganNhat(Graph &graph, int batdau)
    {
        vector<ll> d(n + 1, INF); // mảng lưu đường đi ngắn nhất
        d[batdau] = 0;
        pre[batdau] = batdau;
        Dinh *adj = graph.TT_dothi();
        Canh a[1000];
        a[0].trong_so = 0;
        a[0].dinh = batdau;
        bool first = true;
        while (1)
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

    }

    ~Dijkstra() = default;
};

int main()
{
    GraphNhapXuat userInput;
    Graph graph(userInput);
    graph.nhap();

    Dijkstra dijkstra(userInput);
    cout << "dijkstra: " << endl;
    // stack<int> ans = dijkstra.NganNhat(graph, 0, 1);

    // while (!ans.empty())
    // {
    //     cout << ans.top() << " ";
    //     ans.pop();
    // }
    // cout << endl;

    return 0;
}
