#include<bits/stdc++.h>
using namespace std;

using ll = long long;

const int maxn = 100001;
int n, m, s, t;  //so luong dinh, so luong canh, dinh bat dau, dinh can tim
vector<pair<int, int>> adj[maxn];

void nhap() {
    cin >> n >> m >> s >> t;
    for (int i = 0; i < m; i++) {
        int x, y, w; cin >> x >> y >> w; // dinh x co duong di toi dinh y co trong so w
        adj[x].push_back({y, w});
        adj[y].push_back({x, w});
    }
}

const int INF = 1e9;
int pre[maxn]; // mang xay dung duong di ngan nhat
void dijkstra(int s, int t) {
    // mang luu khoang cach duong di
    vector<ll> d(n + 1, INF);
    d[s] = 0;
    pre[s] = s;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Q; // khoang cach tu dinh nguon, dinh
    Q.push({0, s});
    while (!Q.empty())
    {
        // chon ra dinh co khoang cach tu S nho nhat
        pair<int, int> top = Q.top(); Q.pop();
        int u = top.second;
        int kc = top.first;
        if (kc > d[u]) continue;
        for (auto it : adj[u]) { // Relaxation: cap nhat khoang cach tu dinh s toi moi dinh ke voi u
            int v = it.first;
            int w = it.second;
            if (d[v] > d[u] + w) {
                d[v] = d[u] + w;
                Q.push({d[v], v});
                pre[v] = u; // truoc v la u
            }
        }
    }
    cout << d[t] << endl;
    vector<int> path;
    while (1) {
        path.push_back(t); 
        if (t == s) break;
        t = pre[t];
    }
    reverse(begin(path), end(path));
    for (int x : path) {
        cout << x << " ";
    }
    
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    nhap();
    dijkstra(s, t);
}